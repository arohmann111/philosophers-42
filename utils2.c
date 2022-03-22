/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:58:58 by arohmann          #+#    #+#             */
/*   Updated: 2022/03/18 14:29:27 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	time_from_start_in_ms(void)
{
	struct timeval			time;
	static unsigned long	start_time = 0;

	gettimeofday(&time, NULL);
	if (start_time == 0)
		start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time);
}

void	print_status(t_info *info, int id, char *str)
{
	pthread_mutex_lock(&(info->writing));
	if (info->died == 0 && info->all_ate == 0)
	{
		printf("\033[36;2m%lu ms\033[0m	", time_from_start_in_ms());
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(info->writing));
	return ;
}

void	free_all(t_info *info)
{
	if (info->p != NULL)
		free(info->p);
	if (info->forks != NULL)
		free(info->forks);
	if (info != NULL)
	{
		free(info);
		info = NULL;
	}
}
