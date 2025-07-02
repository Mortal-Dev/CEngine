#include "entity.h"
#include <string.h>

static bool alive[MAX_ENTITIES];
static bool component_table[MAX_ENTITIES][MAX_COMPONENTS];

static Entity next_entity = 0;

void entity_init(void)
{
	memset(alive, 0, sizeof(alive));
	memset(component_table, 0, sizeof(component_table));
	next_entity = 0;
}

Entity entity_create(void) 
{
	for (Entity entity = next_entity; entity < MAX_ENTITIES; ++entity) 
	{
		if (alive[entity]) 
		{
			continue;
		}

		alive[entity] = true;
		memset(component_table[entity], 0, sizeof(component_table[entity]));
		next_entity = entity + 1;
		return entity;
	}

	return INVALID_ENTITY;
}

void entity_destroy(Entity entity) 
{
	if (entity >= MAX_ENTITIES) 
	{
		return;
	}

	alive[entity] = false;
	memset(component_table[entity], 0, sizeof(component_table[entity]));

	if (entity < next_entity) 
	{
		next_entity = entity;
	}
}

bool entity_is_alive(Entity entity) 
{
	return entity < MAX_ENTITIES && alive[entity];
}

void entity_add_component(Entity entity, uint16_t component_id) 
{
	if (entity_is_alive(entity) && component_id < MAX_COMPONENTS) 
	{
		component_table[entity][component_id] = true;
	}
}

void entity_remove_component(Entity entity, uint16_t component_id) 
{
	if (entity_is_alive(entity) && component_id < MAX_COMPONENTS) 
	{
		component_table[entity][component_id] = false;
	}
}

bool entity_has_component(Entity entity, uint16_t component_id) 
{
	return entity_is_alive(entity) && component_id < MAX_COMPONENTS && component_table[entity][component_id];
}