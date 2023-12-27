#pragma once
#include "Component.h"

namespace ImpEngineModule
{
	/// <summary>
	/// ��ġ, ȸ��, ũ�� ������ �����ϴ� ������Ʈ
	/// </summary>
	class Transform :
		public Component
	{
	public:
		Transform();
		~Transform() {}

		/// 
		void Update(float dt) override;

		/// ���纻�� ��ȯ�Ѵ�. 
		Component* Clone()const override;
	
	public:
		ImpMath::Vector3 GetPosition()const { return  _position; }
		void SetPosition(const ImpMath::Vector3& pos) { _position = pos; }
		void AddPosition(const ImpMath::Vector3& deltaPosition) { _position += deltaPosition; }

		ImpMath::Vector3 GetRotation()const { return _rotation; }
		void SetRotation(const ImpMath::Vector3& rotation) { _rotation = rotation; }
		void AddRotation(const ImpMath::Vector3& deltaRotation) { _rotation += deltaRotation; }
		
		ImpMath::Vector3 GetScale()const  {  return _scale; }
		void SetScale(const ImpMath::Vector3& scale) { _scale = scale; }
		void AddScale(const ImpMath::Vector3& deltaScale) { _scale += deltaScale; }

		// ��������� ��´�.
		ImpMath::Matrix GetFinalMatrix()const { return _finalMatrix; }

		// ��������� �����´�.
		ImpMath::Matrix GetLocalMatrix()const { return _localMatrix; }

		// ���� ����� ����Ѵ�.
		void UpdateLocalMatrix();

#pragma region Hierarchy

		// ���� ����� ����Ѵ�.
		void UpdateFinalMatrix();

		// �θ� Ʈ�������� ���´�.
		ImpEngineModule::Transform* GetParent() const { return _parent; }

		// �θ� �����Ѵ�.
		void SetParent(ImpEngineModule::Transform* parent);
		
		// �ڽĵ��� ���´�.
		std::vector<Transform*>& GetChildren() { return _children; }
		
		// �ڽ��� �߰��Ѵ�.
		void AddChild(Transform* addChild);

		void RemoveChild(Transform* child);

		// �θ� ������
		bool IsRoot()const { return _parent == nullptr; }

		// �ڽ��� ������
		bool IsLeaf()const { return _children.empty(); }

		// �ڽ��� ���� ������ �ִ��� Ȯ���Ѵ�.
		bool IsDescendant(Transform* transform);


#pragma endregion Hierarchy

	private:
		ImpMath::Vector3 _position = { 0.f,0.f,0.f };
		ImpMath::Vector3 _rotation = { 0.f,0.f,0.f };
		ImpMath::Vector3 _scale = { 1.f,1.f,1.f };

		ImpMath::Matrix _localMatrix; // �ڽ��� ���
		ImpMath::Matrix _finalMatrix; // �ڽ��� ������� 

		Transform* _parent;
		std::vector<Transform*> _children;

		// ���÷��� ����
		REFLECTION_FRIEND(Transform)
	};
}