#include "core/seethe.h"
#include "core/file.h"
#include "resources/mesh_loader.h"
#include "ecs/core_components/mesh.h"
#include "ecs/components.h"
#include "ecs/systems/render_system.h"
#include "ecs/systems/transform_system.h"
#include "ecs/systems/camera_move_system.h"
#include "core/stopwatch.h"
#include "gfx/renderer.h"
#include <Windows.h>

static void delay_to_target_frame_rate(float delta_time, uint32_t target_frame_rate)
{
    float target_frame_time = 1.0f / (float)target_frame_rate;

    if (delta_time < target_frame_time) 
    {
        Sleep((unsigned long)((target_frame_time * 1000.0f) - (delta_time * 1000.0f)));
    }
}

static void update_systems(float delta_time) 
{
    transform_system_update();
    camera_move_system_update(delta_time);
    render_system_update(delta_time);
}

int main(void)
{
    uint32_t target_frame_rate = 60u;
    Stopwatch stopwatch = { 0 };
    float delta_time = 0.0f;

    //create/load mesh entity
    char* obj_file_data = file_read_local("/Assets/Models/cube.obj");
    Mesh mesh = mesh_load_obj(obj_file_data);
    free(obj_file_data);
    Transform mesh_transform = { 0 };
    mesh_transform.position = (Vec3f){ 0.0f, 0.0f, 5.0f };
    mesh_transform.scale = (Vec3f){ 1.0f, 1.0f, 1.0f };
    Entity mesh_entity = entity_create();
    mesh_add(mesh_entity, mesh);
    transform_add(mesh_entity, mesh_transform);

    //create camera entity
    Camera camera = { 0 };
    camera.fov = 80.0f;
    camera.near_plane = 0.1f;
    camera.far_plane = 100.0f;
    camera.aspect = 1280.0f / 960.0f;
    Transform camera_transform = { 0 };
    camera_transform.position = (Vec3f){ 0.0f, 0.0f, 0.0f };
    transform_update(&camera_transform);
    Entity camera_entity = entity_create();
    camera_add(camera_entity, camera);
    transform_add(camera_entity, camera_transform);

    transform_update(&camera_transform);

    GLFWwindow* window = renderer_init(1280, 960);

    input_init(window);

    /* Loop until the user closes the window */
    while (renderer_should_update(window))
    {
        stopwatch_start(&stopwatch);

        renderer_reset_buffer();

        input_update();

        //update systems
        update_systems(delta_time);

        renderer_update(window);

        delta_time = stopwatch_stop(&stopwatch);
        delay_to_target_frame_rate(delta_time, target_frame_rate);
    }

    renderer_terminate();
    return 0;
}