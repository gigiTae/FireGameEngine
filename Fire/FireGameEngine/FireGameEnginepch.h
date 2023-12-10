#pragma once


#include <string>
#include <assert.h>
#include <Windows.h>
#include "ExportDefine.h"

#ifndef HEADER_INCLUDE
#define HEADER_INCLUDE

#include "../EntityComponentSystem/ComponentHeader.h"
#include "../EntityComponentSystem/ECSHeader.h"
#include "../EntityComponentSystem/ReflectionHeader.h"
#include "../RendererModule/RendererHeader.h"

#endif // !HEADER_INCLUDE


#ifdef EDITOR_MODE
#include "ToolModule/ToolModuleHeader.h"
#endif
