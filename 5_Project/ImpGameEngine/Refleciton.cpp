#include "ImpGameEnginePCH.h"

/// 리플렉션한 정보를 선언하는 cpp이다. 음 구조가 이상하다고 느끼지만 어쩔수없다....

/// ========================= enum class ================================

/// LightType
REFLECTION_ENUM_BEGIN(ImpEngineModule::Light::LightType)
REFLECTION_ENUM_MEMBER(Point)
REFLECTION_ENUM_MEMBER(Spot)
REFLECTION_ENUM_MEMBER(Directional)
REFLECTION_ENUM_END()

/// ========================== struct ====================================

/// Vector3
REFLECTION_DATA_BEGIN(ImpMath::Vector3)
REFLECTION_MEMBER(x)
REFLECTION_MEMBER(y)
REFLECTION_MEMBER(z)
REFLECTION_END()

/// Vector4
REFLECTION_DATA_BEGIN(ImpMath::Vector4)
REFLECTION_MEMBER(x)
REFLECTION_MEMBER(y)
REFLECTION_MEMBER(z)
REFLECTION_MEMBER(w)
REFLECTION_END()


/// ========================== component ==================================

/// Transform
REFLECTION_BEGIN(ImpEngineModule::Transform)
REFLECTION_MEMBER(_position)
REFLECTION_MEMBER(_rotation)
REFLECTION_MEMBER(_scale)
REFLECTION_END()

/// Camera
REFLECTION_BEGIN(ImpEngineModule::Camera)
REFLECTION_MEMBER(_isMain)
REFLECTION_MEMBER(_fieldOfView)
REFLECTION_MEMBER(_nearPlain)
REFLECTION_MEMBER(_farPlain)
REFLECTION_MEMBER(_isPerspective)
REFLECTION_END()

/// Mesh
REFLECTION_BEGIN(ImpEngineModule::Mesh)
REFLECTION_MEMBER(_pixelShader)
REFLECTION_MEMBER(_vertexShader)
REFLECTION_MEMBER(_fbx)
REFLECTION_END()

/// Light
REFLECTION_BEGIN(ImpEngineModule::Light)
REFLECTION_MEMBER(_type)
REFLECTION_MEMBER(_intensity)
REFLECTION_END()