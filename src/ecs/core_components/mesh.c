#include "mesh.h"
#include "../components.h"

Mesh meshes[MAX_ENTITIES];

void mesh_add(Entity entity, Mesh mesh) 
{
	if (entity_has_component(entity, COMPONENT_MESH))
	{
		return;
	}

	entity_add_component(entity, COMPONENT_MESH);

	meshes[entity] = mesh;
}

void mesh_remove(Entity entity) 
{
	if (entity_has_component(entity, COMPONENT_MESH))
	{
		entity_remove_component(entity, COMPONENT_MESH);
	}
}

Mesh* mesh_get(Entity entity) 
{
	if (entity_has_component(entity, COMPONENT_MESH)) 
	{
		return &meshes[entity];
	}
	else 
	{
		return NULL;
	}
}