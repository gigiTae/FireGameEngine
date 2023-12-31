#pragma once
#include "Component.h"

namespace ImpEngineModule
{

	/// <summary>
	/// Camera 컴포넌트
	/// 
	/// </summary>successed
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

		Component* Clone()const override;

		void Update(float dt) override;

		/// 메인 카메라로 설정한다.
		void OnMainCamera();

		/// 메인 카메라 끄기
		void OffMainCamera(){ _isMain = false; }
		 
		/// 메인 카메라인지
		bool IsMain()const { return _isMain; }

		void Strafe(float distance);
		void Walk(float distance);
		void WorldUpDown(float distance);

		void Yaw(float angle);
		void Pitch(float angle);
		void Roll(float angle);

		float GetFieldOfView()const  { return _fieldOfView; }
		void SetFieldOfView(float val) { _fieldOfView = val; }
		float GetNearPlain() const { return _nearPlain; }
		void SetNearPlain(float val) { _nearPlain = val; }
		float GerFarPlain()const { return _farPlain; }
		void SetFarPlain(float val) { _farPlain = val; }
		bool IsPerspective()const { return _isPerspective; }

	private:
		bool _isMain = false;
		float _fieldOfView = 0.25*3.14f;
		float _nearPlain = 0.3f;
		float _farPlain = 1000.f;
		bool _isPerspective = true;

		ImpMath::Matrix _rotMatrix;

		REFLECTION_FRIEND(ImpEngineModule::Camera)
	};


}