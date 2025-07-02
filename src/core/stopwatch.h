#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <time.h>

typedef struct 
{
	clock_t start_time;
	int is_running;
} Stopwatch;

void stopwatch_start(Stopwatch* stopwatch);

float stopwatch_stop(Stopwatch* stopwatch);

#endif