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

        /// World�� Entity�� �����Ѵ�.
        void Set(World* world, Entity* ent);

        /// Component�� �ʱ���¸� �����Ѵ�.
        virtual void Initialize() {};

        /// ���� World�� �������� ȣ���Ѵ�.
        virtual void Start() override {};

        /// �̹� �������� ������ ����.
        virtual void Update(float dt) override {};
        
        /// Component�� ����Ʋ �ʱ�ȭ�Ѵ�.
        virtual void UnInitialize() {};

        /// World ȹ��
        World* GetWorld() const { return _world; }

        /// Entity ȹ��
        Entity* GetEntity()const { return _entity; }

        /// Component�� Ȱ��ȭ ���¸� Ȯ��
        bool IsActive() const { return _isActive; }

    private:
        bool _isActive;
        World* _world;
        Entity* _entity;
    };
}