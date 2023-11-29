#include "EntityView.h"
#include "Entity.h"



Fire::ECS::Internal::EntityView::EntityView(const EntityIterator& first, const EntityIterator& last)
	:firstIterator(first),lastIterator(last)
{
	if (firstIterator.Get() == nullptr || (firstIterator.Get()->IsPedingDestroy() && !firstIterator.IsIncludePedingDestroy()))
	{
		++firstIterator;
	}
}
