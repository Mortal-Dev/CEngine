#ifndef MATRIX_H
#define MATRIX_H

#include "vec3f.h"
#include "../core/seethe.h"
#include <math.h>

typedef struct {
	float m[4][4];
} Mat4;

// Create identity matrix
static inline Mat4 mat4_identity() 
{
	Mat4 mat = { 0 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat.m[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}

	return mat;
}

// Matrix multiplication for 4x4 matrices
static inline Mat4 mat4_multiply(const Mat4 a, const Mat4 b) 
{
	Mat4 result = { 0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = a.m[i][0] * b.m[0][j]
				+ a.m[i][1] * b.m[1][j]
				+ a.m[i][2] * b.m[2][j]
				+ a.m[i][3] * b.m[3][j];
		}
	}
	return result;
}

// Transpose a 4x4 matrix
static inline Mat4 mat4_transpose(const Mat4 m) 
{
	Mat4 result = { 0 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = m.m[j][i];
		}
	}

	return result;
}

// Create a perspective projection matrix
static inline Mat4 mat4_perspective(float fov_degrees, float aspect, float near, float far) 
{
	float f = 1.0f / tanf(fov_degrees * (3.141592f / 180.0f) / 2.0f);
	float range = near - far;

	Mat4 result = { 0 };
	result.m[0][0] = f / aspect;
	result.m[1][1] = f;
	result.m[2][2] = (far + near) / range;
	result.m[2][3] = -1.0f;
	result.m[3][2] = (2.0f * far * near) / range;

	return result;
}

// Translates a matrix given a Vector3 position
static inline Mat4 mat4_translate(const Mat4 m, const Vec3f translation)
{
	Mat4 result = m;

	result.m[3][0] += translation.x;
	result.m[3][1] += translation.y;
	result.m[3][2] += translation.z;

	return result;
}

//matrix euler rotation translations
static inline Mat4 mat4_rotate_x(const Mat4 m, float angle_radians) 
{
	Mat4 rotation = mat4_identity();

	float c = cosf(angle_radians);
	float s = sinf(angle_radians);

	rotation.m[1][1] = c;
	rotation.m[1][2] = -s;
	rotation.m[2][1] = s;
	rotation.m[2][2] = c;

	return mat4_multiply(m, rotation);
}

static inline Mat4 mat4_rotate_y(const Mat4 m, float angle_radians) 
{
	Mat4 rotation = mat4_identity();

	float c = cosf(angle_radians);
	float s = sinf(angle_radians);

	rotation.m[0][0] = c;
	rotation.m[0][2] = s;
	rotation.m[2][0] = -s;
	rotation.m[2][2] = c;

	return mat4_multiply(m, rotation);
}

static inline Mat4 mat4_rotate_z(const Mat4 m, float angle_radians) 
{
	Mat4 rotation = mat4_identity();

	float c = cosf(angle_radians);
	float s = sinf(angle_radians);

	rotation.m[0][0] = c;
	rotation.m[0][1] = -s;
	rotation.m[1][0] = s;
	rotation.m[1][1] = c;

	return mat4_multiply(m, rotation);
}

// Creates a view matrix from camera position, forward, and up vectors
static inline Mat4 mat4_look_at(Vec3f position, Vec3f forward, Vec3f up)
{
	Mat4 result = { 0 };

	// Normalize the forward vector
	float forward_length = sqrtf(forward.x * forward.x + forward.y * forward.y + forward.z * forward.z);
	Vec3f f = {
		forward.x / forward_length,
		forward.y / forward_length,
		forward.z / forward_length
	};

	// Compute the right vector (cross product of up and forward)
	Vec3f right = {
		up.y * f.z - up.z * f.y,
		up.z * f.x - up.x * f.z,
		up.x * f.y - up.y * f.x
	};

	// Normalize the right vector
	float right_length = sqrtf(right.x * right.x + right.y * right.y + right.z * right.z);
	right.x /= right_length;
	right.y /= right_length;
	right.z /= right_length;

	// Recompute the up vector (cross product of forward and right)
	Vec3f u = {
		f.y * right.z - f.z * right.y,
		f.z * right.x - f.x * right.z,
		f.x * right.y - f.y * right.x
	};

	// Create the view matrix
	result.m[0][0] = right.x;
	result.m[1][0] = right.y;
	result.m[2][0] = right.z;
	result.m[3][0] = -(right.x * position.x + right.y * position.y + right.z * position.z);

	result.m[0][1] = u.x;
	result.m[1][1] = u.y;
	result.m[2][1] = u.z;
	result.m[3][1] = -(u.x * position.x + u.y * position.y + u.z * position.z);

	result.m[0][2] = -f.x;
	result.m[1][2] = -f.y;
	result.m[2][2] = -f.z;
	result.m[3][2] = f.x * position.x + f.y * position.y + f.z * position.z;

	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}


static inline Mat4 mat4_scale(const Mat4 m, const Vec3f scale) 
{
	Mat4 result = m;

	result.m[0][0] *= scale.x;
	result.m[1][0] *= scale.x;
	result.m[2][0] *= scale.x;

	result.m[0][1] *= scale.y;
	result.m[1][1] *= scale.y;
	result.m[2][1] *= scale.y;

	result.m[0][2] *= scale.z;
	result.m[1][2] *= scale.z;
	result.m[2][2] *= scale.z;

	return result;
}

// Functions to extract data from matrix

static inline Vec3f mat4_get_position(const Mat4 transform) 
{
	return (Vec3f) 
	{
		transform.m[3][0],
		transform.m[3][1],
		transform.m[3][2]
	};
}

static inline Vec3f mat4_get_scale(const Mat4 transform) 
{
	Vec3f scale = { 0, 0, 0 };

	// X scale is the length of the first basis vector (first column)
	scale.x = sqrtf(
		transform.m[0][0] * transform.m[0][0] +
		transform.m[1][0] * transform.m[1][0] +
		transform.m[2][0] * transform.m[2][0]
	);

	// Y scale is the length of the second basis vector (second column)
	scale.y = sqrtf(
		transform.m[0][1] * transform.m[0][1] +
		transform.m[1][1] * transform.m[1][1] +
		transform.m[2][1] * transform.m[2][1]
	);

	// Z scale is the length of the third basis vector (third column)
	scale.z = sqrtf(
		transform.m[0][2] * transform.m[0][2] +
		transform.m[1][2] * transform.m[1][2] +
		transform.m[2][2] * transform.m[2][2]
	);

	return scale;
}

// Helper function to create rotation matrix from Euler angles
static Mat4 mat4_from_euler(float pitch, float yaw, float roll) 
{
	Mat4 out;

	float cp = cosf(pitch);
	float sp = sinf(pitch);
	float cy = cosf(yaw);
	float sy = sinf(yaw);
	float cr = cosf(roll);
	float sr = sinf(roll);

	out.m[0][0] = cy * cr;
	out.m[0][1] = cy * sr;
	out.m[0][2] = -sy;
	out.m[0][3] = 0.0f;

	out.m[1][0] = sp * sy * cr - cp * sr;
	out.m[1][1] = sp * sy * sr + cp * cr;
	out.m[1][2] = sp * cy;
	out.m[1][3] = 0.0f;

	out.m[2][0] = cp * sy * cr + sp * sr;
	out.m[2][1] = cp * sy * sr - sp * cr;
	out.m[2][2] = cp * cy;
	out.m[2][3] = 0.0f;

	out.m[3][0] = 0.0f;
	out.m[3][1] = 0.0f;
	out.m[3][2] = 0.0f;
	out.m[3][3] = 1.0f;

	return out;
}

static inline void mat4_print(const Mat4 mat) 
{
	char logBuff[512];

	sprintf_s(logBuff, sizeof(logBuff), "\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f",
		mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3],
		mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
		mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3],
		mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]);

	log_info(logBuff);
}

#endif