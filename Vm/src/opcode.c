/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcode.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmauffr <anmauffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 11:11:05 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/01 11:20:16 by anmauffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	ft_choise_opcode_suite(t_vm *vm, unsigned int *pc,
	unsigned char opcode)
{
	if (opcode == 10)
		op_ldi(vm, pc);
	else if (opcode == 11)
		op_sti(vm, pc);
	else if (opcode == 12)
		op_fork(vm, pc);
	else if (opcode == 13)
		op_lld(vm, pc);
	else if (opcode == 14)
		op_lldi(vm, pc);
	else if (opcode == 15)
		op_lfork(vm, pc);
	else if (opcode == 16)
		op_aff(vm, pc);
}

void		ft_choise_opcode(t_vm *vm, unsigned int *pc, unsigned char opcode)
{
	if (opcode == 1)
		op_live(vm, pc);
	else if (opcode == 2)
		op_ld(vm, pc);
	else if (opcode == 3)
		op_st(vm, pc);
	else if (opcode == 4)
		op_add(vm, pc);
	else if (opcode == 5)
		op_sub(vm, pc);
	else if (opcode == 6)
		op_and(vm, pc);
	else if (opcode == 7)
		op_or(vm, pc);
	else if (opcode == 8)
		op_xor(vm, pc);
	else if (opcode == 9)
		op_zjmp(vm, pc);
	else
		ft_choise_opcode_suite(vm, pc, opcode);
}

static void	ft_wait_suite(t_vm *vm, unsigned char opcode)
{
	if (opcode == 10)
		vm->proc->wait = vm->cycle + 25;
	else if (opcode == 11)
		vm->proc->wait = vm->cycle + 25;
	else if (opcode == 12)
		vm->proc->wait = vm->cycle + 800;
	else if (opcode == 13)
		vm->proc->wait = vm->cycle + 10;
	else if (opcode == 14)
		vm->proc->wait = vm->cycle + 50;
	else if (opcode == 15)
		vm->proc->wait = vm->cycle + 1000;
	else if (opcode == 16)
		vm->proc->wait = vm->cycle + 2;
	else
	{
		vm->proc->pc = (vm->proc->pc + 1) % MEM_SIZE;
		vm->proc->wait = vm->cycle + 1;
	}
}

void		ft_wait(t_vm *vm, unsigned char opcode)
{
	vm->proc->opcode = opcode;
	if (opcode == 1)
		vm->proc->wait = vm->cycle + 10;
	else if (opcode == 2)
		vm->proc->wait = vm->cycle + 5;
	else if (opcode == 3)
		vm->proc->wait = vm->cycle + 5;
	else if (opcode == 4)
		vm->proc->wait = vm->cycle + 10;
	else if (opcode == 5)
		vm->proc->wait = vm->cycle + 10;
	else if (opcode == 6)
		vm->proc->wait = vm->cycle + 6;
	else if (opcode == 7)
		vm->proc->wait = vm->cycle + 6;
	else if (opcode == 8)
		vm->proc->wait = vm->cycle + 6;
	else if (opcode == 9)
		vm->proc->wait = vm->cycle + 20;
	else
		ft_wait_suite(vm, opcode);
	ft_visu_wait(vm);
}

void		ft_visu_wait(t_vm *vm)
{
	char	*str;

	if (vm->option_visu_d == 1)
	{
		wattron(vm->visu.hud, A_BOLD);
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 + vm->nb_champ
			* 4, 61, "                                         ");
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 + vm->nb_champ
			* 4, 61, "Need to wait : ");
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 + vm->nb_champ
			* 4, 77, (str = ft_itoa(vm->proc->wait - vm->cycle)));
		ft_strdel(&str);
		mvwprintw(vm->visu.hud, 26 + (vm->proc->n_champ - 1) * 2 + vm->nb_champ
			* 4, 78 + ft_strlen((str = ft_itoa(vm->proc->wait - vm->cycle))),
			"cycles.");
		ft_strdel(&str);
		wrefresh(vm->visu.hud);
	}
}
