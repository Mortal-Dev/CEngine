#include "mesh_loader.h"
#include "../math/vec3f.h"
#include "../core/seethe.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

//mesh loading for .obj file format

//face in obj file stored as: <uint32_t>/<uint32_t>/<uint32_t> <uint32_t>/<uint32_t>/<uint32_t>...
static int parse_face_indices_obj(const char* indices_content, uint32_t** vertex_indices, uint32_t** texture_coordinate_indices, uint32_t** normal_indices, size_t* count) 
{
    const char* p = indices_content;
    char* endptr;
    size_t capacity = 10;
    size_t i = 0;

    // Initialize output arrays
    *vertex_indices = malloc(capacity * sizeof(uint32_t));
    *texture_coordinate_indices = malloc(capacity * sizeof(uint32_t));
    *normal_indices = malloc(capacity * sizeof(uint32_t));

    if (!*vertex_indices || !*texture_coordinate_indices || !*normal_indices) 
    {
        free(*vertex_indices);
        free(*texture_coordinate_indices);
        free(*normal_indices);
        return 0;
    }

    while (*p && *p != '\n') // Stop at newline
    {  
        // Skip leading whitespace (except newline)
        while (isspace((unsigned char)*p))
        {
            if (*p == '\n') 
                break;
            p++;
        }

        if (*p == '\n' || *p == '\0') 
            break;

        // Parse vertex index
        errno = 0;
        (*vertex_indices)[i] = strtoul(p, &endptr, 10);
        if (errno || p == endptr || *endptr != '/') 
        {
            log_error("Invalid vertex index format");
            goto error;
        }
        p = endptr + 1;

        // Parse texture coordinate index
        (*texture_coordinate_indices)[i] = strtoul(p, &endptr, 10);
        if (errno || p == endptr || *endptr != '/') 
        {
            log_error("Invalid texture coordinate index format");
            goto error;
        }
        p = endptr + 1;

        // Parse normal index
        (*normal_indices)[i] = strtoul(p, &endptr, 10);
        if (errno || p == endptr) 
        {
            log_error("Invalid normal index format");
            goto error;
        }
        p = endptr;

        i++;

        // Resize arrays if needed
        if (i >= capacity) 
        {
            capacity *= 2;

            uint32_t* new_v = realloc(*vertex_indices, capacity * sizeof(uint32_t));
            uint32_t* new_tc = realloc(*texture_coordinate_indices, capacity * sizeof(uint32_t));
            uint32_t* new_n = realloc(*normal_indices, capacity * sizeof(uint32_t));

            if (!new_v || !new_tc || !new_n) 
            {
                free(new_v);
                free(new_tc);
                free(new_n);
                goto error;
            }

            *vertex_indices = new_v;
            *texture_coordinate_indices = new_tc;
            *normal_indices = new_n;
        }

        // Skip whitespace until next token or newline
        while (isspace((unsigned char)*p)) 
        {
            if (*p == '\n') break;
            p++;
        }
    }

    *count = i;
    return 1;

error:
    free(*vertex_indices);
    free(*texture_coordinate_indices);
    free(*normal_indices);
    *vertex_indices = NULL;
    *texture_coordinate_indices = NULL;
    *normal_indices = NULL;
    return 0;
}

//interprets char* data in format <float> <float> <float>
static Vec3f parse_vec3f_obj(const char* vertex_content, uint32_t index)
{
    Vec3f result = { 0.0f, 0.0f, 0.0f };

    const char* ptr = &vertex_content[index];
    char* end;

    int count = 0;

    while (*ptr != '\n' && count < 3) 
    {
        // Skip any leading whitespace
        while (*ptr == ' ' || *ptr == '\t' || *ptr == '\n') 
        {
            ptr++;
        }

        // Convert the float
        float value = strtof(ptr, &end);

        // Check if conversion succeeded
        if (ptr == end) 
        {
            break; // Stop if no valid float found
        }

        // Set parsed value to the corresponding Vec3f axis
        if (count == 0) 
        {
            result.x = value;
        }
        else if (count == 1) 
        {
            result.y = value;
        }
        else if (count == 2) 
        {
            result.z = value;
        }

        // Move the pointer to the next part
        ptr = end;

        // Increment Vec3f axis reference counter
        count++;
    }

    return result;
}

static uint32_t get_vertex_count(const char* obj_file_content, size_t obj_file_content_length)
{
    uint32_t vertex_count = 0;

    for (uint32_t i = 0; i < obj_file_content_length; i++)
    {
        char c = obj_file_content[i];

        //vertex in obj file stored as: v <float> <float> <float> (e.g. v 1.000000 1.000000 1.000000)
        if (c == 'v' && obj_file_content[i + 1] == ' ')
        {
            vertex_count++;
        }
    }

    return vertex_count;
}

static uint32_t get_vertex_indices_count(const char* obj_file_content, size_t obj_file_content_length)
{
    uint32_t indices_count = 0;

    for (uint32_t i = 0; i < obj_file_content_length; i++)
    {
        char c = obj_file_content[i];

        //vertex in obj file stored as: v <float> <float> <float> (e.g. v 1.000000 1.000000 1.000000)
        if (c == 'f' && obj_file_content[i + 1] == ' ')
        {
            indices_count += 3;
        }
    }

    return indices_count;
}

Mesh mesh_load_obj(const char* obj_file_content)
{
    size_t obj_file_content_length = strlen(obj_file_content);

    Mesh mesh;

    mesh.verticesCount = get_vertex_count(obj_file_content, obj_file_content_length);
    mesh.vertex_indices_count = get_vertex_indices_count(obj_file_content, obj_file_content_length);

    mesh.vertices = (Vec3f*)malloc(sizeof(Vec3f) * mesh.verticesCount);
    mesh.vertex_indices = (uint32_t*)malloc(sizeof(uint32_t) * mesh.vertex_indices_count);

    for (uint32_t i = 0, vertex_position  = 0, indices_position = 0; i < obj_file_content_length; i++)
    {
        char c = obj_file_content[i];

        //vertex in obj file stored as: v <float> <float> <float> (e.g. v 1.000000 1.000000 1.000000)
        if (c == 'v' && obj_file_content[i + 1] == ' ')
        {
            //parse vertex
            int startVertexIndex = i + 2;
            Vec3f vertex = parse_vec3f_obj(obj_file_content, i + 2);

            //store vertex in mesh vertices
            mesh.vertices[vertex_position] = vertex;
            vertex_position++;
        }
        //face in obj file stored as: f <uint32_t>/<uint32_t>/<uint32_t>
        //first index is vertex index, second index is texture coordinate index, and third index in normal index
        else if (c == 'f' && obj_file_content[i + 1] == ' ') 
        {
            uint32_t* vertex_indices = NULL;
            uint32_t* texture_coordinate_indices = NULL;
            uint32_t* normal_indices = NULL;
            size_t count = 0;

            //parse indices
            if (parse_face_indices_obj(&obj_file_content[i + 2], &vertex_indices, &texture_coordinate_indices, &normal_indices, &count)) 
            {
                //store vertex indices in mesh
                for (uint32_t start = 0; start < count; start++)
                {
                    mesh.vertex_indices[indices_position] = vertex_indices[start] - 1;
                    indices_position++;
                }
            }

            free(vertex_indices);
            free(texture_coordinate_indices);
            free(normal_indices);
        }
    }

    return mesh;
}
