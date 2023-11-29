#pragma once

#include "Entity.h"

namespace Fire
{
	namespace ECS
	{
		namespace Internal
		{
			template<typename... Types>
			class EntityComponentIterator;

			template<typename... Types>
			class EntityComponentView
			{
			public:
				EntityComponentView(const EntityComponentIterator<Types...>& first, const EntityComponentIterator<Types...>& last);

				/// <summary>
				/// range-for문은 begin,end 함수 이름으로 찾는다.
				/// </summary>
				const EntityComponentIterator<Types...>& begin() const
				{
					return firstIterator;
				}

				const EntityComponentIterator<Types...>& end() const
				{
					return lastIterator;
				}


			private:
				EntityComponentIterator<Types...> firstIterator;
				EntityComponentIterator<Types...> lastIterator;
			};

			template<typename ...Types>
			inline EntityComponentView<Types...>::EntityComponentView(const EntityComponentIterator<Types...>& first, const EntityComponentIterator<Types...>& last)
				:firstIterator(first),lastIterator(last)
			{
				if (firstIterator.Get() == nullptr || (firstIterator.Get()->IsPedingDestroy() && !firstIterator.IsIncludePedingDestroy())
					|| !firstIterator.Get()->template Has<Types...>())
				{
					++firstIterator;
				}
			}
		}

	}

}

