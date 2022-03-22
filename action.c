/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 21:09:38 by annarohmnn        #+#    #+#             */
/*   Updated: 2022/03/18 14:29:00 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeps(unsigned long time, t_info *info)
{
	unsigned long	i;

	i = time_from_start_in_ms();
	while (info->died == 0)
	{
		if (time_from_start_in_ms() - i >= time)
			break ;
		usleep(50);
	}
}

void	eats(t_phi *p)
{
	t_info	*info;

	info = p->info;
	pthread_mutex_lock(&(info->forks[p->l_fork]));
	print_status(info, p->id, "\e[1;35mhas taken a fork\033[0m");
	pthread_mutex_lock(&(info->forks[p->r_fork]));
	print_status(info, p->id, "\e[1;35mhas taken a fork\033[0m");
	pthread_mutex_lock(&(info->meal_check));
	print_status(info, p->id, "\e[1;33mis eating\033[0m");
	p->l_eat = time_from_start_in_ms();
	pthread_mutex_unlock(&(info->meal_check));
	sleeps(info->tt_eat, info);
	p->n_eat++;
	pthread_mutex_unlock(&(info->forks[p->l_fork]));
	pthread_mutex_unlock(&(info->forks[p->r_fork]));
}

void	dead_unlock(t_info *i, int j)
{
	int	k;

	print_status(i, j, "\033[1;4;31mdied\033[0m");
	i->died = 1;
	k = 0;
	while (k < i->n_philos)
	{
		pthread_mutex_unlock(&(i->forks[k]));
		++k;
	}
}

void	dead(t_info *i, t_phi *p)
{
	int	j;

	while (i->all_ate == 0)
	{
		j = 0;
		while (j < i->n_philos && (i->died == 0))
		{
			pthread_mutex_lock(&(i->meal_check));
			if ((time_from_start_in_ms() - p[j].l_eat)
				> (unsigned long)i->tt_die)
				dead_unlock(i, j);
			pthread_mutex_unlock(&(i->meal_check));
			j++;
		}
		if (i->died)
			break ;
		j = 0;
		while (i->m_eat != -1 && j < i->n_philos && p[j].n_eat >= i->m_eat)
			j++;
		if (j == i->n_philos)
			i->all_ate = 1;
	}
}

void	end(t_info *info, t_phi *phi)
{
	int	i;

	i = 0;
	while (i < info->n_philos)
	{
		pthread_join(phi[i].t_id, NULL);
		i++;
	}
	i = 0;
	while (i < info->n_philos)
	{
		pthread_mutex_destroy(&(info->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(info->writing));
	pthread_mutex_destroy(&(info->meal_check));
}
