#pragma once
#include <string>
#include "../ImpStructure/ImpMesh.h"

using namespace ImpStructure;

namespace ImpGraphics
{
	class ImpLoader
	{
	public:
		ImpMesh* GetMesh(const std::wstring& path);
	};
}