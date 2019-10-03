/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idx_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmauffr <anmauffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:26:13 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/03 16:14:50 by anmauffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned int	idx_mod(unsigned int realpc, unsigned int jump)
{
	ft_printf("%u\n", jump > 32768 ? (realpc - (-jump % IDX_MOD)) % MEM_SIZE : (realpc + jump % IDX_MOD) % MEM_SIZE);
	return (jump > 32768 ? (realpc - (-jump % IDX_MOD)) % MEM_SIZE
		: (realpc + jump % IDX_MOD) % MEM_SIZE);
}
