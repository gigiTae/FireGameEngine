#pragma once

#include "EntityIterator.h"

namespace Fire
{
	namespace ECS
	{
		namespace Internal
		{

			class EntityView
			{
			public:
				EntityView(const EntityIterator& first, const EntityIterator& last);
				
				const EntityIterator& begin() const
				{
					return firstIterator;
				}

				const EntityIterator& end() const
				{
					return lastIterator;
				}

			private:
				EntityIterator firstIterator;
				EntityIterator lastIterator;
			};

		}

	}
}

