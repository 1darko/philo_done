/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:54:58 by dakojic           #+#    #+#             */
/*   Updated: 2024/05/25 11:30:26 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_settings	t_s;

typedef struct s_philo
{
	pthread_t		tr_id;
	int				id;
	int				stop;
	int				meals;
	long long		last_meal;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	a;
	t_s				*set;
	pthread_t		temp;
}	t_philo;

typedef struct s_settings
{
	pthread_mutex_t	*forks;
	t_philo			*philo;
	long long		start;
	int				nbr_philo;
	long long int	time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				glutony;
	int				big_stop;
	int				full;
	pthread_mutex_t	eating;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	mutex_stop;
	pthread_mutex_t	stop_check;
	int				num_meals;
	int				meals_eaten;
	int				dead_philo;
}	t_s;

long long	true_time(void);
void		true_sleep(int nap_time, t_philo *phi);
void		printer(t_philo *philo, char *s, int flag);
int			ft_atoi(const char *str);
int			is_digit(char c);
void		free_setter(t_s *set, int level);
int			check_av(char **av);
void		philo_filler(t_s *set, int i);
int			starter_philo(t_s *set);
int			dead_thread(int flag, t_philo *philo);
void		*pulse_check(void *phi);
void		monitoring(t_s *set, int i);
void		fork_grab(t_philo *philo);
void		fork_drop(t_philo *philo);
void		eating(t_philo *philo);
void		lonely_philo(t_philo *philo);
void		*diner(void *p);
int			settings_mutex_init(t_s *s);
void		mutex_fail(t_s *s, int i);
int			settings_filler(t_s *settings, char **av);
void		settings_filler2(t_s *set, char **av);
int			setter(t_s *set, char **av);

#endif
