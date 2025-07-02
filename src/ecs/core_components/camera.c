#include "camera.h"
#include "../components.h"
#include "../../math/vec3f.h"
#include "../../math/matrix.h"

Camera cameras[MAX_ENTITIES];

void camera_add(Entity entity, Camera camera)
{
	if (entity_has_component(entity, COMPONENT_CAMERA))
	{
		return;
	}

	entity_add_component(entity, COMPONENT_CAMERA);

	cameras[entity] = camera;
}

void camera_remove(Entity entity)
{
	if (entity_has_component(entity, COMPONENT_CAMERA))
	{
		entity_remove_component(entity, COMPONENT_CAMERA);
	}
}

Camera* camera_get(Entity entity)
{
	if (entity_has_component(entity, COMPONENT_CAMERA))
	{
		return &cameras[entity];
	}
	else
	{
		return NULL;
	}
}

void camera_process_keyboard(const Camera* camera, Transform* camera_transform, const char direction, const float delta_time)
{
	float velocity = camera->speed * delta_time;

	// foward
	if (direction == 'W') 
	{
		camera_transform->position.x += camera_transform->forward.x * velocity;
		camera_transform->position.y += camera_transform->forward.y * velocity;
		camera_transform->position.z += camera_transform->forward.z * velocity;
	}

	//backwards
	if (direction == 'S') 
	{
		camera_transform->position.x -= camera_transform->forward.x * velocity;
		camera_transform->position.y -= camera_transform->forward.y * velocity;
		camera_transform->position.z -= camera_transform->forward.z * velocity;
	}

	//left
	if (direction == 'A') 
	{
		camera_transform->position.x -= camera_transform->forward.x * velocity;
		camera_transform->position.y -= camera_transform->forward.y * velocity;
		camera_transform->position.z -= camera_transform->forward.z * velocity;
	}

	//right
	if (direction == 'D') 
	{
		camera_transform->position.x += camera_transform->forward.x * velocity;
		camera_transform->position.y += camera_transform->forward.y * velocity;
		camera_transform->position.z += camera_transform->forward.z * velocity;
	}
}
