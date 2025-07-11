#ifndef CAMERA_MOVE_SYSTEM_H
#define CAMERA_MOVE_SYSTEM_H

#include "../entity.h"
#include "../components.h"
#include "../core_components/transform.h"
#include "../../core/input.h"
#include "../../math/vec2f.h"
#include "../../core/seethe.h"
#include "../../math/math_utils.h"

static void process_move(Transform* transform, float delta_time) 
{
	Vec2f move_input = input_get_movement();

	float speed = 20.0f;  // meters per second
	float velocity = speed * delta_time;  // delta_time should be in seconds

	// Get and normalize direction vectors
	Vec3f forward = vec3f_normalized(transform->forward);
	Vec3f right = vec3f_normalized(transform->right);

	// Calculate movement in both directions
	Vec3f movement = vec3f_add(vec3f_mul_scalar(forward, move_input.y * velocity), vec3f_mul_scalar(right, move_input.x * velocity));

	// Update position
	transform->position = vec3f_add(transform->position, movement);
}

static void process_rotation(Transform* transform) 
{
	float mouse_sensitivity = 1.0f;

    Vec2f mouse_delta = input_get_mouse_delta();

    // apply mouse movement to yaw (left/right)
    transform->rotation.y += -mouse_delta.x * mouse_sensitivity;

    // normalize yaw to stay within 0-360 degrees
    /*transform->rotation.y = fmodf(transform->rotation.y, 360.0f);
    if (transform->rotation.y < 0.0f) 
	{
        transform->rotation.y += 360.0f;
    }*/

    // apply mouse movement to pitch (up/down)
    float pitch_delta = -mouse_delta.y * mouse_sensitivity;
    transform->rotation.x -= pitch_delta;

	//transform->rotation.x = clamp(transform->rotation.x, -180.0f, 90.0f);
	
}

static void camera_move_system_update(float delta_time) 
{
	for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
	{
		if (!entity_has_component(entity, COMPONENT_CAMERA) || !entity_has_component(entity, COMPONENT_CAMERA))
			continue;

		Transform* camera_transform = transform_get(entity);

		process_move(camera_transform, delta_time);
		process_rotation(camera_transform);
	}
}

#endif