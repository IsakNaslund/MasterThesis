#include "Structure.h"
#include "GlobalSettings.h"


CIFem::Structure::Structure()
{
	// Structure orientation (standard XYZ plane)
	Vector3d x(1, 0, 0);
	Vector3d y(0, 1, 0);
	Vector3d z(0, 0, 1);
	XYZ origin(0, 0, 0);
	_structureOrientation = Plane(x, y, z, origin);
}


CIFem::Structure::~Structure()
{
	// Should not be necessary to do anymore, since elements were changed to smart pointers
	/*
	for (int i = 0; i < _elements.size(); i++)
		delete _elements[i];
	*/

	_elements.clear();
}

void CIFem::Structure::AddNode(std::shared_ptr<INode> node)
{
	_nodes.push_back(node);
}

void CIFem::Structure::AddNode(std::vector<std::shared_ptr<INode>> nodes)
{
	for (int i = 0; i < nodes.size(); i++)
		AddNode(nodes[i]);
}

void CIFem::Structure::AddElementRcp(std::shared_ptr<IElementRcp> elementRcp)
{
	_elementRcps.push_back(elementRcp);
}

void CIFem::Structure::AddElementRcp(std::vector<std::shared_ptr<IElementRcp>> elements)
{
	for (int i = 0; i < elements.size(); i++)
		AddElementRcp(elements[i]);
}


// Not implemented!
CIFem::Structure CIFem::Structure::Copy()
{
	// Create new structure
	CIFem::Structure s();

	// Copy orientation
	// Not necessary atm since orientation is standard and set in constructor

	// Copy nodes
	throw std::exception("Not implemented yet!");

	// Copy ElementRecipes

	// Copy Elements

	// Remap dofs (maybe, maybe needs to be done while copying the other stuff)

	return Structure();
}


void CIFem::Structure::Solve()
{
	// Build structure
	BuildStructure();

	// Get dofs
	std::vector<std::shared_ptr<CIFem::DOF>> spDofs = GetDofs();

	// Update dof kIndex
	SetDofKMatIndex(spDofs);

	//Calculate elemet forces
	CalculateElemetForces();


	// Create K matrix
	arma::sp_mat K = AssembleStiffnessMatrix(spDofs);
	
	// Get a and f vectors 
	arma::mat C = GetCMatrix();							// Get transformation vector for restraints
	arma::colvec am = GetDisplacementVector(spDofs);	// Get displacement vector
	arma::colvec f = GetForceVector(spDofs);			// Get force vector

	// Transform matrices and vectors to allow for non-global restraints

	// Debug
	arma::mat Kwrite(K);
	Kwrite.print("Kwrite: ");
	f.print("f: ");

	// Solve K matrix
	arma::colvec s;		// Resulting forces
	LinEqSolve(K, am, f, C, spDofs, s);

	// Store results in dofs
	StoreResultsInDofs(am, s, spDofs);
}

std::vector<std::shared_ptr<CIFem::IElement>> CIFem::Structure::GetElements()
{
	return _elements;
}


std::vector<std::shared_ptr<CIFem::IElement>> CIFem::Structure::CreateElements()
{
	std::vector<std::shared_ptr<CIFem::IElement>> elements;
	std::vector<std::shared_ptr<CIFem::IElement>> outElems;
	for (int i = 0; i < _elementRcps.size(); i++)
	{
		outElems.clear();
		outElems = _elementRcps[i]->CreateElement(_nodes);

		for (int j = 0; j < outElems.size(); j++)
			elements.push_back(outElems[j]);
	}

	return elements;
}

void CIFem::Structure::BuildStructure()
{
	// Create elements from recipes and assign
	_elements = CreateElements();
}

std::vector<std::shared_ptr<CIFem::DOF>> CIFem::Structure::GetDofs()
{
	// Create pointer list of dofs
	std::vector<std::shared_ptr<CIFem::DOF>> dofs;

	// Add all dofs in nodes
	for (int i = 0; i < _nodes.size(); i++)
	{
		std::vector<std::shared_ptr<CIFem::DOF>> nDofs = _nodes[i]->GetDofs();
		for (int j = 0; j < nDofs.size(); j++)
			dofs.push_back(nDofs[j]);
	}

	// Add non-duplicate dofs in elements
	for (int i = 0; i < _elements.size(); i++)
	{
		std::vector<std::shared_ptr<CIFem::DOF>> eDofs = _elements[i]->GetDofs();
		for (int j = 0; j < eDofs.size(); j++)
		{
			bool unique = true;
			for (int k = 0; k < dofs.size(); k++)
			{
				if (eDofs[j] == dofs[k])
				{
					unique = false;
					break;
				}
			}

			if (unique)
				dofs.push_back(eDofs[j]);
		}
	}

	return dofs;
}



void CIFem::Structure::SetDofKMatIndex(std::vector<std::shared_ptr<CIFem::DOF>> spDofs)
{
	//Counting dofs, assuming all dofs exists in the nodes
	int dofCounter = 0;
	for each (std::shared_ptr<DOF> dof in spDofs)
	{
		dof->UpdateKIndex(dofCounter);
		dofCounter++;
	}
}

arma::sp_mat CIFem::Structure::AssembleStiffnessMatrix(std::vector<std::shared_ptr<CIFem::DOF>> spDofs)
{
	// Count dofs
	int dofCount = spDofs.size();
	
	// Create K matrix
	arma::sp_mat K(dofCount, dofCount);

	// Assemble K matrix
	for each (std::shared_ptr<CIFem::IElement> pElem in _elements)
	{
		arma::mat Ke = pElem->GetStiffnessMatrix();

		AssembleElementsInKMat(K, Ke, pElem->GetDofs());
	}
	
	return K;
}

void CIFem::Structure::AssembleElementsInKMat(arma::sp_mat & K, arma::mat & Ke, std::vector<std::shared_ptr<DOF>> spEDofs)
{
	//DEBUG
	K.print("K:");
	Ke.print("Ke");

	// Check inputs
	int n = K.n_rows;
	for each (std::shared_ptr<DOF> spDof in spEDofs)
		if (spDof->GetKIndex() > n - 1)
			throw std::invalid_argument("Error in k matrix numbering");

	int nKe = Ke.n_rows;
	if (nKe != spEDofs.size())
		throw std::invalid_argument("Element dofs and Ke matrix rows mismatch!");

	// Assemble K matrix
	for (int i = 0; i < nKe; i++)
	{
		int iKIndex = spEDofs[i]->GetKIndex();
		for (int j = 0; j < nKe; j++)
		{
			int jKIndex = spEDofs[j]->GetKIndex();
			K.at(iKIndex, jKIndex) += Ke.at(i, j);
		}
	}
}

arma::colvec CIFem::Structure::GetForceVector(std::vector<std::shared_ptr<DOF>> spDofs)
{
	arma::colvec f(spDofs.size(), arma::fill::zeros);

	for each (std::shared_ptr<DOF> spDof in spDofs)
		f(spDof->GetKIndex()) = spDof->GetLoad();

	return f;
}

// Creates a displacement vector from the dofs.
// N.B. the displacement vector is in transformed coordinates (am, rather than as)
arma::colvec CIFem::Structure::GetDisplacementVector(std::vector<std::shared_ptr<DOF>> spDofs)
{
	arma::colvec a(spDofs.size(), arma::fill::zeros);
	
	for each (std::shared_ptr<DOF> spDof in spDofs)
		if (spDof->HasSetTranslation())
			a(spDof->GetKIndex()) = spDof->GetTranslation();

	return a;
}



void CIFem::Structure::LinEqSolve(arma::sp_mat & K, arma::colvec & a, arma::colvec & f, arma::mat & C, 
	std::vector<std::shared_ptr<DOF>> spDofs, arma::colvec & s)
{
	// Check prescribed deformations
	std::vector<unsigned int> transBCDof;
	std::vector<unsigned int> fDof;
	std::vector<unsigned int> pDof;
	for each (std::shared_ptr<DOF> dof in spDofs)
	{
		// Check transformed bcs
		if (dof->HasTransformedBc())
			transBCDof.push_back(dof->GetKIndex());

		
		// Check prescribed deformations
		if (dof->HasSetTranslation())
			pDof.push_back(dof->GetKIndex());
		else
			fDof.push_back(dof->GetKIndex());
		
	}

	// There must be a way to do this from the start,
	// however, I think uvec is fixed size
	arma::uvec ufDof(fDof);
	arma::uvec upDof(pDof);

	arma::colvec fa(fDof.size());

	// Solve deformations
	arma::mat Kmat(K); // Debugging, workaround this to improve speed
	//arma::sp_mat Kff(Kmat(ufDof, ufDof));
	arma::mat f_fsolved = f(ufDof)- Kmat(ufDof, upDof) * a(upDof);
	//fa = arma::spsolve(Kff, f_fsolved);
	fa = arma::solve(Kmat(ufDof, ufDof), f_fsolved);
	a(ufDof) = fa;

	// Solve forces
	s = K*a - f;
}

void CIFem::Structure::StoreResultsInDofs(arma::colvec a, arma::colvec f, std::vector<std::shared_ptr<DOF>> spDofs)
{
	// Set results in dofs
	for (int i = 0; i < spDofs.size(); i++)
	{
		spDofs[i]->SetResults(a(spDofs[i]->GetKIndex()), f(spDofs[i]->GetKIndex()));
	}
}

arma::mat CIFem::Structure::GetCMatrix()
{
	// Count dofs
	int nDofs = 0;
	for each (std::shared_ptr<INode> node in _nodes)
		nDofs += node->GetDofs().size();

	// Create C matrix
	arma::mat C(nDofs, nDofs, arma::fill::zeros);

	// Populate C matrix
	for each (std::shared_ptr<INode> node in _nodes)
	{
		// Get local C matrix
		arma::mat CN(1,1);
		if (node->GetNodeCMatrix(this->_structureOrientation, CN))
		{
			// Populate global C matrix
			std::vector<std::shared_ptr<DOF>> nDofs = node->GetDofs();
			for (int i = 0; i < nDofs.size(); i++)
			{
				for (int j = 0; j < nDofs.size(); j++)
					C(nDofs[i]->GetKIndex(), nDofs[j]->GetKIndex()) = CN(i, j);

				// Set transformed BC flag
				nDofs[i]->SetTransformedBC(true);
			}
		}
	}

	return C;
}

void CIFem::Structure::CalculateElemetForces()
{
	for (int i = 0; i < _elements.size(); i++)
	{
		_elements[i]->GravityLoad();
	}

}

