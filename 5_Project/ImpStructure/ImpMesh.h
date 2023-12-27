#pragma once
#include "ImpMath.h"
#include "pch.h"

using namespace ImpMath;

namespace ImpStructure
{
	struct Vertex
	{
		Vector3 _pos;

		float _u, _v;

		Vector3 _normal;
		Vector3 _tangent; // normalMap
		Vector3 _bitangent; // normalMap
	};

	struct Face
	{
		size_t vertexIndex[3];
		size_t textureIndex[3];
	};

	struct ImpMesh
	{
		std::vector<Vertex*> _meshVertex;
		std::vector<Face*> _meshFace;
	};
}