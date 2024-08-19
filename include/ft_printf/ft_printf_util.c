/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzakharc <hzakharc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 22:08:26 by hzakharc          #+#    #+#             */
/*   Updated: 2024/06/23 17:57:23 by hzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		return (ft_printstr("(null)"));
	}
	while (s[i] != '\0')
	{
		ft_printchar(s[i]);
		i++;
	}
	return (i);
}

int	ft_printnum(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i += ft_printchar('-');
		n = -n;
	}
	if (n / 10)
		i += ft_printnum(n / 10);
	i += ft_printchar((n % 10) + '0');
	return (i);
}

int	ft_printunum(unsigned long n)
{
	int	i;

	i = 0;
	if (n / 10)
		i += ft_printunum(n / 10);
	i += ft_printchar((n % 10) + '0');
	return (i);
}
