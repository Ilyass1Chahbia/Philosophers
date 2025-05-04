/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:36:07 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/10 11:19:38 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitor_loop(t_data *data)
{
	while (1)
	{
		if (check_philosopher_death(data))
			break ;
		if (check_all_philosophers_full(data))
			return ;
		data = data->next;
	}
}

t_pub	*vars_int(char **av, int ac)
{
	t_pub	*pb;

	pb = (t_pub *)malloc(sizeof(t_pub));
	if (!pb)
		return (NULL);
	pb->nb_ph = ft_atoi(av[1]);
	pb->time_to_die = ft_atoi(av[2]);
	pb->time_to_eat = ft_atoi(av[3]);
	pb->time_to_sleep = ft_atoi(av[4]);
	if ((pb->nb_ph < 1) || pb->time_to_die < 1 || pb->time_to_eat < 1
		|| pb->time_to_sleep < 1)
		return (write(2, "Error\n", 6), free_shared_data(pb), NULL);
	pb->nb_deaths = 0;
	pb->real_time = ft_get_time();
	pb->nb_eat = -1;
	if (ac == 6)
	{
		pb->nb_eat = ft_atoi(av[5]);
		if (pb->nb_eat <= 0)
			return (write(2, "Error3\n", 6), free_shared_data(pb), NULL);
	}
	pb->full_ph = 0;
	if (!init_mutexes(pb))
		return (free_shared_data(pb), NULL);
	return (pb);
}

void	ft_lstaddback(t_data **philo, t_data *new)
{
	t_data	*tempo;

	tempo = *philo;
	if (!*philo)
		*philo = new;
	else
	{
		while (tempo->next)
			tempo = tempo->next;
		tempo->next = new;
	}
}

t_data	*ft_lstnew(t_pub *pb, int n)
{
	t_data	*ph;

	ph = (t_data *)malloc(sizeof(t_data));
	if (!ph)
		return (0);
	ph->id = n + 1;
	ph->nb_meals = 0;
	ph->ms_lastm = pb->real_time;
	pthread_mutex_init(&ph->forks, NULL);
	pthread_mutex_init(&ph->var_lock, NULL);
	ph->data_of_shared = pb;
	ph->next = NULL;
	return (ph);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_pub		*pb;

	data = NULL;
	if (ac == 5 || ac == 6)
	{
		if (!parsing(av))
			return (write(2, "Error\n", 6), 1);
		pb = vars_int(av, ac);
		if (!pb)
			return (1);
		if (!ft_create_philo(pb, &data))
			return (free_shared_data(pb), 1);
		if (!ft_create_thread(pb, data))
			return (free_shared_data(pb), 1);
		monitor_loop(data);
		if (!ft_join_threads(data, pb->nb_ph))
			return (free_shared_data(pb), free_philosophers(data, pb->nb_ph),
				1);
		free_philosophers(data, pb->nb_ph);
		free_shared_data(pb);
	}
	else
		return (write(2, "Error !, wrong number of arguments!\n", 36), 1);
}
