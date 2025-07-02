#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>
#include <stdbool.h>

#define MAX_ENTITIES 100
#define MAX_COMPONENTS 32
#define INVALID_ENTITY ((Entity)0xFFFFFFFF)

// Type alias for entity IDs
typedef uint32_t Entity;

void entity_init(void);
Entity entity_create(void);
void entity_destroy(Entity entity);
bool entity_is_alive(Entity entity);

void entity_add_component(Entity entity, uint16_t component_id);
void entity_remove_component(Entity entity, uint16_t component_id);
bool entity_has_component(Entity entity, uint16_t component_id);
#endif //ENTITY_H