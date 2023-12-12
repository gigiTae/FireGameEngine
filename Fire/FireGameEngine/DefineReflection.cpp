
#include "FireGameEnginepch.h"


#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Name)
BEGIN_REFLECTION(Fire::Component::Name)
MEMBER_REFLECTION(name)
MEMBER_REFLECTION(category)
MEMBER_REFLECTION(vecI)
END_REFLECTION()

#endif

#ifdef REFLECTION_PROJECT

REFLECT_CHECK_ENUM(OBJECT_TYPE)
BEGIN_REFLECTION_ENUM(OBJECT_TYPE)
ENUM_MEMBER_REFLECTION(CAMERA)
ENUM_MEMBER_REFLECTION(MESH)
ENUM_MEMBER_REFLECTION(LIGHT)
ENUM_MEMBER_REFLECTION(NONE)
END_REFLECTION_ENUM()

#endif // REFLE

#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::SphereMesh)
BEGIN_REFLECTION(Fire::Component::SphereMesh)
MEMBER_REFLECTION(r)
MEMBER_REFLECTION(g)
MEMBER_REFLECTION(b)
MEMBER_REFLECTION(a)
END_REFLECTION()

#endif


#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Vector3)
BEGIN_REFLECTION(Fire::Component::Vector3)
MEMBER_REFLECTION(x)
MEMBER_REFLECTION(y)
MEMBER_REFLECTION(z)
END_REFLECTION()

#endif

#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Transform)
BEGIN_REFLECTION(Fire::Component::Transform)
MEMBER_REFLECTION(position)
MEMBER_REFLECTION(rotation)
MEMBER_REFLECTION(scale)
END_REFLECTION()

#endif


#ifdef REFLECTION_PROJECT

REFLECT_CHECK(Fire::Component::Camera)
BEGIN_REFLECTION(Fire::Component::Camera)
MEMBER_REFLECTION(isMain)
MEMBER_REFLECTION(cameraSpeed)
MEMBER_REFLECTION(sensitivity)
END_REFLECTION()

#endif 

