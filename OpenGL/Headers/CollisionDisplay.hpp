#pragma once
#include "Math.hpp"
#include "Model.hpp"

namespace CollisionDisplay
{
	class CollisionMesh
	{
	public :

		static void InitCubeMesh();

		static void InitSphereMesh();

		static inline Resources::Model Cube, Sphere;
	private :
	};
}
