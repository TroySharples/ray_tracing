#pragma once
#include "Config.h"

namespace unstd
{
	class Camera
	{
	public:
		Camera() = default;
		Camera(
			unstd::Vector3<float> _orig,
			unstd::Vector3<float> _hori,
			unstd::Vector3<float> _vertl,
			unstd::Vector3<float> _llc)
			:	origin(_orig), 
				horizontal(_hori), 
				vertical(_vertl), 
				lower_left_corner(_llc) {}				
		~Camera() = default;

		float c_height = 2.0f;
		float c_width = ASPECT_RATIO * c_height;
		float c_focal_length = 1.0f;

		unstd::Vector3<float> origin = unstd::Vector3<float>(0, 0, 0);
		unstd::Vector3<float> horizontal = unstd::Vector3<float>(c_width, 0, 0);
		unstd::Vector3<float> vertical = unstd::Vector3<float>(0, c_height, 0);
		unstd::Vector3<float> lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - unstd::Vector3<float>(0, 0, c_focal_length);
	};
}