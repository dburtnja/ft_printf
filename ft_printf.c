/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dburtnja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 14:01:51 by dburtnja          #+#    #+#             */
/*   Updated: 2017/01/27 21:11:19 by dburtnja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(char *str, ...)
{
	t_arg	*head;
	int		ret;
	va_list arg_ptr;

	if (!str)
		return (-1);
	va_start(arg_ptr, str);
	head = read_str(str, arg_ptr);
	ret = ft_print(head);
	va_end(arg_ptr);
	return (ret);
}
