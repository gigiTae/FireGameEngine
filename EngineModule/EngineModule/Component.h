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

        /// <summary>
        /// World와 Entity를 연결한다.
        /// </summary>
        void Set(World* world, Entity* ent);

        /// <summary>
        /// Component의 초기상태를 결정한다.
        /// </summary>
        virtual void Initialize() {};

        /// <summary>
        /// 게임 World에 들어가지전에 호출한다.
        /// </summary>
        virtual void Start() override {};

        /// <summary>
        /// 이번 프레임의 로직을 구현.
        /// </summary>
        virtual void Update() override {};
        
        /// <summary>
        /// Component의 상태틀 초기화한다.
        /// </summary>
        virtual void UnInitialize() {};

        /// <summary>
        /// World 획득
        /// </summary>
        World* GetWorld() const { return m_world; }

        /// <summary>
        /// Entity 획득
        /// </summary>
        Entity* GetEntity()const { return m_entity; }

        /// <summary>
        /// Component의 활성화 상태를 확인
        /// </summary>
        bool IsActive() const { return m_isActive; }

    private:
        bool m_isActive;
        World* m_world;
        Entity* m_entity;
    };
}