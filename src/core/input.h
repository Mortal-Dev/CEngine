#ifndef INPUT_H
#define INPUT_H

#include "../math/vec2f.h"
#include <GLFW/glfw3.h>

void input_init(GLFWwindow* window_input_reference);

void input_update();

Vec2f input_get_movement();

Vec2f input_get_mouse_delta();

#endif