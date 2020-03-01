
#include <stdbool.h>
#include <stdio.h>
#include "libft.h"
#include "asm.h"
#include "asm_dasha.h"


int	token_exit(char *error, u_int32_t row, u_int32_t column)
{
	if (error)
		printf("%s, [row: %d, column: %d]\n", error, row, column);
	exit(1);
	return (0);
}

void 	init_check_list(t_token_sec **check_list)
{
	*check_list = (t_token_sec*)ml_malloc(sizeof(t_token_sec), ML_CHECK_LST);
	(*check_list)->arg = false;
	(*check_list)->command = false;
	(*check_list)->comment = false;
	(*check_list)->comment_prog = false;
	(*check_list)->separator = false;
	(*check_list)->str_comment = false;
	(*check_list)->str_name = false;
	(*check_list)->name = false;
	(*check_list)->new_line = true;
	(*check_list)->new_line_name = false;
	(*check_list)->new_line_comment = false;
	(*check_list)->label = false;
}

void	if_str_check(t_token *token, t_token_sec *check_list)
{
	if (token->type == STRING)
	{
		if (check_list->name && !check_list->comment_prog)
		{
			check_list->str_name = true;
			check_list->new_line = false;
		}
		else if (check_list->comment_prog && !check_list->label)
		{
			check_list->str_comment = true;
			check_list->new_line = false;
		}
		else
			token_exit("ERROR: Champion's file contains error",
														token->row, token->column);
	}
}

void	if_command_label(t_token *token, t_token_sec *check_list)
{
	if (token->type == LABEL)
	{
		if (!check_list->new_line)
			token_exit("ERROR: Champion's comment should be separated"
						  " with new line from label", token->row, token->column);
		else if (!check_list->str_comment)
			token_exit("ERROR: Champion should have comment before label",
														token->row, token->column);
		else
		{
			check_list->arg = false;
			check_list->label = true;
		}
	}
	else if (token->type == COMMAND)
	{
		if (!check_list->label)
			token_exit("ERROR: Command should only follow some label",
														token->row, token->column);
		else
			check_list->command = true;
	}
}

void	if_arg(t_token *token, t_token_sec *check_list)
{
	if (token->type == ARGUMENT)
	{
		if (!check_list->command)
			token_exit("ERROR: Arguments should be preceded by command name",
														token->row, token->column);
		else
		{
			if (!check_list->arg)
			{
				check_list->new_line = false;
				check_list->separator = false;
				check_list->arg = true;
			}
			else
				if (!check_list->separator)
					token_exit("ERROR: Arguments should be separated",
														token->row, token->column);
		}
	}
}

void	if_comment_prog(t_token *token, t_token_sec *check_list)
{
	if (token->type == COMMENT_PROG)
	{
		if (!check_list->str_name)
			token_exit("ERROR: Champion should have name before comment",
													   token->row, token->column);
		if (!check_list->new_line)
			token_exit("ERROR: Champion's name should be separated"
					   " with new line from comment", token->row, token->column);
		if (check_list->comment_prog)
			token_exit("ERROR: Champion can have only one"
										   " comment", token->row, token->column);
		else
			check_list->comment_prog = true;
	}
}

void	if_name(t_token *token, t_token_sec *check_list)
{
	if (token->type == NAME)
	{
		if (!check_list->name)
			check_list->name = true;
		else
			token_exit("ERROR: Champion can have only one name",
					   token->row, token->column);
	}
}

_Bool			token_sequence(t_token *token)
{
	t_token_sec	*check_list;
	t_token		*token_arr;

	token_arr = token;
	init_check_list(&check_list);
	while (token != NULL)
	{
		if (token->type == NEW_LINE)
			check_list->new_line = true;
		else if (token->type == COMMENT)
			;
		else if (token->type == SEPARATOR)
			check_list->separator = true;
		if_name(token, check_list);
		if_comment_prog(token, check_list);
		if_str_check(token, check_list);
		if_command_label(token, check_list);
		if_arg(token, check_list);
		token = token->next;
	}
	token = token_arr;
}

void	main()
{
	t_token *new1;
	t_token *new2;
	t_token *new3;
	t_token *new4;
	t_token *new5;
	t_token *new6;
	t_token *new7;
	t_token *new8;
	t_token *new9;
	t_token *new0;


	new9 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new9->row = 1;
	new9->column = 2;
	new9->type = NEW_LINE;
	new9->next = NULL;

	new8 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new8->row = 1;
	new8->column = 2;
	new8->type = STRING;
	new8->next = new9;

	new7 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new7->row = 1;
	new7->column = 2;
	new7->type = COMMENT_PROG;
	new7->next = new8;


	new6 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new6->row = 1;
	new6->column = 2;
	new6->type = NEW_LINE;
	new6->next = new7;

	new5 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new5->row = 1;
	new5->column = 2;
	new5->type = STRING;
	new5->next = new6;

	new4 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new4->row = 1;
	new4->column = 2;
	new4->type = NEW_LINE;
	new4->next = new5;

	new3 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new3->row = 1;
	new3->column = 2;
	new3->type = STRING;
	new3->next = new4;

	new2 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new2->row = 1;
	new2->column = 2;
	new2->type = NEW_LINE;
	new2->next = new3;

	new1 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new1->row = 1;
	new1->column = 1;
	new1->type = STRING;
	new1->next = new2;

	new0 = (t_token*)ml_malloc(sizeof(t_token), ML_TOKEN);
	new0->row = 10;
	new0->column = 2;
	new0->type = NAME;
	new0->next = new1;

	token_sequence(new0);
}