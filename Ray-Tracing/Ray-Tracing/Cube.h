#pragma once
#include "Object.h"
#include "Vector3.h"
#include <array>

namespace unstd
{
	//class Cube : public Object
	//{
	//	class Triangle
	//	{
	//	public:
	//		typedef unstd::Vector3<float> vertex_t;
	//		typedef std::array<vertex_t, 3> vertices_t;
	//		vertices_t vertices;

	//		Triangle(const vertices_t& vertices_)
	//			:vertices(vertices_) {};
	//	};

	//	const float kEpsilon = 1e-8;

	//	std::array<Triangle, 12> qbe;

	//	bool render()
	//	{

	//	}


	//	// Ray triangle intersect
	//	/*
	//		https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
	//	*/
	//	bool hit(const Triangle tri, const unstd::Ray r)
	//	{
	//		/*
	//			origin
	//			direction
	//			v0
	//			v1
	//			v2
	//			t
	//			u
	//			v

	//			Ray r has information:
	//				r.origin() = origin
	//				r.direction() = direction
	//				r.at() = t;

	//			Triangle has information (3 vector points for verteces):
	//				v0 = t.vertices[0];
	//				v1 = t.vertices[1];
	//				v2 = t.vertices[2];


	//		*/

	//		// ASSESSES TRIANGLE BASED ON THESE VERTICES
	//		//unstd::Vector3<float> v0(-1, -1, -5);
	//		//unstd::Vector3<float> v1(1, -1, -5);
	//		//unstd::Vector3<float> v2(0, 1, -5);


	//		//////////////////////////
	//	   //Ray triangle intersect//
	//	  //////////////////////////			

	//	  // Compute plane's normal.
	//		unstd::Vector3<float> v0v1 = v1 - v0;
	//		unstd::Vector3<float> v0v2 = v2 - v0;
	//		unstd::Vector3<float> N = cross(v0v1, v0v2);
	//		float area2 = N.length();
	//		float denom = dot(N, N);
	//		float t, u, v;

	//		// STEP 1: Finding P.

	//			// Check if ray and plane are parallel.
	//		float NdotRayDirection = dot(N, r.direction());

	//		if (fabs(NdotRayDirection) < kEpsilon) { return false; } // They are paralell so hit is impossible.

	//		//Compute d (equation 2).
	//		float d = -(dot(N, v0));

	//		// Compute t (equation 3).
	//		t = -(dot(N, r.origin()) + d) / NdotRayDirection;

	//		// Check if the triangle is behind the ray.
	//		if (t < 0) { return false; } // triangle is behind.

	//		// Compute the intersection point (equation 1).
	//		unstd::Vector3<float> P = r.origin() + t * r.direction();

	//		// STEP 2: inside-outside test.

	//		unstd::Vector3<float> C; // Vector perpendicular to triangle's plane.

	//		// Edge 0.
	//		unstd::Vector3<float> edge0 = v1 - v0;
	//		unstd::Vector3<float> vp0 = P - v0;
	//		C = cross(edge0, vp0);
	//		if (dot(N, C) < 0) { return false; } // P is on the right side.

	//		// Edge 1.
	//		unstd::Vector3<float> edge1 = v2 - v1;
	//		unstd::Vector3<float> vp1 = P - v1;
	//		C = cross(edge1, vp1);
	//		if ((u = dot(N, C)) < 0) { return false; } // P is on the right side.

	//		// Edge 2.
	//		unstd::Vector3<float> edge2 = v0 - v2;
	//		unstd::Vector3<float> vp2 = P - v2;
	//		C = cross(edge2, vp2);
	//		if ((v = dot(N, C)) < 0) { return false; } // P is on the right side.

	//		u /= denom;
	//		v /= denom;

	//		// If all discriminators fail, return true.
	//		return true;
	//	}
	//};

	//std::istream& operator>>(std::istream& is, Polygon& p);
}