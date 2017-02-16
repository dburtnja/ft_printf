/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_g.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dburtnja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 21:28:34 by dburtnja          #+#    #+#             */
/*   Updated: 2017/02/16 15:24:23 by dburtnja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*try_double(long double nbr, t_arg *head, int nbr_len)
{
	char	*str;
	int		i;
	int		prec;

	prec = head->precision;
	if (head->precision >= nbr_len && (long long)nbr != 0)
		head->precision = head->precision - nbr_len;
	str = ft_itoa_d(nbr, head, -1);
	i = ft_strlen(str);
	while (i > 0 && str[i - 1] == '0' && head->precision != 0 && head->flag.hesh == 0)
	{
		str[i - 1] = 0;
		i--;
	}
	if (str[i - 1] == '.')
		str[i - 1] = 0;
	head->precision = prec;
	return (str);
}

void	rem_nul(char *str)
{
	int		i;
	char	*p;

	i = 0;
	while ((str[i] != 0 && str[i] >= '0' && str[i] <= '9') || str[i] == '-' ||
		str[i] == '.')
		i++;
	p = str + i - 1;
	while ((*p == '0') && p != str)
		p--;
	if (*p == '.')
		p--;
	ft_memmove((void*)p + 1, (void*)str + i, (ft_strlen(str) - i) + 1);
}

char	*try_mod_e(long double nbr, t_arg *head, int *count)
{
	int		prec;
	char	*str;

	prec = head->precision;
	if (head->precision >= 1)
		head->precision = head->precision - 1;
	str = mod_e(nbr, head, count);
	if (head->flag.hesh == 0)
		rem_nul(str);
	head->precision = prec;
	return (str);
}

char	*mod_g(long double nbr, t_arg *head)
{
	char	*str;
	int		count;
	int		nbr_len;

	nbr_len = ft_nbrlen((long long)(nbr < 0 ? -nbr : nbr), 10);
	if (head->precision == -1)
		head->precision = 6;
	else if (head->precision < 1)
		head->precision = 1;
	str = try_mod_e(nbr, head, &count);
	if (count < -4 || (head->precision != -1 && count >= head->precision))
		return (str);
	else
	{
		ft_strdel(&str);
		return (try_double(nbr, head, nbr_len));
	}
}
