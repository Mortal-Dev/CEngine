#ifndef CAMERA_H
#define CAMERA_H

#include "../entity.h"
#include "transform.h"

typedef struct
{
	float speed;
	float sensitivity;

	float fov;
	float aspect;

	float near_plane;
	float far_plane;
} Camera;

void camera_add(Entity entity, Camera camera);
void camera_remove(Entity entity);
Camera* camera_get(Entity entity);

void camera_process_keyboard(const Camera* camera, Transform* camera_transform, const char direction, const float delta_time);

#endif