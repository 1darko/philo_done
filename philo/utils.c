/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:29:18 by dakojic           #+#    #+#             */
/*   Updated: 2024/05/25 11:29:20 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	true_time(void)
{
	struct timeval	clock;

	gettimeofday(&clock, NULL);
	return ((clock.tv_sec * 1000) + (clock.tv_usec / 1000));
}

void	true_sleep(int nap_time, t_philo *phi)
{
	long long	clock;
	long long	post_nap;

	clock = true_time();
	post_nap = clock;
	while (post_nap - clock < nap_time && !dead_thread(0, phi))
	{
		usleep(nap_time / 10);
		post_nap = true_time();
	}
}

void	printer(t_philo *philo, char *s, int flag)
{
	long long	time;

	pthread_mutex_lock(&(philo->set->print));
	time = true_time();
	pthread_mutex_lock(&philo->set->dead);
	if (!dead_thread(0, philo))
	{
		printf("%lld %d %s", (time - philo->set->start), philo->id, s);
	}
	pthread_mutex_unlock(&philo->set->dead);
	pthread_mutex_unlock(&(philo->set->print));
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	i;
	int	num;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (num * neg);
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}
