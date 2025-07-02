#ifndef MATH_UTILS_H
#define MATH_UTILS_H

//clamps a given value between a min and max
static inline float clamp(float value, float min, float max) 
{
	if (value < min) 
	{
		return min;
	}
	else if (value > max) 
	{
		return max;
	}
	else 
	{
		return value;
	}
}

static inline float normalize_range(float value, float min_value, float max_value, float normalized_min, float normalized_max) 
{
	float normalized = ((value - min_value) / (max_value - min_value)) * (normalized_max - normalized_min) + normalized_min;
	return normalized;
}

#endif