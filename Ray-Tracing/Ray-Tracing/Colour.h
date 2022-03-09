#pragma once
#include "Vector3.h"

namespace unstd
{
	class Colour
	{
	public:
		Colour() = default;
		Colour(unstd::Vector3<float> col)
			: colour(col) {}
		~Colour() = default;	

		unstd::Vector3<float> getColour() { return colour; }

	private: 
		unstd::Vector3<float> colour = unstd::Vector3<float>(0, 0, 0);

	};
}