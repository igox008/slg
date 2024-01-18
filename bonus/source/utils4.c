/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaassir <alaassir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 19:39:17 by alaassir          #+#    #+#             */
/*   Updated: 2024/01/18 04:22:23 by alaassir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

int	mlx_fail(t_data	*i)
{
	int	j;

	j = 0;
	while (i->map[j])
	{
		free(i->map[j]);
		j++;
	}
	free(i->map);
	mlx_destroy_window(i->ptr, i->win);
	mini_printf(0, "you Pressed"RED" X "RESET"button");
	exit(0);
}

void	mlX_start_engine(t_data *i, t_img *m)
{
	i->ptr = mlx_init();
	if (!i->ptr)
	{
		mini_printf(0, RED"ERROR\nmlx init fail"RESET);
		close_window(i, EXIT_FAILURE);
	}
	i->win = mlx_new_window(i->ptr, m->width, m->height, "so_long");
	if (!i->win)
	{
		mini_printf(0, RED"ERROR\nmlx new window fail"RESET);
		close_window(i, EXIT_FAILURE);
	}
}

void	*get_image(t_data *i, char *path, int size)
{
	void	*img;

	img = mlx_xpm_file_to_image(i->ptr, path, &size, &size);
	if (!img)
	{
		// printf("%s\n", path);
		mini_printf(0, RED"asset LOAD fail!!!"RESET);
		close_window(i, EXIT_FAILURE);
	}
	return (img);
}

int	frames(t_data *i)
{
	if (clock() > i->cur + 100000)
	{
		enemy_to_move(i);
		i->cur = clock();
		mlx_do_sync(i->ptr);
	}
	if (i->keyp == UP)
		move_up(&i);
	else if (i->keyp == DOWN)
		move_down(&i);
	else if (i->keyp == LEFT)
		move_left(&i);
	else if (i->keyp == RIGHT)
		move_right(&i);
	return (i->keyp);
}
