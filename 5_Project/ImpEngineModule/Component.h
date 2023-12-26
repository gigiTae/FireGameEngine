#pragma once

namespace ImpEngineModule
{
    class World;
    class Entity;

    /// <summary>
    /// Entity에 담겨서 데이터를 가지고 로직을 수행하는 객체
    /// </summary>
    class Component 
    {
        friend class Entity;

    public:
        Component();
        virtual ~Component();

        /// ===== !복사생성 반드시 정의하세요! ====== 
        virtual Component* Clone()const abstract;
        /// =======================================

        /// World와 Entity를 연결한다.
        void Set(World* world, Entity* ent);

        /// Component의 초기상태를 결정한다.
        virtual void Initialize() {};

        /// 게임 World에 들어가지전에 호출한다.
        virtual void Start() {};

        /// 이번 프레임의 로직을 구현.
        virtual void Update(float dt)  {};
        
        /// Component의 상태틀 초기화한다.
        virtual void Finalize() {};

        /// World 획득
        World* GetWorld() const { return _world; }

        /// Entity 획득
        Entity* GetEntity()const { return _entity; }

        /// Component의 활성화 상태를 확인
        bool IsActive() const { return _isActive; }


        /// 다른 컴포넌트를 가져온다.
        template<typename T>
        T* GetComponent()const;

        /// 컴포넌트를 추가한다.
        template<typename T,typename... Types>
        T* AddComponent(Types ...);

    private:
        bool _isActive;
        World* _world;
        Entity* _entity;
    };

	template<typename T, typename... Types>
	T* ImpEngineModule::Component::AddComponent(Types ...)
	{
       Entity* ent = GetEntity();

       return ent->template AddComponent<T>(Types...);
	}

	template<typename T>
	T* ImpEngineModule::Component::GetComponent() const
	{
        Entity* ent = GetEntity();
        assert(ent && "Entity가 nullptr");

        return ent->template GetComponent<T>();
	}


}