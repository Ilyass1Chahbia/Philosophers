/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_rot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:29:15 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/10 11:18:32 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_complet_routine(t_data *data, long ind)
{
	pthread_mutex_lock(&data->forks);
	safe_printf(data, "has taken a fork");
	pthread_mutex_lock(&data->next->forks);
	safe_printf(data, "has taken a fork");
	pthread_mutex_lock(&data->var_lock);
	data->ms_lastm = ft_get_time();
	data->nb_meals++;
	pthread_mutex_unlock(&data->var_lock);
	safe_printf(data, "is eating");
	ind = ft_get_time();
	while (ft_get_time() - ind < data->data_of_shared->time_to_eat)
	{
		pthread_mutex_lock(&data->data_of_shared->death_lock);
		if (data->data_of_shared->nb_deaths == 1)
		{
			pthread_mutex_unlock(&data->data_of_shared->death_lock);
			return ;
		}
		pthread_mutex_unlock(&data->data_of_shared->death_lock);
		usleep(500);
	}
}

void	think_sleep(t_data *data, long ind)
{
	safe_printf(data, "is sleeping");
	ind = ft_get_time();
	while (ft_get_time() - ind < data->data_of_shared->time_to_sleep)
	{
		pthread_mutex_lock(&data->data_of_shared->death_lock);
		if (data->data_of_shared->nb_deaths == 1)
		{
			pthread_mutex_unlock(&data->data_of_shared->death_lock);
			return ;
		}
		pthread_mutex_unlock(&data->data_of_shared->death_lock);
		usleep(500);
	}
	safe_printf(data, "is thinking");
}

void	ft_all_routine(t_data	*data)
{
	long	ind;

	ind = 0;
	while (1)
	{
		pthread_mutex_lock(&data->data_of_shared->death_lock);
		if (data->data_of_shared->nb_deaths == 1)
		{
			pthread_mutex_unlock(&data->data_of_shared->death_lock);
			return ;
		}
		pthread_mutex_unlock(&data->data_of_shared->death_lock);
		ft_complet_routine(data, ind);
		pthread_mutex_unlock(&data->forks);
		pthread_mutex_unlock(&data->next->forks);
		pthread_mutex_lock(&data->data_of_shared->meal_lock);
		if (data->nb_meals == data->data_of_shared->nb_eat)
		{
			data->data_of_shared->full_ph++;
			pthread_mutex_unlock(&data->data_of_shared->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&data->data_of_shared->meal_lock);
		think_sleep(data, ind);
	}
}

int	check_philosopher_death(t_data *data)
{
	pthread_mutex_lock(&data->var_lock);
	if ((ft_get_time()) - data->ms_lastm > data->data_of_shared->time_to_die)
	{
		pthread_mutex_unlock(&data->var_lock);
		pthread_mutex_lock(&data->data_of_shared->death_lock);
		data->data_of_shared->nb_deaths = 1;
		pthread_mutex_unlock(&data->data_of_shared->death_lock);
		printf("%ld %d died\n",
			ft_get_time() - data->data_of_shared->real_time, data->id);
		return (1);
	}
	pthread_mutex_unlock(&data->var_lock);
	return (0);
}

void	*routine(void *av)
{
	t_data	*data;

	data = (t_data *)av;
	if (data->data_of_shared->nb_ph == 1)
	{
		one_case(data);
		return (NULL);
	}
	if (data->id % 2 == 0)
		usleep(400);
	ft_all_routine(data);
	return (NULL);
}
