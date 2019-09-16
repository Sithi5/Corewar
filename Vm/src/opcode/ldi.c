/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:25:30 by anmauffr          #+#    #+#             */
/*   Updated: 2019/09/16 10:31:30 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** T_REG SIZE 1
** T_IND SIZE 2
** T_DIR SIZE 2
*/

static void	ft_arg(t_vm *vm, int *pc, unsigned int *arg_value,
	unsigned int *arg_size)
{
	int		i;

	i = -1;
	while (++i < 3)
		if (arg_size[i] == T_REG)
		{
			(*pc) += T_REG;
			arg_size[i] = T_REG;
			arg_value[i] = vm->arena[*pc][0] - 0x01;
		}
		else if (arg_size[i] == T_DIR)
		{
			(*pc) += T_DIR;
			arg_size[i] = T_DIR;
			arg_value[i] = vm->arena[*pc - 1][0] << 8 | vm->arena[*pc][0];
		}
		else if (arg_size[i] == T_IND)
		{
			(*pc) += T_DIR;
			arg_size[i] = T_IND;
			arg_value[i] = vm->arena[*pc - 1][0] << 8 | vm->arena[*pc][0];
		}
}

static void	exec_ldi(t_vm *vm, unsigned int arg_value[3]
	, unsigned int arg_size[3])
{
	(void)arg_size;
	vm->proc->r[arg_value[2]] = (arg_value[0] + arg_value[1]) % IDX_MOD;
}

void		op_ldi(t_vm *vm, int *pc)
{
	unsigned int	arg_value[3];
	unsigned int	arg_size[3];

	(*pc)++;
	arg_size[2] = T_REG;
	if ((vm->arena[*pc][0] == 54 || vm->arena[*pc][0] == 100)
		&& (arg_size[0] = T_REG))
		arg_size[1] = vm->arena[*pc][0] == 54 ? T_REG : T_DIR;
	else if ((vm->arena[*pc][0] == 148 || vm->arena[*pc][0] == 164)
		&& (arg_size[0] = T_DIR))
		arg_size[1] = vm->arena[*pc][0] == 148 ? T_REG : T_DIR;
	else if ((vm->arena[*pc][0] == 212 || vm->arena[*pc][0] == 228)
		&& (arg_size[0] = T_IND))
		arg_size[1] = vm->arena[*pc][0] == 212 ? T_REG : T_DIR;
	else
		ft_error(ERROR_LDI, vm->proc->n_champ, vm);
	ft_arg(vm, pc, arg_value, arg_size);
	exec_ldi(vm, arg_value, arg_size);
}