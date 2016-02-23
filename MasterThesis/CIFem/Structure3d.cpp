#include "Structure3d.h"
#include "IElement.h"

using namespace CIFem;

Structure3d::Structure3d()
{
}


Structure3d::~Structure3d()
{
}

void Structure3d::AddElement(IElement * e)
{
	// Add elements
	_elements.push_back(e);
	
	// Add non-duplicate dofs
	for each (int edof in e->GetDofs())
	{
		bool newDof = true;
		for each (DOF dof in _dofs)
		{
			if (dof.GetIndex() == edof)
			{
				newDof = false;
				break;
			}
		}
		if (newDof)
		{
			DOF nDof(edof);
			_dofs.push_back(nDof);
		}

		// Update max dof in structure
		if (edof > _maxDof)
			_maxDof = edof;
	}
}

// Apply force or a moment on a dof
void Structure3d::ApplyForce(int dofIndex, double magnitude)
{
	try
	{
		DOF & d = FindDof(dofIndex);
		d._f = magnitude;
	}
	catch (const std::exception& e)
	{
		throw e;
		// Some meaningful exception handling here?
	}
}

// Set a translation on a specific dof
void Structure3d::SetTranslation(int dofIndex, double a)
{
	try
	{
		DOF & d = FindDof(dofIndex);
		d.SetTranslation(a);
	}
	catch (const std::exception& e)
	{
		throw e;
		// Some meaningful exception handling here?
	}
}

// Find a dof
CIFem::DOF& Structure3d::FindDof(int dofIndex)
{
	//for each (DOF & dof in _dofs)
	for (int i = 0; i < _dofs.size(); i++)
	{
		if (dofIndex == _dofs[i].GetIndex())
		{
			DOF & d = _dofs[i];

			return d;	
		}
	}

	// If dof not found
	throw invalid_argument("Degree of freedom not found!");
}

// Assembles the stiffness matrix and gives each dof the corresponding index of their row 
arma::mat Structure3d::AssembleStiffnessMatrix()
{
	///////// NEW STUFF /////////

	//// Check dofs and find corresponding indeces in K matrix ////

	// Debugging way of doing this, change to non-index based later /C
	std::vector<unsigned int> exDofs;


	for (int j = 0; j < _elements.size(); j++)
	{
		for each (DOF dof in _elements[j]->GetDofs())
		{
			bool b = false;
			unsigned int dIndex = dof.GetIndex();
			for (int i = 0; i < exDofs.size(); i++)
				if (dIndex == exDofs[i])
					b = true;

			if (!b)
				exDofs.push_back(dIndex);
		}
	}
	std::sort(exDofs.begin(), exDofs.end());
	int nDof = exDofs.size();	// Number of dofs

	// Set relative index
	for (int i = 0; i < _dofs.size(); i++)
		for (int j = 0; j < nDof; j++)
			if (_dofs[i].GetIndex() == exDofs[j])
				_dofs[i]._kIndex = j;


	// Create K matrix
	arma::mat K(nDof, nDof);

	// Assemble K matrix
	for (int e = 0; e < _elements.size(); e++)
	{
		std::vector<int> dofs = _elements[e]->GetDofs();
		arma::mat Ke = _elements[e]->GetStiffnessMatrix();

		// Yeah, I know...
		// Need to fix this. /C
		for (int i = 0; i < dofs.size(); i++)
			for (int di = 0; di < _dofs.size(); di++)
				if (dofs[i] == _dofs[di].GetIndex())
					for (int j = 0; j < dofs.size(); j++)
						for (int dj = 0; dj < _dofs.size(); dj++)
							if (dofs[j] == _dofs[dj].GetIndex())
								K(_dofs[di]._kIndex, _dofs[dj]._kIndex) = Ke(i, j);
	}







	///////// OLD STUFF /////////
	/*
	arma::mat K(_maxDof+1, _maxDof+1, arma::fill::zeros);

	// Assemble elements
	for each (IElement elem in _elements)
	{
		std::vector<int> dofs = elem.GetDofs();
		arma::mat Ke = elem.GetStiffnessMatrix();

		for (int i = 0; i < dofs.size(); i++)
			for (int j = 0; j < dofs.size(); j++)
				K(dofs[i], dofs[i]) = Ke(i, j);
	}

	// Eliminate possible unassigned dofs from matrix
	int kIndex = 0;
	vector<unsigned int> existingDofs;
	for (int i = 1; i <= _maxDof; i++)
	{
		// Check if index has a corresponding dof
		bool exist = false;
		for (int j = 0; j < _dofs.size(); j++)
		{
			if (_dofs[j].GetIndex() == i)
			{
				exist = true;
				_dofs[j]._kIndex = kIndex;
				exDofs.push_back(i - 1);
				break;
			}
		}
			

		// Increase K index counter
		kIndex++;

		// Dont increase K index counter if the dof doesnt exist
		if (!exist)
			kIndex--;
	}

	// Eliminate non-existing rows and columns from K matrix

	K.print("K (1):");		// DEBUG!!!

	arma::uvec uExDof(exDofs);
	uExDof.print("uExDof:");		// DEBUG!!!
	K = K(uExDof, uExDof);

	K.print("K (2):");		// DEBUG!!!
	*/

	K.print("K");		// DEBUG!!!

	return K;
}


/*
std::shared_ptr[DOF] CIFem::Structure3d::GetOrCreateDof(int index)
{
	for (int i = 0; i < _dofs.size(); i++)
		if (index == _dofs[i].GetIndex())
			return &_dofs[i];

	return nullptr;
}
*/

void Structure3d::Solve()
{
	arma::mat K = AssembleStiffnessMatrix();

	// DEBUG //
	K.print("K matrix");


	// Create a and f vectors
	arma::colvec a(_dofs.size());
	arma::colvec f(_dofs.size());


	// Check prescribed deformations
	std::vector<unsigned int> fDof;
	std::vector<unsigned int> pDof;
	for each (DOF dof in _dofs)
	{
		if (dof.HasSetTranslation())
		{
			pDof.push_back(dof._kIndex);
			a[dof._kIndex] = dof.GetTranslation();
		}
		else
			fDof.push_back(dof._kIndex);

		// Set force
		f[dof._kIndex] = dof._f;
	}

	// There must be a way to do this from the start,
	// however, I think uvec is fixed size
	arma::uvec ufDof(fDof);
	arma::uvec upDof(pDof);

	arma::colvec fa(fDof.size());

	// Solve deformations
	fa = arma::solve(K(ufDof, ufDof), f(ufDof) - K(ufDof, upDof)*a(upDof));
	a(ufDof) = fa;

	// Solve forces
	f = K*a;

	// Set results in dofs
	for (int i = 0; i < _dofs.size(); i++)
	{
		_dofs[i]._resA = a(_dofs[i]._kIndex);
		_dofs[i]._resF = f(_dofs[i]._kIndex);
	}
}

vector<double> CIFem::Structure3d::GetDisplacements()
{

	vector<double> a;
	for each (DOF dof in _dofs)
		a.push_back(dof.GetTranslation());

	return a;
}
