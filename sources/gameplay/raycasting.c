/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natamazy <natamazy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:52:18 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/30 21:51:01 by natamazy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	draw_line(t_ipoint p1, t_ipoint p2, int color, t_img *img);
void	draw_square(t_img *img, t_ipoint xy, int size, int color);
void	draw_mini_map(t_game_info *game);
void	draw_player(t_game_info *game, double s_i, double s_j);

void	draw_clg_and_flr(t_game_info *game)
{
	for (int i = 0; i < WIN_H / 2; i++)
		for (int j = 0; j < WIN_W; j++)
			my_mlx_pixel_put(&game->img, j, i, game->texs.clg);
	for (int i = WIN_H / 2; i < WIN_H; i++)
		for (int j = 0; j < WIN_W; j++)
			my_mlx_pixel_put(&game->img, j, i, game->texs.flr);
}

void	choose_color(t_game_info *game, t_line *map, t_ipoint ij, t_dpoint	s)
{
	t_ipoint	xy;

	xy.x = CELL_SZ * (ij.y - s.y);
	xy.y = CELL_SZ * (ij.x - s.x);
	if (map[ij.x].val[ij.y] == '1')
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 204, 255, 204));
	else if (map[ij.x].val[ij.y] == 'D')
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 100, 100, 255));
	else if (map[ij.x].val[ij.y] == 'C')
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 69, 169, 69));
	else if (map[ij.x].val[ij.y] == '0' || (map[ij.x].val[ij.y] == 'W'
			|| map[ij.x].val[ij.y] == 'N'
			|| map[ij.x].val[ij.y] == 'S' || map[ij.x].val[ij.y] == 'E'))
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 255, 255, 255));
	else if (map[ij.x].val[ij.y] == ' ')
		draw_square(&game->img, xy, CELL_SZ, create_trgb(0, 33, 33, 33));
}

char	*getTexture(t_game_info *game, int hit, int side, t_dpoint ray_dir)
{
	if (hit == 2)
		return (game->texs.dopen.addr);
	if (hit == 3)
		return (game->texs.dclose.addr);
	if (side == 1 && ray_dir.y <= 0)
		return (game->texs.no.addr);
	if (side == 0 && ray_dir.x > 0)
		return (game->texs.so.addr);
	if (side == 0 && ray_dir.x <= 0)
		return (game->texs.ea.addr);
	return (game->texs.we.addr);
}

void	raycasting(t_game_info *game)
{
	// init variables for loop of wall raycasting
	int	x;
	int	mapX;
	int	mapY;
	double cameraX;
	t_dpoint ray_dir;
	double deltaDistX, deltaDistY;
	// loop for wall raycasting
	x = 0;
	while (x < WIN_W)
	{
		mapX = (int) game->pl.posX;
		mapY = (int) game->pl.posY;

		cameraX = 2 * x / (double)WIN_W - 1;
		ray_dir.x = game->pl.dirX + game->pl.planeX * cameraX;
		ray_dir.y = game->pl.dirY + game->pl.planeY * cameraX;
		
		deltaDistX = ternard(ray_dir.x == 0, 1e30, fabs(1 / ray_dir.x));
		deltaDistY = ternard(ray_dir.y == 0, 1e30, fabs(1 / ray_dir.y));

		//calculate step and initaial sideDist
		int stepX, stepY; //what direction to step in x or y-direction (either +1 or -1)
		double sideDistX, sideDistY;
		if(ray_dir.x < 0)
		{
			stepX = -1;
			sideDistX = (game->pl.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->pl.posX) * deltaDistX;
		}
		if(ray_dir.y < 0)
		{
			stepY = -1;
			sideDistY = (game->pl.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->pl.posY) * deltaDistY;
		}
		// perform DDA
		int hit;
		int side;  //was a NS or a EW wall hit?

		hit = 0;
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			// CHECK are mapX and mapY in the correct range(0 < mapX/mapY < size) AND on map[mapX] is greather elements than mapY
			if (game->map[mapX].val[mapY] == '1')
				hit = 1;
			else if (game->map[mapX].val[mapY] == 'C')
				hit = 2;
			else if (game->map[mapX].val[mapY] == 'D')
				hit = 3;
		}
		double perpWallDist;
		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		
		int lineHeight = (int)(WIN_H / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WIN_H / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_H / 2;
		if(drawEnd >= WIN_H) drawEnd = WIN_H - 1;

		// int texNum = (game->map[mapX].val[mapY] - 48) - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = game->pl.posY + perpWallDist * ray_dir.y;
		else           wallX = game->pl.posX + perpWallDist * ray_dir.x;
		wallX -= floor((wallX));

      //x coordinate on the texture
		int texX = (int)(wallX * (double)game->texs.ea.w);
		if(side == 0 && ray_dir.x > 0)
			texX = game->texs.ea.w - texX - 1;
		if(side == 1 && ray_dir.y < 0)
			texX =	game->texs.ea.w - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * 64 / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - WIN_H / 2 + lineHeight / 2) * step;
	int	y;
	y = drawStart;
	while (++y < drawEnd)
	{
		int texY = (int)texPos & (game->texs.ea.w - 1);
		texPos += step;
		int color = *(((unsigned int *)getTexture(game, hit, side, ray_dir)) + (game->texs.ea.h * texY + texX));

		if(side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&game->img, x, y, color);
	}
	x++;
	}
}

void	process_line(t_ipoint *d, t_ipoint *s, t_ipoint *e, t_ipoint *p1)
{
	e->y = 2 * e->x;
	if (e->y > -d->y)
	{
		e->x -= d->y;
		p1->x += s->x;
	}
	if (e->y < d->x)
	{
		e->x += d->x;
		p1->y += s->y;
	}
}
