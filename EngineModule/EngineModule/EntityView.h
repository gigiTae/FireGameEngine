#pragma once

#include "EntityIterator.h"

namespace ImpEngineModule
{
	/// <summary>
	/// 
	/// </summary>
	class EntityView
	{
	public:
		EntityView(const EntityIterator& first, const EntityIterator& last);

		const EntityIterator& begin() const { return m_firstIter; }
		const EntityIterator& end() const { return m_lastIter; }

	private:
		EntityIterator m_firstIter;
		EntityIterator m_lastIter;
	};

}
