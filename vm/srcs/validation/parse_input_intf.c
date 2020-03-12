#include "vm.h"

_Bool	is_flg(const char *arg, t_flgs *flgs)
{
	_Bool	good;

	good = 1;
	if (!ft_strcmp(arg, "-n"))
		flgs->flgs |= N_FLG;
	else if (!ft_strcmp(arg, "-dump"))
	{
		if (flgs->flgs & DUMP_FLG)
			get_error("The dump flag is already existent");
		flgs->flgs |= DUMP_FLG;
	}
	else if (!ft_strcmp(arg, "-a"))
	{
		if (flgs->flgs & A_FLG)
			get_error("The a flag is already existent");
		flgs->flgs |= A_FLG;
	}
	else
		good = 0;
	return (good);
}

_Bool	is_champion(const char *arg, t_corewar *corewar)
{
	char	*lst_dot;

	lst_dot = ft_strrchr(arg, '.');
	if (!lst_dot || ft_strcmp(lst_dot + 1, "cor"))
		return (0);
//		get_error("Champion file should contain .cor completion");
	push_back_champ(&corewar->champs, arg);
	if (corewar->flgs.flgs & N_FLG)
	{
		if (is_there_same_champ_num(corewar->champs,
				corewar->flgs.nxt_player_num))
			get_error("Number after one of -n flg is already exists");
		corewar->champs->lst->num = corewar->flgs.nxt_player_num;
	}
	return (1);
}

void	reverse_bytes(unsigned int *num_to_rev)
{
	unsigned int	rev;
	unsigned int	byte;
	unsigned int	i;

	rev = 0;
	i = 0;
	while (i < 32)
	{
		byte = *num_to_rev >> i & 0xFFu;
		rev |= byte << (32u - 8u - i);
		i += 8;
	}
	*num_to_rev = rev;
}

int		max_champs_num(t_champion *champs)
{
	int		max_num;

	max_num = champs->num;
	champs = champs->next;
	while (champs)
	{
		if (champs->num > max_num)
			max_num = champs->num;
		champs = champs->next;
	}
	return (max_num);
}

_Bool	is_there_same_champ_num(t_champion *champs, const int nxt_player_num)
{
	while (champs)
	{
		if (champs->num == nxt_player_num)
			return (1);
		champs = champs->next;
	}
	return (0);
}