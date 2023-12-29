#include "ImpGameEnginePCH.h"
#include "RenderingSystem.h"
#include "../ImpGraphicsEngine/ImpGraphicsEngine.h"

ImpGameEngine::RenderingSystem::RenderingSystem()
	:_graphicsEngine(nullptr), _engineModule(nullptr)
{

}

ImpGameEngine::RenderingSystem::~RenderingSystem()
{

}

void ImpGameEngine::RenderingSystem::Initialize(ImpGraphics::IImpGraphicsEngine* graphics, ImpEngineModule::EngineModule* module)
{
	using namespace ImpEngineModule;

	_graphicsEngine = graphics;
	_engineModule = module;

	EventManager* eventMgr = _engineModule->GetEventManager();
	eventMgr->SubScribe<Event::OnEntityCreated>(this);
	eventMgr->SubScribe<Event::OnEntityStarted>(this);
	eventMgr->SubScribe<Event::OnEntityDestroyed>(this);
}

void ImpGameEngine::RenderingSystem::Update()
{
	using namespace ImpEngineModule;
	World* world = _engineModule->GetWorld();

	world->Each<Transform, Mesh>([this](Entity* ent, ComponentHandle<Transform> transform, ComponentHandle<Mesh> mesh)
		{
			if (mesh->IsBindGraphics())
			{
				_graphicsEngine->SetMeshObject(ent->GetID(), transform->GetFinalMatrix());
			}

		}, false);
}

void ImpGameEngine::RenderingSystem::Finalize()
{
	using namespace ImpEngineModule;

	EventManager* eventMgr = _engineModule->GetEventManager();
	eventMgr->UnSubScribe<Event::OnEntityCreated>(this);
	eventMgr->UnSubScribe<Event::OnEntityStarted>(this);
	eventMgr->UnSubScribe<Event::OnEntityDestroyed>(this);
}

void ImpGameEngine::RenderingSystem::Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityCreated& event)
{

}

void ImpGameEngine::RenderingSystem::Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityStarted& event)
{
	using namespace ImpEngineModule;

	// 그래픽스 엔진에 생성정보를 전달한다.
	Entity* ent = event.entity;

	// 메쉬정보 전달
	if (ent->HasComponent<Mesh>())
	{
		_graphicsEngine->DeleteMeshObject(ent->GetID());
		Mesh* mesh = ent->GetComponent<Mesh>();

		ImpGraphics::MeshObjectInfo info{};
		info._objectID = ent->GetID();
		info._meshPath = mesh->GetFBXPath();
		info._pisxelShaderPath = mesh->GetPixelShaderPath();
		info._vertexShaderPath = mesh->GetVertexShaderPath();

		// 만약에 정보가 없으면 바인딩 하지 않는다.
		if (info._meshPath.empty() || info._pisxelShaderPath.empty() ||
			info._vertexShaderPath.empty())
		{
			return;
		}

		// 그래픽스 엔진에 바인딩한다.
		mesh->SetBindGraphics(true);
		_graphicsEngine->AddMeshObejct(info);
	}

}

void ImpGameEngine::RenderingSystem::Receive(ImpEngineModule::World* world, const ImpEngineModule::Event::OnEntityDestroyed& event)
{
	using namespace ImpEngineModule;

	// 그래픽스 엔진에 소멸정보를 전달한다.
	Entity* ent = event.entity;

	// 메쉬삭제 요청
	if (ent->HasComponent<Mesh>())
	{
		_graphicsEngine->DeleteMeshObject(ent->GetID());
	}

}

