#pragma once
#include "CIFem_dll.h"
#include "IUtilisationCheck.h"
#include "IUtilCheck3d.h"
#include "Vector3d.h"
#include <memory>
#include "Checks.h"


namespace CIFem
{
	class CIFEM_API Element3dChecks
	{
		std::vector<std::shared_ptr<IUtilCheck3d>> _checks;
	public:
		Element3dChecks();
		~Element3dChecks();

		void AddCheck(std::shared_ptr<IUtilCheck3d>);
		//Checks utilisations for a given loadcase. Updates the utilisation if needed.
		void CheckElementUtilisations(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string resName);
		//Checks if a cross section holds for all loadcases. Returns true if it holds, false if not
		bool CheckUtilUntilFail(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results);
		bool CheckUtilUntilFail(std::shared_ptr<ICrossSection> xSec, std::shared_ptr<Material> mat, ElementResults3d & results, std::string loadCase);
		static Element3dChecks BasicCheck();
		static std::shared_ptr<Element3dChecks> BasicCheckSharedPtr();


	};
}

