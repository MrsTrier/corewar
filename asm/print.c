//
// Created by Mort Deanne on 04/03/2020.
//

#include <stdio.h>
#include <libft/libft.h>
#include "asm.h"

char *print_cmd_name(t_token *token, u_int8_t flag)
{
	if (token->type != COMMAND)
		return (NULL);
	if (!flag)
		return ((char*)token->content);
	return (ft_itoa((int)*(u_int8_t*)token->content));
}

void print_token(t_token *t)
{
	int flag = 0;
	printf("[%s", g_type[t->type - 1]);
	if (t->type == COMMAND || t->type == STRING)
		printf(":%s", (char*)t->content);
	else if (t->type == ARGUMENT || t->type == ARGUMENT_LABEL)
	{
		if (t->type == ARGUMENT_LABEL)
		{
			flag = 1;
			((t_arg*)t->content)->type = ((t_arg*)t->content)->type & ~8;
		}
		printf(":%s", g_type[((t_arg*)t->content)->type + 10]);
		if (!flag)
			printf(":%d", ((t_arg*)t->content)->num);
		else
			printf(":%s", ((t_label*)((t_arg*)t->content)->content)->name);
	}
	else if (t->type == LABEL)
		printf(":%s", ((t_label*)t->content)->name);
	printf("] ");
}

void print_tokens(t_token *token, u_int8_t setting)
{
	while (token->prev && token->prev/*token->prev->type != NEW_LINE*/)
		token = token->prev;
	printf("-");
	while (token)
	{
		if (!setting)
			printf("[%s] ", g_type[token->type - 1]);
		else
			print_token(token);
		if (token->type == NEW_LINE)
			printf("\n");
		token = token->next;
	}
	system("clear");
}