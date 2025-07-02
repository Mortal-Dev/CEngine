#ifndef VEC2F_H
#define VEC2F_H

#include "../core/seethe.h"
#include <stdio.h>

typedef struct 
{
	float x;
	float y;
} Vec2f;

static inline void vec2f_print(const Vec2f v) 
{
	char log_buf[256];

	sprintf_s(log_buf, sizeof(log_buf), "\n%f %f", v.x, v.y);

	log_info(log_buf);
}

#endif