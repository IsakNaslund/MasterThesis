#pragma once
#include "CIFem_dll.h"
#include <string>
#include <memory>


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
		std::shared_ptr<Utilisation> Copy();	// Returns a new shared pointer to an identical object

		void Reset();
		void Update(const double & utilisation, const std::string & description);
		inline double const GetUtil() const { return _util; }
		inline std::string const GetDesc() const { return _description; }
	};
}
