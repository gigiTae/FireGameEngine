#include "EngineModulePCH.h"
#include "Transform.h"
#include "InputManager.h"

ImpEngineModule::Transform::Transform() :_parent(nullptr), _children{},
_finalMatrix{}, _localMatrix{}
{}

void ImpEngineModule::Transform::Update(float dt)
{
	// �ֻ��� �θ� ������Ѵ�.
	if (!IsRoot())
	{
		return;
	}

	std::queue<Transform*> q;
	q.push(this);

	while (!q.empty())
	{
		Transform* transform = q.front();
		transform->UpdateLocalMatrix();
		transform->UpdateFinalMatrix();

		// �ڽ��� �ִٸ� ť�� �߰��Ѵ�.
		if (!transform->IsLeaf())
		{
			for (Transform* child : transform->GetChildren())
			{
				q.push(child);
			}
		}

		q.pop();
	}
}

ImpEngineModule::Component* ImpEngineModule::Transform::Clone() const
{
	Transform* clone = new Transform();

	clone->_position = _position;
	clone->_rotation = _rotation;
	clone->_scale = _scale;

	// �θ� �ڽİ���� �������� �ʴ´�.
	clone->_localMatrix = _localMatrix;
	clone->_finalMatrix = _localMatrix;

	clone->_children = {};
	clone->_parent = nullptr;

	return clone;
}

void ImpEngineModule::Transform::UpdateLocalMatrix()
{
	using namespace ImpMath;

	Matrix rot = Matrix::MakeRotationMatrixRollPitchYaw(_rotation);
	Matrix scale = Matrix::MakeScaleMatrix(_scale);
	Matrix translation = Matrix::MakeTranslationMatrix(_position);

	// SRT
	_localMatrix = scale * rot * translation;
}

void ImpEngineModule::Transform::UpdateFinalMatrix()
{
	if (IsRoot())
	{
		_finalMatrix = _localMatrix;
	}
	else
	{
		ImpMath::Matrix parentMatrix = _parent->GetFinalMatrix();
		_finalMatrix = _localMatrix * parentMatrix;
	}
}

void ImpEngineModule::Transform::SetParent(ImpEngineModule::Transform* parent)
{
	if (parent == _parent || parent == this)
	{
		return;
	}

	_parent = parent;

	if (_parent != nullptr)
	{
		_parent->AddChild(this);
	}
}

void ImpEngineModule::Transform::AddChild(Transform* addChild)
{
	if (addChild == this)
	{
		return;
	}

	for (Transform* child : _children)
	{
		if (addChild == child)
		{
			return;
		}
	}

	Transform* prevParent = addChild->GetParent();

	if (prevParent != nullptr)
	{
		prevParent->RemoveChild(addChild);
	}

	_children.push_back(addChild);

	addChild->SetParent(this);
}

void ImpEngineModule::Transform::RemoveChild(Transform* child)
{
	// �ڽĸ�Ͽ��� �����Ѵ�.
	_children.erase(std::remove(_children.begin(), _children.end(), child), _children.end());

	// �ڽ��� �θ� ������ �����Ѵ�.
	child->SetParent(nullptr);
}

bool ImpEngineModule::Transform::IsDescendant(Transform* transform)
{
	std::queue<Transform*> q;

	q.push(this);

	while (!q.empty())
	{
		Transform* tmp = q.front();
		q.pop();
		
		if (tmp == transform)
		{
			return true;
		}

		if (!tmp->IsLeaf())
		{
			for (Transform* child : tmp->GetChildren())
			{
				q.push(child);
			}
		}
	}

	return false;
}
