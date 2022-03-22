/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:44:57 by arohmann          #+#    #+#             */
/*   Updated: 2022/03/18 14:00:26 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_info *info)
{
	int	i;

	i = 0;
	info->p = (t_phi *)malloc(sizeof(t_phi) * info->n_philos);
	while (i < info->n_philos)
	{
		info->p[i].id = i;
		info->p[i].l_fork = i;
		info->p[i].r_fork = (i + 1) % info->n_philos;
		info->p[i].l_eat = 0;
		info->p[i].n_eat = 0;
		i++;
	}
	i = 0;
	while (i < info->n_philos)
	{
		info->p[i].info = info;
		i++;
	}
}

int	init_mutex(t_info *info)
{
	int	i;

	i = 0;
	info->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->n_philos);
	while (i < info->n_philos)
	{
		if (pthread_mutex_init(&(info->forks[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(info->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(info->meal_check), NULL))
		return (1);
	return (0);
}

int	init_info_2nd(int ac, char **av, t_info **info)
{
	int	error;

	error = 0;
	if (ac == 6)
	{
		(*info)->m_eat = ft_atoi(av[5], &error);
		if ((*info)->m_eat <= 0 || error != 0)
			return (1);
	}
	else
		(*info)->m_eat = -1;
	if (init_mutex((*info)))
		return (1);
	init_philo((*info));
	return (0);
}

int	init_info(int ac, char **av, t_info **info)
{
	int	error;

	error = 0;
	*info = (t_info *)malloc(sizeof(t_info));
	(*info)->n_philos = ft_atoi(av[1], &error);
	(*info)->tt_die = ft_atoi(av[2], &error);
	(*info)->tt_eat = ft_atoi(av[3], &error);
	(*info)->tt_sleep = ft_atoi(av[4], &error);
	if (error == -1)
		return (1);
	(*info)->all_ate = 0;
	(*info)->died = 0;
	if ((*info)->n_philos < 1 || (*info)->tt_die < 0 || (*info)->tt_eat < 0
		|| (*info)->tt_sleep < 0 || (*info)->n_philos > 250)
		return (1);
	return (init_info_2nd(ac, av, info));
}
