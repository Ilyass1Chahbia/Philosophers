/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:47:30 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/09/28 12:47:30 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*ft_lstlast(t_data *lst)
{
	t_data	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

int	check_all_philosophers_full(t_data *data)
{
	pthread_mutex_lock(&data->data_of_shared->meal_lock);
	if (data->data_of_shared->full_ph == data->data_of_shared->nb_ph)
	{
		pthread_mutex_unlock(&data->data_of_shared->meal_lock);
		pthread_mutex_lock(&data->data_of_shared->death_lock);
		data->data_of_shared->nb_deaths = 1;
		pthread_mutex_unlock(&data->data_of_shared->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->data_of_shared->meal_lock);
	return (0);
}

void	one_case(t_data *data)
{
	pthread_mutex_lock(&data->forks);
	safe_printf(data, "has taken a fork");
	pthread_mutex_unlock(&data->forks);
}

int	is_full_spaces(char **ag)
{
	int	i;
	int	j;
	int	found_digit;

	i = 1;
	while (ag[i])
	{
		j = 0;
		found_digit = 0;
		while (ag[i][j])
		{
			if (ft_isdg(ag[i][j]) && !ft_isdg(ag[i][j + 1]))
				found_digit++;
			j++;
		}
		if (found_digit > 1)
			return (0);
		i++;
	}
	return (1);
}
