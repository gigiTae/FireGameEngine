#include "Common.h"
#include "Parser.h"
#include "Geometry.h"

int main()
{
	const char* fileName = "file.fbx";

	FBXLoad::Import(fileName);
}