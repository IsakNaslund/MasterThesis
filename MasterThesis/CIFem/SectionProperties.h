#pragma once

namespace CIFem
{
	struct SectionProperties
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

	};

}