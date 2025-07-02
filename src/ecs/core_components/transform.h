#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../../math/vec3f.h"
#include "../entity.h"

typedef struct
{
	Vec3f position;
	Vec3f rotation;
	Vec3f scale;

	Vec3f up;
	Vec3f right;
	Vec3f forward;
} Transform;

void transform_add(Entity entity, Transform transform);
void transform_remove(Entity entity);
Transform* transform_get(Entity entity);

void transform_update(Transform* transform);

#endif //TRANSFORM_H
