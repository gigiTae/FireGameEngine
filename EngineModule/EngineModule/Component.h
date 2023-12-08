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
        /// Component�� �ʱ���¸� �����Ѵ�.
        /// </summary>
        void Initialize() {};

        /// <summary>
        /// ���� World�� �������� ȣ���Ѵ�.
        /// </summary>
        void Start() override {};

        /// <summary>
        /// �̹� �������� ������ ����.
        /// </summary>
        void Update() override {};
        
        /// <summary>
        /// Component�� ����Ʋ �ʱ�ȭ�Ѵ�.
        /// </summary>
        void UnInitialize() override {};

        /// <summary>
        /// World ȹ��
        /// </summary>
        World* GetWorld() const { return world; }

        /// <summary>
        /// Entity ȹ��
        /// </summary>
        Entity* GetEntity()const { return entity; }

        /// <summary>
        /// Component�� Ȱ��ȭ ���¸� Ȯ��
        /// </summary>
        bool IsActive() const { return isActive; }

    private:
        bool isActive;
        World* world;
        Entity* entity;
    };
}