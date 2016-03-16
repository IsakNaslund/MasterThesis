#pragma once
#include "CIFem_dll.h"
#include <string>


namespace CIFem
{
	class CIFEM_API Utilisation
	{
		double _util;
		std::string _description;

	public:
		Utilisation();
		Utilisation(double utilisation, std::string description);
		~Utilisation();

		void Reset();
		void Update(double utilisation, std::string description);
		inline double const GetUtil() { return _util; }
		inline std::string const GetDesc() { return _description; }
	};
}
