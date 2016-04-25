#pragma once
#include "CIFem_dll.h"
#include <string>
#include <memory>
#include <vector>
#include "Utilisation.h"


namespace CIFem
{

	class CIFEM_API UtilisationSet
	{
		std::vector<std::shared_ptr<Utilisation>> _utilisations;
		Utilisation _maxUtil;

	public:
		UtilisationSet();
		~UtilisationSet();

		void Update(double utilisation, std::string description, int i);
		void Reset();
		void Clear();
		void SetUpEmptyUtilisations(int nb);
		const int size() const
		{
			return _utilisations.size();
		}

		const Utilisation & MaxUtil() const { return _maxUtil; }

		void ScaleUtilisation(double sFac);

		const std::shared_ptr<Utilisation> &operator[](int i) const
		{
			return _utilisations[i];
		}
	};
}

