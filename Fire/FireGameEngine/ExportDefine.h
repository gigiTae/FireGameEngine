#pragma once

#ifdef FIRE_GAME_ENGINE_DLL_EXPROTS
#define FIRE_ENGNIE_API __declspec(dllexport)
#else
#define FIRE_ENGNIE_API __declspec(dllimport)
#endif

#ifdef FIRE_GAME_ENGINE_DLL_EXPROTS
#define FIRE_ENGNIE_TEMPLATE_API __declspec(dllexport)
#else
#define FIRE_ENGNIE_TEMPLATE_API __declspec(dllimport)
#endif
