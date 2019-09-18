/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:26:04 by anmauffr          #+#    #+#             */
/*   Updated: 2019/09/18 10:14:40 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** T_REG SIZE 1
*/

static void	ft_arg(t_vm *vm, int *pc, unsigned int *arg_value)
{
	int		i;

	i = 0;
	while (i < 3)
	{
		(*pc) += T_REG;
		arg_value[i++] = vm->arena[*pc][0] - 0x01;
	}
}

static void	exec_sub(t_vm *vm, unsigned int arg_value[3])
{
	vm->proc->r[arg_value[2]] = vm->proc->r[arg_value[0]]
		- vm->proc->r[arg_value[1]];
	vm->proc->carry = vm->proc->r[arg_value[2]] == 0 ? 1 : 0;
}

void		op_sub(t_vm *vm, int *pc)
{
	unsigned int	arg_value[3];
	
	ft_arg(vm, pc, arg_value);
	exec_sub(vm, arg_value);
	ft_visu_d_message(vm, "sub");
}
