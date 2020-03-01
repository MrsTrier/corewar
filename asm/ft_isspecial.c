/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspecial.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 17:52:30 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/29 17:52:31 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

_Bool	ft_isspecial(char c, char *special)
{
	while (*special)
	{
		if (c == *special)
			return (1);
		special++;
	}
	return (0);
}