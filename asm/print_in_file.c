/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdeanne <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:22:26 by mdeanne           #+#    #+#             */
/*   Updated: 2020/02/28 16:22:28 by mdeanne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/libft.h>
#include <fcntl.h>
#include "asm_dasha.h"
#include <stdlib.h>
#include <stdio.h>

void			print_in_file(char *file_name, t_token *token, header_t *header)
{
	int			fd;
	int			nulle;

	nulle = 0;
	fd = open(file_name, O_RDWR);
	print_header(fd, header);
	write(fd, &nulle, 4);
	print_commands(fd, token);


	/*
	 * DEBAG PART
	 *
	*/
	u_int32_t	buff[2300];
	u_int8_t	*ptr;

	lseek(fd, 0, SEEK_SET);
	int ret;
	ret = read(fd, buff, 2299);
	ptr = (u_int8_t*)buff;
	int i = 0;
	while (ret--)
	{
		printf("%02x", *ptr);
		if (i && (i + 1) % 2 == 0)
			printf(" ");
		if (i && (i + 1) % 16 == 0)
			printf("\n");
		i++;
		ptr++;
	}
	/*
	 * DEBAG PART
	 *
	*/
	close(fd);
}
