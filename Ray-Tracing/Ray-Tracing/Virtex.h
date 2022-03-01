#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace unstd
{
	struct Virtex
	{
		unstd::Vector3<> position;
		unstd::Vector3<> colour;
		unstd::Vector2<> texcoord;
		unstd::Vector3<> normal;
	};
}