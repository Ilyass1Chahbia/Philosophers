/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:26:19 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/04 15:03:28 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ft_get_time(void)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

int	ft_create_philo(t_pub *pb, t_data **data)
{
	int		n;
	t_data	*tempo;

	n = 0;
	while (n < pb->nb_ph)
	{
		tempo = ft_lstnew(pb, n);
		if (!tempo)
		{
			free_philosophers(*data, n);
			return (0);
		}
		ft_lstaddback(data, tempo);
		n++;
	}
	tempo->next = *data;
	return (1);
}

int	ft_create_thread(t_pub *pb, t_data *data)
{
	int	n;

	n = 0;
	while (n < pb->nb_ph)
	{
		if (pthread_create(&data->nb_thread, NULL, &routine, data) != 0)
			return (free_philosophers(data, pb->nb_ph), 0);
		data = data->next;
		n++;
	}
	return (1);
}

void	safe_printf(t_data *data, char *s)
{
	pthread_mutex_lock(&data->data_of_shared->print_lock);
	pthread_mutex_lock(&data->data_of_shared->death_lock);
	if (data->data_of_shared->nb_deaths == 1)
	{
		pthread_mutex_unlock(&data->data_of_shared->death_lock);
		pthread_mutex_unlock(&data->data_of_shared->print_lock);
		return ;
	}
	pthread_mutex_unlock(&data->data_of_shared->death_lock);
	printf("%ld %d %s\n", ft_get_time() - data->data_of_shared->real_time,
		data->id, s);
	pthread_mutex_unlock(&data->data_of_shared->print_lock);
}

int	ft_join_threads(t_data *data, int num_threads)
{
	int	n;

	n = 0;
	while (n < num_threads && data)
	{
		if (pthread_join(data->nb_thread, NULL) != 0)
			pthread_detach(data->nb_thread);
		data = data->next;
		n++;
	}
	return (1);
}
