/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmordeka <nmordeka@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 08:08:54 by nmordeka          #+#    #+#             */
/*   Updated: 2021/12/17 11:14:39 by nmordeka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **dlst, t_dlist *new)
{
	t_dlist	*last;

	if (dlst)
	{
		if (*dlst && new)
		{
			last = (*dlst)->prev;
			(*dlst)->prev = new;
			new -> next = *dlst;
			if (last)
			{
				last -> next = new;
				new -> prev = last;
			}
			else
			{
				(*dlst)->next = new;
				new->prev = *dlst;
			}
		}
		else
			*dlst = new;
	}
}
