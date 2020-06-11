#include "entity.h"

#include "entity_composition.h"
#include "../components/movement_component.h"

Entity::Entity(
	std::shared_ptr<EntityComposition> group,
	std::shared_ptr<MovementComponent> globalMovementComponent)
	: group(group),
	globalMovementComponent(globalMovementComponent)
{}
