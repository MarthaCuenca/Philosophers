#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

void	aru(void *tmp)
{
	if (tmp)
		free(tmp);
}

void	wait_pthreads(int n, pthread_t *philos, pthread_t *monitor)
{
	int	i;

	i = 0;
	if (philos)
		while (i < n)
			pthread_join(philos[i++], NULL);
	if (monitor)
		pthread_join(*monitor, NULL);
}

void	clean_mng(t_id *data, pthread_t *philos, pthread_t *monitor)
{
	if (philos || monitor)
	{
		wait_pthreads(data->share->st->people, philos, monitor);
		pthread_mutex_destroy(&data->share->dy->mutex);
	}
	free(data->share->dy->hashi);
	free(data->share->dy->timer);
	free(data);
	free(philos);
}

