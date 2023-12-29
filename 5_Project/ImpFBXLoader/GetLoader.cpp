#include "GetLoader.h"
#include "Loader.h"

FBXLoad::IFBXLoader* FBXLoad::GetLoader::GetFBXLoader()
{
	return new Loader;
}
