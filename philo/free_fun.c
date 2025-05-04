/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:50:52 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/10 10:50:45 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philosophers(t_data *ph, int len)
{
	t_data	*temp;
	int		i;

	i = 0;
	if (!ph)
		return ;
	while (ph && i < len)
	{
		temp = ph;
		pthread_mutex_destroy(&temp->forks);
		pthread_mutex_destroy(&temp->var_lock);
		ph = ph->next;
		free(temp);
		i++;
	}
}

void	free_shared_data(t_pub *pb)
{
	if (!pb)
		return ;
	pthread_mutex_destroy(&pb->death_lock);
	pthread_mutex_destroy(&pb->meal_lock);
	pthread_mutex_destroy(&pb->print_lock);
	free(pb);
}

void	skip_wspaces(char **str)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
}

int	init_mutexes(t_pub *pb)
{
	if (pthread_mutex_init(&pb->death_lock, NULL) != 0)
		return (write(2, "Mutex init error\n", 17), 0);
	if (pthread_mutex_init(&pb->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&pb->death_lock);
		return (write(2, "Mutex init error\n", 17), 0);
	}
	if (pthread_mutex_init(&pb->print_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&pb->death_lock);
		pthread_mutex_destroy(&pb->meal_lock);
		return (write(2, "Mutex init error\n", 17), 0);
	}
	return (1);
}

int	ft_inv(char c)
{
	if (!ft_isdg(c) && c != '+' && c != 32)
		return (0);
	else
		return (1);
}
