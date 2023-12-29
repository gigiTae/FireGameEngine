#include "pch.h"

#include "ImpGraphicsEngine.h"

namespace ImpGraphics
{
	IImpGraphicsEngine* EngineExporter::GetEngine()
	{
		_engine = new ImpGraphicsEngine;
		return _engine;
	}

	void EngineExporter::DeleteEngine()
	{
		delete _engine;
	}

	ImpGraphics::IImpGraphicsEngine* EngineExporter::_engine = nullptr;
}