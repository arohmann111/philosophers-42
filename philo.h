/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:58:30 by arohmann          #+#    #+#             */
/*   Updated: 2022/03/18 13:07:21 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

struct	s_info;

typedef struct s_phi
{
	int				id;
	int				l_fork;
	int				r_fork;
	unsigned long	l_eat;
	int				n_eat;
	pthread_t		t_id;
	struct s_info	*info;
}	t_phi;

typedef struct s_info
{
	int				n_philos;
	int				tt_eat;
	int				tt_die;
	int				tt_sleep;
	int				died;
	int				m_eat;
	int				all_ate;
	t_phi			*p;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	meal_check;
}	t_info;

/**********************************************************/
/*                         PHILO                          */
/**********************************************************/
int				create_philos(t_info *info);
int				init_info(int ac, char **av, t_info **info);
void			eats(t_phi *p);
void			sleeps(unsigned long time, t_info *info);
void			dead(t_info *info, t_phi *p);
void			end(t_info *info, t_phi *phi);
/**********************************************************/
/*                         UTILS                          */
/**********************************************************/
void			print_status(t_info *info, int id, char *str);
unsigned long	time_from_start_in_ms(void);
int				ft_atoi(char *str, int *error);
void			free_all(t_info *info);
#endif