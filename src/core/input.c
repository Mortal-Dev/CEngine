#include "input.h"
#include "../math/math_utils.h"

Vec2f movement_vector;
Vec2f mouse_delta;

Vec2f last_mouse_pos;

GLFWwindow* input_window;

void on_move_input(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (key == GLFW_KEY_W)
	{
		movement_vector.y += action == GLFW_PRESS ? 1.0f : action == GLFW_RELEASE ? -1.0f : 0.0f;
	}
	else if (key == GLFW_KEY_S) 
	{
		movement_vector.y -= action == GLFW_PRESS ? 1.0f : action == GLFW_RELEASE ? -1.0f : 0.0f;
	}
	else if (key == GLFW_KEY_D)
	{
		movement_vector.x += action == GLFW_PRESS ? 1.0f : action == GLFW_RELEASE ? -1.0f : 0.0f;
	}
	else if (key == GLFW_KEY_A) 
	{
		movement_vector.x -= action == GLFW_PRESS ? 1.0f : action == GLFW_RELEASE ? -1.0f : 0.0f;
	}

	movement_vector.x = clamp(movement_vector.x, -1.0f, 1.0f);
	movement_vector.y = clamp(movement_vector.y, -1.0f, 1.0f);
}

void input_init(GLFWwindow* window_input_reference)
{
	glfwSetKeyCallback(window_input_reference, on_move_input);

	input_window = window_input_reference;
}

void input_update()
{
	double xpos, ypos;
	glfwGetCursorPos(input_window, &xpos, &ypos);

	int width, height;
	glfwGetWindowSize(input_window, &width, &height);

	xpos = (double)normalize_range((float)xpos, 0.0f, (float)width, 0.0f, 1.0f);
	ypos = 1.0f - (double)normalize_range((float)ypos, 0.0f, (float)height, 0.0f, 1.0f);

	mouse_delta.x = (float)xpos - last_mouse_pos.x;
	mouse_delta.y = (float)ypos - last_mouse_pos.y;

	last_mouse_pos.x = (float)xpos;
	last_mouse_pos.y = (float)ypos;
}

Vec2f input_get_movement()
{
	return movement_vector;
}

Vec2f input_get_mouse_delta()
{
	return mouse_delta;
}