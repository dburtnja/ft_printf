/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dburtnja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 15:50:26 by dburtnja          #+#    #+#             */
/*   Updated: 2017/02/11 20:38:48 by dburtnja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*write_e(long double nbr, t_arg *head, int c)
{
	char	*buf;
	char	*str1;
	char	*str2;
	char	*ret;
	char	upper;

	upper = head->type == 13 || head->type == 15 ? 'e' : 'E';
	str2 = ft_strnew(10);
	str2[0] = upper;
	str2[1] = c < 0 ? '-' : '+';
	buf = str2 + 2;
	if ((c > 0 ? c : c * -1) < 10)
	{
		*buf = '0';
		buf++;
	}
	nbr_to_str(c > 0 ? c : c * -1, 10, &buf, 0);
	head->width = head->width > (int)ft_strlen(str2) ? head->width -
		(int)ft_strlen(str2) : head->width;
	str1 = ft_itoa_d(nbr, head, c < 0 ? -c : c);
	ret = ft_strjoin(str1, str2);
	ft_strdel(&str1);
	ft_strdel(&str2);
	return (ret);
}

char	*mod_e(long double nbr, t_arg *head)
{
	unsigned long long	buf;
	int					count;
	long double			r_nbr;

	count = 0;
	buf = (unsigned long long)(nbr < 0 ? nbr * -1 : nbr);
	while (buf == 0 && nbr != 0)
	{
		count--;
		nbr *= 10;
		buf = (unsigned long long)(nbr < 0 ? nbr * -1 : nbr);
	}
	while (buf > 9)
	{
		count++;
		nbr /= 10;
		buf = (unsigned long long)(nbr < 0 ? nbr * -1 : nbr);
	}
	r_nbr = head->precision == 0 ? ft_r_nbr(nbr) : nbr;
	return (write_e(nbr, head, count));
}

char	*mod_g(long double nbr, t_arg *head)
{
	char		*m_d;
	char		*m_e;
	int			i;
	int			len;
	int			nbr_n;

	nbr_n = nbr < 0 ? -nbr : nbr;
	len = ft_nbrlen((long long)nbr_n, 10);
	if (head->precision == -1 && nbr - (long long)nbr == 0 && len > 6)
		head->precision = 6;
	else if (head->precision == -1 && nbr - (long long)nbr == 0)
		head->precision = 0;
	else if (head->precision == -1)
		head->precision = 4;
	else
		head->precision = head->precision - len;
	m_d = ft_itoa_d(nbr, head, -1);
	i = ft_strlen(m_d);
	while (i > 0 && m_d[i - 1] == '0' && head->precision != 0)
	{
		m_d[i - 1] = 0;
		i--;
	}
	i = head->precision;
	head->precision = head->precision < 0 ? head->precision + len - 1 : 5;
	m_e = mod_e(nbr, head);
	if (((len = ft_strlen(m_d)) < 6 || (size_t)len < ft_strlen(m_e)) && i >= 0 && ft_nbrlen((long long)nbr_n, 10) < 6)
		return (m_d);
	else
		return (m_e);
}

char	*type_d(t_arg *head, long double nbr)
{
	if (head->type == 11 || head->type == 12)
		return (ft_itoa_d(nbr, head, -1));
	else if (head->type == 13 || head->type == 14)
		return (mod_e(nbr, head));
	else if (head->type == 15 || head->type == 16)
		return (mod_g(nbr, head));
	else if (head->type == 17 || head->type == 18)
		return (mod_a(nbr, head));
	return (NULL);
}

void	mod_double(t_arg *head, va_list arg)
{
	char		*str;
	long double	nbr;

	if (head->size == 8)
		nbr = (long double)va_arg(arg, long double);
	else
		nbr = va_arg(arg, double);
	if (head->flag.min == 1)
		head->flag.nul = 0;
	if (head->precision == -1 && !(head->type >= 15 && head->type <= 18))
		head->precision = 6;
	str = type_d(head, nbr);
	mod_m_flag(str, head);
	ft_strdel(&str);
}
