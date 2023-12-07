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

        void Initialize() {};

        void Start() override {};

        void Update() override {};
        
        void UnInitialize() override {};

        World* GetWorld() const { return world; }

        Entity* GetEntity()const { return entity; }

        bool IsActive() const { return isActive; }

    private:
        bool isActive;
        World* world;
        Entity* entity;
    };
}