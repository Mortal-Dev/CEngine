#include "stopwatch.h"

void stopwatch_start(Stopwatch* stopwatch)
{
	if (!stopwatch->is_running)
	{
		stopwatch->start_time = clock();
		stopwatch->is_running = 1;
	}
}

float stopwatch_stop(Stopwatch* stopwatch)
{
	if (stopwatch->is_running)
	{
		clock_t end_time = clock();
		stopwatch->is_running = 0;
		return (float)(end_time - stopwatch->start_time) / CLOCKS_PER_SEC;
	}

	return 0.0f;
}