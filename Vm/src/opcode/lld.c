/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:24:59 by anmauffr          #+#    #+#             */
/*   Updated: 2019/09/26 14:04:53 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_arg(t_vm *vm, unsigned int *pc, unsigned int *arg_value,
	unsigned int *arg_size)
{
	int		i;
	int		ret;

	i = -1;
	ret = 1;
	while (++i < 2)
		if (arg_size[i] == T_REG)
		{
			(*pc) += T_REG;
			arg_size[i] = T_REG;
			arg_value[i] = vm->arena[*pc][0] - 0x01;
			if (arg_value[i] > 15)
				ret = 0;
		}
		else if (arg_size[i] == T_DIR)
		{
			(*pc) += T_IND;
			arg_size[i] = T_DIR + 1;
			arg_value[i] = vm->arena[*pc - 3][0] << 24
				| vm->arena[*pc - 2][0] << 16 | vm->arena[*pc - 1][0] << 8
				| vm->arena[*pc][0];
		}
		else if (arg_size[i] == T_IND)
		{
			(*pc) += T_DIR;
			arg_size[i] = T_IND;
			arg_value[i] = vm->arena[*pc - 1][0] << 8 | vm->arena[*pc][0];
		}
	return (ret);
}

static void	exec_lld(t_vm *vm, unsigned int arg_value[3]
	, unsigned int arg_size[3])
{
	if (arg_value[1] <= 15)
	{
		if (arg_size[0] == T_DIR + 1 || arg_size[0] == T_IND)
			vm->proc->r[arg_value[1]] = arg_value[0] < IDX_MOD
				? arg_value[0] : arg_value[0];
		vm->proc->carry = arg_value[0] == 0 ? 1 : 0;
	}
}

void		op_lld(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];
	int				save;

	(*pc)++;
	save = (*pc);
	arg_size[2] = 0;
	arg_value[2] = 0;
	arg_size[1] = T_REG;
	if (vm->arena[*pc][0] == 144)
		arg_size[0] = T_DIR;
	else if (vm->arena[*pc][0] == 208)
		arg_size[0] = T_IND;
	if (ft_arg(vm, pc, arg_value, arg_size))
	{
		if (vm->arena[save][0] == 144 || vm->arena[save][0] == 208)
		{
			exec_lld(vm, arg_value, arg_size);
			ft_visu_d_message(vm, "lld");
		}
	}
}
