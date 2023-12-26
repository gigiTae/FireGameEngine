#pragma once

#include <fbxsdk.h>
#include <cassert>
#include <vector>

namespace FBXLoad
{ 
	struct SceneData; 

	void Import(const char* file);
}