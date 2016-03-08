#pragma once
#include "CIFem_dll.h"

namespace CIFem
{
	class CIFEM_API SectionProperties
	{
		double _area;
		double _Iy;
		double _Iz;
		double _Kv;
	public:
		SectionProperties();
		SectionProperties(const double area);
		SectionProperties(const double area, const double i);
		SectionProperties(const double area, const double iy, const double iz, const double kv);
		~SectionProperties();

		inline double A() const;
		inline double Iy() const;
		inline double Iz() const;
		inline double Kv() const;

	};

}