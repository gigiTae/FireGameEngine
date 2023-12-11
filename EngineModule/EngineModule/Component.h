#pragma once
#include "BaseComponent.h"

namespace ImpEngineModule
{
    class World;
    class Entity;

    /// <summary>
    /// 
    /// </summary>
    class Component :public BaseComponent
    {
    public:
        Component();
        ~Component() override;

        /// World와 Entity를 연결한다.
        void Set(World* world, Entity* ent);

        /// Component의 초기상태를 결정한다.
        virtual void Initialize() {};

        /// 게임 World에 들어가지전에 호출한다.
        virtual void Start() override {};

        /// 이번 프레임의 로직을 구현.
        virtual void Update(float dt) override {};
        
        /// Component의 상태틀 초기화한다.
        virtual void UnInitialize() {};

        /// World 획득
        World* GetWorld() const { return _world; }

        /// Entity 획득
        Entity* GetEntity()const { return _entity; }

        /// Component의 활성화 상태를 확인
        bool IsActive() const { return _isActive; }

    private:
        bool _isActive;
        World* _world;
        Entity* _entity;
    };
}