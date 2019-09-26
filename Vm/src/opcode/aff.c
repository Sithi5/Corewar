/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:24:51 by anmauffr          #+#    #+#             */
/*   Updated: 2019/09/26 12:34:19 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	ft_arg(t_vm *vm, unsigned int *pc, unsigned int *arg_value)
{
	(*pc) = (*pc + T_REG) % MEM_SIZE;
	(*arg_value) = vm->arena[*pc][0] - 0x01;
	return (*arg_value > 15 ? 0 : 1);
}

static void	exec_aff(t_vm *vm, unsigned int arg_value)
{
	vm->option_visu == 0 && vm->option_visu_d == 0
		? ft_printf("%c", vm->proc->r[arg_value] % 256) : 0;
}

void		op_aff(t_vm *vm, unsigned int *pc)
{
	unsigned int	arg_value;

	(*pc) = (*pc + 1) % MEM_SIZE;
	if (ft_arg(vm, pc, &arg_value))
	{
		exec_aff(vm, arg_value);
		ft_visu_d_message(vm, "aff");
	}
}
