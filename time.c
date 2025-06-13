#include "philo.h"
// void	print_time(int time_ms)
// {
// 	struct timeval	start_abs_time;
// 	struct timeval	cur_abs_time;
// 	// unsigned int	rel_time_s;
// 	int	rel_time_ms;

// 	gettimeofday(&start_abs_time, NULL);
// 	usleep(time_ms * 1000);
// 	gettimeofday(&cur_abs_time, NULL);
// 	// rel_time_s = cur_abs_time.tv_sec - start_abs_time.tv_sec;
// 	rel_time_ms = ((cur_abs_time.tv_usec + cur_abs_time.tv_sec * 1000000) - (start_abs_time.tv_usec + start_abs_time.tv_sec * 1000000)) / 1000;
// 	printf("time elapsed: %d ms\n", rel_time_ms);
// }

// int main(void)
// {
// 	int i = 0;
// 	__useconds_t x;

// 	while (i<10)
// 	{
// 		print_time(i++);
// 	}
// 	while (i<100)
// 	{
// 		print_time(i);
// 		i += 10;
// 	}
// 	while (i < 1000)
// 	{
// 		print_time(i);
// 		i += 100;
// 	}

// }

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (printf("gettimeofday() FAILURE\n"), 0);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / 1000));
}

int	ft_msleep(unsigned int time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}