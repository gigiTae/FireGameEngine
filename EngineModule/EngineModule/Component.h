#pragma once
#include "BaseComponent.h"

namespace EngineModule
{
    class World;
    class Entity;

    /// <summary>
    /// 
    /// </summary>
    class Component :public BaseComponent
    {
    public:
        Component(World* world, Entity* entity);
        ~Component() override;

        /// <summary>
        /// Component의 초기상태를 결정한다.
        /// </summary>
        void Initialize() {};

        /// <summary>
        /// 게임 World에 들어가지전에 호출한다.
        /// </summary>
        void Start() override {};

        /// <summary>
        /// 이번 프레임의 로직을 구현.
        /// </summary>
        void Update() override {};
        
        /// <summary>
        /// Component의 상태틀 초기화한다.
        /// </summary>
        void UnInitialize() override {};

        /// <summary>
        /// World 획득
        /// </summary>
        World* GetWorld() const { return world; }

        /// <summary>
        /// Entity 획득
        /// </summary>
        Entity* GetEntity()const { return entity; }

        /// <summary>
        /// Component의 활성화 상태를 확인
        /// </summary>
        bool IsActive() const { return isActive; }

    private:
        bool isActive;
        World* world;
        Entity* entity;
    };
}