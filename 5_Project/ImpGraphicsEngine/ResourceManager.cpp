#include "pch.h"
#include "ResourceManager.h"

#include "ImpLoader.h"
#include "../ImpFBXLoader/GetLoader.h"
#include "../ImpFBXLoader/IFBXLoader.h"

using namespace ImpGraphics;

ResourceManager::ResourceManager(ImpDevice* device)
	:_resources(), 
	_device(device),
	_impLoader(nullptr),
	_fbxLoader(nullptr)
{
	_impLoader = new ImpLoader;
	FBXLoad::GetLoader GetLoader;
	_fbxLoader = GetLoader.GetFBXLoader();
}

ResourceManager::~ResourceManager()
{
	delete _impLoader;
	delete _fbxLoader;
}
