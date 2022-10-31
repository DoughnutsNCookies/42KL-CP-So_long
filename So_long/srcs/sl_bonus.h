/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_bonus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 13:19:36 by schuah            #+#    #+#             */
/*   Updated: 2022/10/31 13:23:25 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SL_BONUS_H
# define SL_BONUS_H

# include "../libft/srcs/libft.h"
# include "../libft/srcs/get_next_line.h"
# include "../libft/srcs/ft_printf.h"
# include <mlx.h>

/* Mac key codes */
# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_UP		126
# define KEY_LEFT	123
# define KEY_DOWN	125
# define KEY_RIGHT	124
# define EXIT_EVENT	17
# define EXIT_MASK	0

/* Colors */
# define BLACK		0

/* Player prefs */
# define PLY_MVSPD	64
# define FPS		20
# define STEPS_X	16
# define STEPS_Y	8
# define PAD_Y		16

/* Vector with an x and y */
typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

/* Image info */
typedef struct s_image {
	void		*ref;
	t_vector	size;
}	t_image;

/* Player info */
typedef struct s_player
{
	int			alive;
	int			pickups;
	int			moves;
	t_vector	pos;
	t_image		image;
}	t_player;

/* A pointer to the window and its size */
typedef struct s_window {
	void		*ref;
	int			frame;
	t_vector	size;
}	t_window;

typedef struct s_tprt {
	int			t_exist;
	int			r_exist;
	t_vector	tel_pos;
	t_vector	rec_pos;
	t_image		tel_img;
	t_image		rec_img;
}	t_tprt;

/* A struct storing all map data */
typedef struct s_map {
	int			level;
	int			total_level;
	int			x;
	int			y;
	int			n_pick;
	int			start;
	int			exit;
	char		**layout;
	char		**level_lst;
	t_image		pickup_img;
	t_image		wall_img;
	t_image		exit_img;
	t_image		spc_img;
	t_image		eblock_img;
	t_tprt		tprt;
}	t_map;

/* The gamemaster or game manager that holds all the game's value */
typedef struct s_gm {
	void		*mlx;
	t_window	window;
	t_player	player;
	t_player	enemy;
	t_map		map;
}	t_gm;

/* Window functions */
int		sl_exit(t_gm *gm);
int		sl_fullexit(char *str, int fd);
int		sl_update(t_gm *gm);
void	sl_putimage(t_gm *gm);
void	sl_displaymap(t_gm *gm);
void	sl_newwindow(t_gm *gm, int height, int width, char *name);

/* Player functions */
void	sl_hooks(t_gm *gm);
void	sl_mapevents(t_gm *gm);
void	sl_enemyanim(t_gm *gm);
void	sl_playeranim(t_gm *gm);
void	sl_defaultplayer(t_gm *gm);
int		sl_getinput(int keycode, t_gm *gm);
void	sl_movement(t_gm *gm, int keycode);
void	sl_enemymovement(t_gm *gm, int keycode);
void	sl_setposplayer(t_gm *gm, int x, int y, char player);

/* Map functions */
void	sl_getmap(t_gm *gm);
void	sl_defaultmap(t_gm *gm);
void	sl_getfiles(t_gm *gm, char **av);
void	sl_checkfileformat(t_gm *gm, int ac, char **av);
void	sl_runthroughmap(t_gm *gm, char *str, char *prev, int fd);
void	sl_objectanim(t_gm *gm);

/* Helper functions */
void	sl_printply(t_gm *gm);
void	sl_printmap(t_gm *gm);
void	sl_freeeverything(t_gm *gm);

#endif