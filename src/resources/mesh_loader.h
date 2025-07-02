#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "../ecs/core_components/mesh.h"

Mesh mesh_load_obj(const char* obj_file_content);

#endif