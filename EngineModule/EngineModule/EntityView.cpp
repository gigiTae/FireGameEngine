#include "EngineModulePCH.h"
#include "EntityView.h"




ImpEngineModule::EntityView::EntityView(const EntityIterator& first, const EntityIterator& last)
	:m_firstIter(first), m_lastIter(last)
{

}
