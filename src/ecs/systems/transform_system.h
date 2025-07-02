#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H

#include "../entity.h"
#include "../core_components/transform.h"
#include "../components.h"

static void transform_system_update() 
{
	for (Entity entity = 0; entity < MAX_ENTITIES; entity++) 
	{
		if (!entity_has_component(entity, COMPONENT_TRANSFORM)) 
		{
			continue;
		}

		Transform* transform = transform_get(entity);

		transform_update(transform);
	}
}

#endif