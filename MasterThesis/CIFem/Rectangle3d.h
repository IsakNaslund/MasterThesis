#pragma once
#include "CIFem_dll.h"
#include "SectionProperties.h"
#include "CIFemMath.h"
#include "ICrossSection.h"



namespace CIFem
{

	class CIFEM_API Rectangle3d :public ICrossSection
	{
		double _height;
		double _width;
	public:
		Rectangle3d();
		Rectangle3d(const double height, const double width);
		~Rectangle3d();
		

		double GetHeight() const;
		double GetWidth() const;


	private:
		void CalcSectionProperties();
		double CalcTorsionalStiffness(const double iy, const double iz);
		double CalcAlphaFactor();

		// Inherited via ICrossSection
		virtual double CheckCombAxialBending(double N, double Myy, double Mzz) override;
		virtual double CheckShearY(double Vy) override;
		virtual double CheckShearZ(double Vz) override;

		bool DirectionDependant() { return true; }

		std::string ToString() override;
	};
}

