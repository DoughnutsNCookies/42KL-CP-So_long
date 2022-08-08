/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_enemy_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:26:22 by schuah            #+#    #+#             */
/*   Updated: 2022/08/04 17:30:46 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sl_bonus.h"

/* Plays the enemy animation every FPS frames */
void	sl_enemyanim(t_gm *gm)
{
	if (gm->enemy.alive == 0)
		return ;
	if (gm->window.frame == FPS)
		gm->enemy.pos.y += 1;
	else if (gm->window.frame >= FPS * 2)
		gm->enemy.pos.y -= 1;
	mlx_put_image_to_window(gm->mlx, gm->window.ref,
		gm->enemy.image.ref, gm->enemy.pos.x, gm->enemy.pos.y);
}

/* Moves the enemy depending on the keycode pressed. 
** Also Checks whether the move is possible (ie. Wall and Pickups) */
void	sl_enemymovement(t_gm *gm, int keycode)
{
	if (gm->enemy.alive == 0)
		return ;
	if (keycode == KEY_UP && (gm->map.layout[(gm->enemy.pos.y / PLY_MVSPD) - 1]
			[gm->enemy.pos.x / PLY_MVSPD] != '1'))
		if ((gm->map.layout[(gm->enemy.pos.y / PLY_MVSPD) - 1]
				[gm->enemy.pos.x / PLY_MVSPD] != 'C'))
			gm->enemy.pos.y -= PLY_MVSPD;
	if (keycode == KEY_LEFT && (gm->map.layout[(gm->enemy.pos.y / PLY_MVSPD)]
			[(gm->enemy.pos.x / PLY_MVSPD) - 1] != '1'))
		if ((gm->map.layout[(gm->enemy.pos.y / PLY_MVSPD)]
				[(gm->enemy.pos.x / PLY_MVSPD) - 1] != 'C'))
			gm->enemy.pos.x -= PLY_MVSPD;
	if (keycode == KEY_DOWN && (gm->map.layout[(gm->enemy.pos.y / PLY_MVSPD)
				+ 1][gm->enemy.pos.x / PLY_MVSPD] != '1'))
		if ((gm->map.layout[(gm->enemy.pos.y / PLY_MVSPD)
					+ 1][gm->enemy.pos.x / PLY_MVSPD] != 'C'))
			gm->enemy.pos.y += PLY_MVSPD;
	if (keycode == KEY_RIGHT && (gm->map.layout[(gm->enemy.pos.y / PLY_MVSPD)]
			[(gm->enemy.pos.x / PLY_MVSPD) + 1] != '1'))
		if ((gm->map.layout[(gm->enemy.pos.y / PLY_MVSPD)]
				[(gm->enemy.pos.x / PLY_MVSPD) + 1] != 'C'))
			gm->enemy.pos.x += PLY_MVSPD;
}
