#pragma once

#include "LoadCombination.h"
#include "WR_Vector.h"
#include <msclr\marshal_cppstd.h>
#include "WR_XYZ.h"

namespace CIFem_wrapper
{
	public ref class WR_LoadCombination
	{
		CIFem::LoadCombination * _loadComb;

	public:
		WR_LoadCombination(System::String^ name);
		WR_LoadCombination(System::String^ name, WR_Vector^ gravField);
		WR_LoadCombination(System::String^ name, bool gravityOn);
		~WR_LoadCombination();


		void AddPointLoad(WR_Vector^ force, WR_Vector^ moment, WR_XYZ^ pos);

		void SetGravity(WR_Vector^ gravField);
		void SetGravity(bool gravityOn);

		WR_LoadCombination^ Copy();

		LoadCombination GetCombination();

	private:
		WR_LoadCombination(CIFem::LoadCombination comb);
	};

}