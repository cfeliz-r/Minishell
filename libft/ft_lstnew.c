/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manufern <manufern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:56:07 by cfeliz-r          #+#    #+#             */
/*   Updated: 2024/09/16 14:22:55 by manufern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list_env	*ft_lstnew(void *content)
{
	t_list_env	*elt;

	elt = (t_list_env *)malloc(sizeof(*elt));
	if (elt == NULL)
		return (NULL);
	elt->data = content;
	elt->next = NULL;
	return (elt);
}
