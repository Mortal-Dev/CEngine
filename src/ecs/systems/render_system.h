#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "../../math/matrix.h"
#include "../entity.h"
#include "../core_components/mesh.h"
#include "../core_components/transform.h"
#include "../core_components/camera.h"
#include "../../gfx/renderer.h"
#include "../../core/seethe.h"

static void render_system_update(float delta_time) 
{
	Camera* camera = NULL;
	Transform* camera_transform = NULL;

	for (Entity camera_entity = 0; camera_entity < MAX_ENTITIES; camera_entity++) 
	{
		if (!entity_is_alive(camera_entity) || !entity_has_component(camera_entity, COMPONENT_CAMERA) || !entity_has_component(camera_entity, COMPONENT_TRANSFORM))
			continue;

		camera = camera_get(camera_entity);
		camera_transform = transform_get(camera_entity);
	}

	if (camera == NULL) 
	{
		log_error("Unable to find camera for render system");
		return;
	}
	
	if (camera_transform == NULL) 
	{
		log_error("Transform component must be attached to entities with a camera component");
		return;
	}

	for (Entity mesh_entity = 0; mesh_entity < MAX_ENTITIES; mesh_entity++)
	{
		if (!entity_is_alive(mesh_entity) || !entity_has_component(mesh_entity, COMPONENT_MESH) || !entity_has_component(mesh_entity, COMPONENT_TRANSFORM))
			continue;

		Mesh* mesh = mesh_get(mesh_entity);
		
		Transform* mesh_transform = transform_get(mesh_entity);

		renderer_draw_mesh(*mesh, *mesh_transform, *camera, *camera_transform);
	}
}

#endif