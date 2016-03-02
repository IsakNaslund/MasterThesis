#pragma once

namespace CIFem
{
	class SectionProperties
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

		double A();
		double Iy();
		double Iz();
		double Kv();

	};

}