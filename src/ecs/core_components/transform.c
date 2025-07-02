#include "transform.h"
#include "../components.h"
#include <stdbool.h>
#include "../../math/matrix.h"

Transform transforms[MAX_ENTITIES];

void transform_add(Entity entity, Transform transform) 
{
	if (entity_has_component(entity, COMPONENT_TRANSFORM)) 
	{
		return;
	}

	entity_add_component(entity, COMPONENT_TRANSFORM);

	transforms[entity] = transform;
}

void transform_remove(Entity entity) 
{
	if (entity_has_component(entity, COMPONENT_TRANSFORM))
	{
		entity_remove_component(entity, COMPONENT_TRANSFORM);
	}
}

Transform* transform_get(Entity entity)
{
	if (entity_has_component(entity, COMPONENT_TRANSFORM))
	{
		return &transforms[entity];
	}
	else 
	{
		return NULL;
	}
}

static void extract_basis_vectors(const Mat4 rotation, Vec3f* right, Vec3f* up, Vec3f* forward) 
{
	// Right vector (first column)
	right->x = rotation.m[0][0];
	right->y = rotation.m[1][0];
	right->z = rotation.m[2][0];

	// Up vector (second column)
	up->x = rotation.m[0][1];
	up->y = rotation.m[1][1];
	up->z = rotation.m[2][1];

	// Forward vector (third column)
	forward->x = rotation.m[0][2];
	forward->y = rotation.m[1][2];
	forward->z = rotation.m[2][2];
}


void transform_update(Transform* transform)
{
	Mat4 rotation = mat4_from_euler(transform->rotation.x, transform->rotation.y, transform->rotation.z);// mat4_euler_to_rotation_matrix(transform->rotation.z, transform->rotation.y, transform->rotation.x);

	Vec3f right, up, forward;

	extract_basis_vectors(rotation, &right, &up, &forward);

	transform->right = right;
	transform->up = up;
	transform->forward = forward;
}
