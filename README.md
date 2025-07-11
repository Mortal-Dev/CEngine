Barebones 3D Renderer (C + OpenGL)
==================================

A very minimal 3D rendering engine written in C using OpenGL.

> This project was created as a way to refresh myself with C programming and revisit the fundamentals of real-time rendering and ECS architecture.

Features
--------

- Triangulated .obj file support (no materials or textures)
- Lightweight ECS architecture with transform, camera, and mesh components
- Basic camera movement system
- Wireframe/solid rendering via OpenGL
- Simple frame rate limiter

Not Included
------------

This project does NOT support:
- Textures
- Materials (MTL)
- Lighting
- Skeletal animation
- Complex .obj features

Project Structure
-----------------

core/
    seethe.h           - Logging/debugging
    file.h             - File utilities
    stopwatch.h        - Simple timer

gfx/
    renderer.h         - OpenGL rendering backend

resources/
    mesh_loader.h      - .obj mesh loader

ecs/
    core_components/   - Basic ECS components like mesh
    components.h       - Component definitions
    systems/           - Update systems (render, transform, camera)

Main Loop Example
-----------------

while (renderer_should_update(window))
{
    stopwatch_start(&stopwatch);
    renderer_reset_buffer();
    input_update();
    update_systems(delta_time);
    renderer_update(window);
    delta_time = stopwatch_stop(&stopwatch);
    delay_to_target_frame_rate(delta_time, target_frame_rate);
}

Building
--------

This project currently supports Windows (uses <Windows.h> for timing). Requires:

- GLFW for windowing/input
- OpenGL 3.x+
- C compiler (tested with MSVC)

Loading a Mesh
--------------

char* obj_file_data = file_read_local("/Assets/Models/cube.obj");
Mesh mesh = mesh_load_obj(obj_file_data);
free(obj_file_data);

Goals
-----

This renderer is not meant to be a full engine. It’s a barebones playground designed to:

- Reinforce C fundamentals
- Teach core rendering loop concepts
- Showcase ECS in C
