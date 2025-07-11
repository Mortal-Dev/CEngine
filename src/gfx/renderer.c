#include "renderer.h"
#include "shaders.h"
#include "../core/seethe.h"
#include "../core/file.h"
#include "../math/matrix.h"
#include <string.h>
#include <stdio.h>

static GLuint vertex_shader;
static GLuint fragment_shader;

static GLuint program;

static uint32_t vertexArray;
static uint32_t vertexBuffer;
static uint32_t indexBuffer;

static void glfw_error_callback(int error_code, const char* description)
{
    char errorMessage[256];

    sprintf_s(errorMessage, sizeof(errorMessage), "GLFW Error: %d\n%s", error_code, description);

    log_error(errorMessage);
}

static void print_glfw_version()
{
    int major = 0;
    int minor = 0;
    int rev = 0;
    glfwGetVersion(&major, &minor, &rev);

    char message[128];
    sprintf_s(message, sizeof(message), "GLFW Version: %d.%d.%d", major, minor, rev);

    log_notice(message);
}

GLFWwindow* renderer_init(int width, int height)
{
    print_glfw_version();

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        log_error("Failed to initialize GLFW\n");
        return NULL;
    }

    // Set GLFW error callback
    glfwSetErrorCallback(glfw_error_callback);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "CEngine", NULL, NULL);
    if (!window)
    {
        log_error("Failed to create window\n");
        glfwTerminate();
        return NULL;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // init GLEW
    if (glewInit() != GLEW_OK) 
    {
        log_error("Failed to init GLEW");
        glfwTerminate();
        return NULL;
    }

    // init shaders
    program = create_shader_program("/Assets/Shaders/vertex.glsl", "/Assets/Shaders/fragment.glsl");
    if (program == 0) 
    {
        log_error("Failed to create shader program");
        glfwTerminate();
        return NULL;
    }

    //generate arrays/buffers
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    glGenBuffers(1, &indexBuffer);

    glBindVertexArray(vertexArray);

    glBindVertexArray(vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), (void*)0);
    glEnableVertexAttribArray(0);

    //enable depth testing
    glEnable(GL_DEPTH_TEST);

	return window;
}

bool renderer_should_update(GLFWwindow* window)
{
    return !glfwWindowShouldClose(window);
}

void renderer_reset_buffer() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
}

void renderer_update(GLFWwindow* window) 
{
    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}

void renderer_draw_mesh(const Mesh mesh, const Transform model_transform, const Camera camera, const Transform camera_transform)
{
    //setup model * view * matrix variable
    // build the model matrix
    Mat4 model = mat4_identity();
    model = mat4_scale(model, model_transform.scale);
    model = mat4_rotate_x(model, model_transform.rotation.x);
    model = mat4_rotate_y(model, model_transform.rotation.y);
    model = mat4_rotate_z(model, model_transform.rotation.z);
    model = mat4_translate(model, model_transform.position);

    // create view and projection matrices
    Mat4 view = mat4_look_at(camera_transform.position, camera_transform.forward, camera_transform.up);
    Mat4 projection = mat4_perspective(camera.fov, camera.aspect, camera.near_plane, camera.far_plane);

    //assign model matrix
	GLint modelLocation = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model.m[0][0]);

    //assign view matrix
	GLint viewLocation = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view.m[0][0]);

	GLint projectionLocation = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection.m[0][0]);
    

    // Create MVP
    /*Mat4 mvp = mat4_multiply(projection, mat4_multiply(view, model));

    //assign MVP
    GLint mvpLocation = glGetUniformLocation(program, "MVP");
    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp.m[0][0]);*/

    //set vertex buffer data
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, mesh.verticesCount * sizeof(Vec3f), mesh.vertices, GL_STATIC_DRAW);

    //set index buffer data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.vertex_indices_count * sizeof(uint32_t), mesh.vertex_indices, GL_STATIC_DRAW);

    //setup vertex shader with vec3f data format
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vec3f), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawElements(GL_TRIANGLES, mesh.vertex_indices_count, GL_UNSIGNED_INT, NULL);
}

void renderer_terminate()
{
    glfwTerminate();

    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);
}