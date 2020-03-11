
#include <libft/libft.h>
#include <fcntl.h>
#include "file_to_list.h"
#include "asm_dasha.h"
#include <stdlib.h>
#include <stdio.h>
#include "ft_ptintf.h"

char		*parse_file_name(char *file_path)
{
	char		*name;
	int			name_len;

	name_len = ft_strlen(file_path);
	name = ft_strcat(ft_strsub(file_path, 0, name_len - 1), "cor"); //ОЧИСТКА памяти
	return (name);
}

char	*open_files(char *file_name, t_token_sec *check_list,
		t_token **token)
{
	int	fd;
	char		*name;
	t_label		*label;

	label = NULL;
	//	//проверка read'ом
	name = parse_file_name(file_name);
//	fclose(fopen(name, "w"));//fclose!!!!!!!!!!
	fd = open(file_name, O_RDONLY);
	tokenize(fd, token, &label);
	token_sequence(*token, check_list);
	label_substitution(label);
	return (name);
}

int main(int ac, char **av)
{
	t_token		*token;
	header_t	header;
	t_token_sec	check_list;
	int			i;
	char        *file_tofill;

	i = 1;
	token = NULL;
	while (i < ac)
	{
		file_tofill = open_files(av[i], &check_list, &token);
		init_headers(&header, token, &check_list);
		print_in_file(file_tofill, token, &header);
		i++;
	}

//	ml_free_all();
	return (0);
}