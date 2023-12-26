#pragma once

#ifndef IMP_ENGIME_MODULE_HEADER
#define IMP_ENGIME_MODULE_HEADER

#include "EngineModulePCH.h"
#include "TypeIndex.h"

#include "IEntity.h"
#include "IWorld.h"

#include "World.h"
#include "Entity.h"
#include "Component.h"
#include "Resource.h"
#include "EntityResource.h"

/// Internal
#include "EntityComponentIterator.h"
#include "EntityComponentView.h"
#include "EntityIterator.h"
#include "EntityView.h"
#include "ComponentHandle.h"

/// Manager
#include "PathManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "CameraManager.h"

/// Component
#include "Transform.h"
#include "Camera.h"
#include "Mesh.h"

/// EngineModule
#include "EngineModule.h"

#endif //IMP_ENGIME_MODULE_HEADER