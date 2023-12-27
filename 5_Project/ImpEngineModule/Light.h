#pragma once
#include "Component.h"

namespace ImpEngineModule
{
	/// <summary>
	/// Light ÄÄÆ÷³ÍÆ® 
	/// </summary>
	class Light : public Component
	{
	public:
		enum class LightType
		{
			Point,
			Spot,
			Directional,
		};

	public:
		Light();
		~Light();

		Component* Clone()const override;

		void Update(float dt) override;


	private:
		LightType _type;
		float _intensity;
		
		REFLECTION_FRIEND(Light);
	};


}