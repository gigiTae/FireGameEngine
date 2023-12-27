#pragma once
#include "Component.h"

namespace ImpEngineModule
{
	/// <summary>
	/// 위치, 회전, 크기 정보를 관리하는 컴포넌트
	/// </summary>
	class Transform :
		public Component
	{
	public:
		Transform();
		~Transform() {}

		/// 
		void Update(float dt) override;

		/// 복사본을 반환한다. 
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

		// 최종행렬을 얻는다.
		ImpMath::Matrix GetFinalMatrix()const { return _finalMatrix; }

		// 로컬행렬을 가져온다.
		ImpMath::Matrix GetLocalMatrix()const { return _localMatrix; }

		// 로컬 행렬을 계산한다.
		void UpdateLocalMatrix();

#pragma region Hierarchy

		// 최종 행렬을 계산한다.
		void UpdateFinalMatrix();

		// 부모 트랜스폼은 얻어온다.
		ImpEngineModule::Transform* GetParent() const { return _parent; }

		// 부모를 설정한다.
		void SetParent(ImpEngineModule::Transform* parent);
		
		// 자식들을 얻어온다.
		std::vector<Transform*>& GetChildren() { return _children; }
		
		// 자식을 추가한다.
		void AddChild(Transform* addChild);

		void RemoveChild(Transform* child);

		// 부모가 없는지
		bool IsRoot()const { return _parent == nullptr; }

		// 자식이 없는지
		bool IsLeaf()const { return _children.empty(); }

		// 자신의 하위 계층이 있는지 확인한다.
		bool IsDescendant(Transform* transform);


#pragma endregion Hierarchy

	private:
		ImpMath::Vector3 _position = { 0.f,0.f,0.f };
		ImpMath::Vector3 _rotation = { 0.f,0.f,0.f };
		ImpMath::Vector3 _scale = { 1.f,1.f,1.f };

		ImpMath::Matrix _localMatrix; // 자신의 행렬
		ImpMath::Matrix _finalMatrix; // 자신의 최종행렬 

		Transform* _parent;
		std::vector<Transform*> _children;

		// 리플렉션 선언
		REFLECTION_FRIEND(Transform)
	};
}