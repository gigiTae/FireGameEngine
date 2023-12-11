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
        /// World�� Entity�� �����Ѵ�.
        /// </summary>
        void Set(World* world, Entity* ent);

        /// <summary>
        /// Component�� �ʱ���¸� �����Ѵ�.
        /// </summary>
        virtual void Initialize() {};

        /// <summary>
        /// ���� World�� �������� ȣ���Ѵ�.
        /// </summary>
        virtual void Start() override {};

        /// <summary>
        /// �̹� �������� ������ ����.
        /// </summary>
        virtual void Update() override {};
        
        /// <summary>
        /// Component�� ����Ʋ �ʱ�ȭ�Ѵ�.
        /// </summary>
        virtual void UnInitialize() {};

        /// <summary>
        /// World ȹ��
        /// </summary>
        World* GetWorld() const { return m_world; }

        /// <summary>
        /// Entity ȹ��
        /// </summary>
        Entity* GetEntity()const { return m_entity; }

        /// <summary>
        /// Component�� Ȱ��ȭ ���¸� Ȯ��
        /// </summary>
        bool IsActive() const { return m_isActive; }

    private:
        bool m_isActive;
        World* m_world;
        Entity* m_entity;
    };
}