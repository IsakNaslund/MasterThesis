#include "Structure3d.h"

using namespace CIFem;

Structure3d::Structure3d()
{
}


Structure3d::~Structure3d()
{
}

void Structure3d::AddElement(Element3d e)
{
	// Add elements
	_elements.push_back(e);
	
	// Add non-duplicate dofs
	for each (int edof in e.GetDofs())
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
DOF & Structure3d::FindDof(int dofIndex)
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
	arma::mat K(_maxDof+1, _maxDof+1, arma::fill::zeros);

	// Assemble elements
	for each (Element3d elem in _elements)
	{
		std::vector<int> dofs = elem.GetDofs();
		arma::mat Ke = elem.GetStiffnessMatrix();

		// DEBUG
		Ke.print("Ke ");

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
				existingDofs.push_back(i - 1);
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
	arma::uvec uExDof(existingDofs);
	K = K(uExDof, uExDof);

	return K;
}


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
	fa = solve(K(ufDof, ufDof), f(ufDof) - K(ufDof, upDof)*a(upDof));
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
