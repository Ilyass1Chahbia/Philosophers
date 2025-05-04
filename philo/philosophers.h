/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilchahbi <ilchahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:36:01 by ilchahbi          #+#    #+#             */
/*   Updated: 2024/10/07 12:23:43 by ilchahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_pub
{
	int				nb_ph;
	int				time_to_eat;
	int				time_to_die;
	int				time_to_sleep;
	int				nb_eat;
	long			real_time;
	int				nb_deaths;
	int				full_ph;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	print_lock;
	struct s_data	*head;
}	t_pub;

typedef struct s_data
{
	long			ms_lastm;
	int				id;
	int				nb_meals;
	pthread_mutex_t	forks;
	pthread_mutex_t	var_lock;
	pthread_t		nb_thread;
	t_pub			*data_of_shared;
	struct s_data	*next;
}	t_data;

int		ft_isdg(int c);
long	ft_atoi(char *str);
int		parsing(char **av);
t_data	*ft_lstnew(t_pub *pb, int i);
void	ft_lstaddback(t_data **philo, t_data *new);
long	ft_get_time(void);
t_pub	*vars_int(char **av, int ac);
void	*routine(void *av);
int		init_mutexes(t_pub *pb);
int		ft_create_thread(t_pub *pb, t_data *data);
int		ft_create_philo(t_pub *pb, t_data **data);
int		ft_join_threads(t_data *data, int num_threads);
void	safe_printf(t_data *data, char *s);
void	free_philosophers(t_data *ph, int len);
void	free_shared_data(t_pub *pb);
void	skip_wspaces(char **str);
int		check_all_philosophers_full(t_data *data);
int		check_philosopher_death(t_data *data);
void	one_case(t_data *data);
int		is_full_spaces(char **ag);
int		ft_inv(char c);

#endif
