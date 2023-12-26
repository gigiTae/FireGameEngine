#include "ImpGameEnginePCH.h"

/// 리플렉션한 정보를 선언하는 cpp이다. 음 구조가 이상하다고 느끼지만 어쩔수없다....

/// ========================= enum class ================================


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
REFLECTION_MEMBER(_texture)
REFLECTION_END()
