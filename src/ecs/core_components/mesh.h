#ifndef MESH_H
#define MESH_H

#include "../entity.h"
#include "../../math/vec3f.h"

typedef struct 
{
	Vec3f* vertices;
	uint32_t verticesCount;

	uint32_t* vertex_indices;
	uint32_t vertex_indices_count;
} Mesh;

void mesh_add(Entity entity, Mesh mesh);
void mesh_remove(Entity enitty);
Mesh* mesh_get(Entity entity);

#endif