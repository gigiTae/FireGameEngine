#pragma once
#include "ImpMath.h"
#include "pch.h"

using namespace ImpMath;

namespace ImpStructure
{
	struct ImpVertex
	{
		Vector3 _localPos;

		//float _u = 0, _v = 0; // texture
		std::vector<Vector2> _uvs;

		Vector3 _normal;
		Vector3 _tangent; // normalMap
		Vector3 _bitangent; // normalMap
		Vector4 _color;
	};

	struct ImpFace
	{
		size_t vertexIndex[3];
		size_t textureIndex[3];
	};

	struct ImpMesh
	{
		std::vector<ImpVertex*> _meshVertex;
		std::vector<ImpFace*> _meshFace;

		bool _hasTexture = false;
		bool _hasNormal = false;
		bool _hasTangent = false;
		bool _hasColor = false;
	};
}