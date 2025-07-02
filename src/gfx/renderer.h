#ifndef RENDERER_H
#define RENDERER_H

#include "../ecs/core_components/mesh.h"
#include "../ecs/core_components/transform.h"
#include "../ecs/core_components/camera.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

GLFWwindow* renderer_init(int width, int height);

bool renderer_should_update(GLFWwindow* window);

void renderer_reset_buffer();

void renderer_update(GLFWwindow* window);

void renderer_draw_mesh(const Mesh mesh, const Transform model_transform, const Camera camera, const Transform camera_transform);

void renderer_terminate();

#endif