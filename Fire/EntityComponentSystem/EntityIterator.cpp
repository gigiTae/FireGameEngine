#include "EntityIterator.h"
#include "World.h"
#include "Entity.h"

Fire::ECS::Internal::EntityIterator::EntityIterator
(World* world, size_t index, bool isEnd, bool isIncludePendingDestroy)
    :world(world) , index(index), isEnd(isEnd), isIncludePedingDestroy(isIncludePedingDestroy)
{
    if (index >= world->GetCount())
        this->isEnd = true;
}

bool Fire::ECS::Internal::EntityIterator::IsEnd() const
{
    return isEnd || index >= world->GetCount();
}

Fire::ECS::Entity* Fire::ECS::Internal::EntityIterator::Get() const
{
    if (IsEnd())
        return nullptr;

    return world->GetByIndex(index);
}

Fire::ECS::Internal::EntityIterator& Fire::ECS::Internal::EntityIterator::operator++()
{
    ++index;
    while (index < world->GetCount() && (Get() == nullptr || (Get()->IsPedingDestroy() && !isIncludePedingDestroy)))
    {
        ++index;
    }

    if (index >= world->GetCount())
        isEnd = true;

    return *this;
}
