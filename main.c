/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:44:25 by arohmann          #+#    #+#             */
/*   Updated: 2022/03/18 13:08:20 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *v_philo)
{
	int		i;
	t_phi	*p;
	t_info	*info;

	i = 0;
	p = (t_phi *)v_philo;
	info = p->info;
	if (p->id % 2)
		usleep(15000);
	while (p->info->died == 0 && info->all_ate == 0)
	{
		eats(p);
		if (info->all_ate)
			break ;
		print_status(info, p->id, "\033[1;36mis sleeping\033[0m");
		sleeps(info->tt_sleep, info);
		print_status(info, p->id, "\033[1;32mis thinking\033[0m");
		i++;
	}
	return (NULL);
}

int	create_philos(t_info *info)
{
	int		i;
	t_phi	*p;

	i = 0;
	p = info->p;
	while (i < info->n_philos)
	{
		if (pthread_create(&(p[i].t_id), NULL, routine, (void *)(&p[i])))
		{
			write(1, "Error: Failed to create thread \n", 32);
			return (1);
		}
		p[i].l_eat = time_from_start_in_ms();
		i++;
	}
	dead(info, info->p);
	end(info, p);
	return (0);
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = NULL;
	if (ac == 5 || ac == 6)
	{
		if (init_info(ac, av, &info) != 0)
			return (1);
		create_philos(info);
	}
	else
	{
		write(1, "Error: wrong number of arguments!\n", 34);
		return (1);
	}
	free_all(info);
	return (0);
}
