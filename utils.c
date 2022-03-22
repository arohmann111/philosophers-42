/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:58:00 by arohmann          #+#    #+#             */
/*   Updated: 2022/03/18 12:58:10 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (c);
	return (0);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return ((char *)(str + i));
		i++;
	}
	if (c == '\0')
		return ((char *)str + i);
	return (0);
}

static void	ft_check(char *s, int *error, int *minus)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (s[i] != '\0')
	{	
		if (s[i] == '-' || s[i] == '+')
			sign += 1;
		if (ft_strchr("0123456789+- ", s[i]) == 0)
		{
			*error = -1;
			return ;
		}
		i++;
	}
	if (sign == 1 && s[0] == '-')
		*minus = -1;
	if (sign > 1 || i > 11 || (sign == 1
			&& (s[0] != '-' && s[0] != '+')) || s[i] != '\0')
		*error = -1;
}

int	ft_atoi(char *str, int *error)
{
	int				i;
	unsigned int	res;
	int				sign;

	i = 0;
	sign = 1;
	res = 0;
	ft_check(str, error, &sign);
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_isdigit(str[i]) == 0)
		*error = -1;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if ((sign == 1 && res > 2147483647)
		|| (res > ((unsigned int) 2147483647 + 1) && sign == -1))
		*error = -1;
	return (sign * res);
}
