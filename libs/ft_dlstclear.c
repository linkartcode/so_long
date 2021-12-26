/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 07:44:13 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/17 08:42:23 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstclear(t_dlist **dlst, void (*del)(void *))
{
	if (!*dlst)
		return ;
	while (*dlst)
		ft_dlstdelone(&(*dlst), del);
}
