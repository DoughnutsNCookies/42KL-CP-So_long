/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_hook_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:10:47 by schuah            #+#    #+#             */
/*   Updated: 2022/08/06 17:21:26 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sl_bonus.h"

/* Will run through everything in this function each time a key is pressed */
int	sl_getinput(int keycode, t_gm *gm)
{
	mlx_clear_window(gm->mlx, gm->window.ref);
	if (keycode == KEY_ESC)
		sl_fullexit("Thanks for playing!", 1);
	sl_movement(gm, keycode);
	sl_enemymovement(gm, keycode);
	sl_putimage(gm);
	sl_mapevents(gm);
	return (0);
}

/* Will run through everything in this function every frame */
int	sl_update(t_gm *gm)
{
	gm->window.frame++;
	sl_putimage(gm);
	sl_objectanim(gm);
	sl_playeranim(gm);
	sl_enemyanim(gm);
	if (gm->window.frame >= FPS * 2)
		gm->window.frame = 0;
	return (0);
}

/* Performs a full exit after freeing everything */
int	sl_fullexit(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	exit(fd - 1);
	return (0);
}

/* Also performs a full exit but especially made for mlx_hook */
static int	sl_crossexit(void)
{
	ft_printf("Thanks for playing!\n");
	exit(0);
	return (0);
}

/* Determines which function to run depending on the button pressed */
void	sl_hooks(t_gm *gm)
{
	mlx_hook(gm->window.ref, EXIT_EVENT, EXIT_MASK,
		&sl_crossexit, "Thanks for playing!\n");
	mlx_key_hook(gm->window.ref, &sl_getinput, gm);
	mlx_loop_hook(gm->mlx, &sl_update, gm);
}
