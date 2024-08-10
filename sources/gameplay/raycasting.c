/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:52:18 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/10 14:47:57 by aggrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void 	draw_line(int x0, int y0, int x1, int y1, int color, t_img *img);
void	draw_square(t_img *img, int x1, int y1, int size, int color);
void	draw_mini_map(t_game_info *game);
void	draw_player(t_game_info *game);

# define CELL_SZ 25

int	draw_scene(t_game_info *game)
{
	mlx_clear_window(game->mlx, game->win);

	// draw_clg_and_flr();
	// for (int i = 0; i < WIN_H / 2; i++)
	// 	for (int j = 0; j < WIN_W; j++)
	// 		my_mlx_pixel_put(&game->img, j, i, game->texs.clg);
	// for (int i = WIN_H / 2; i < WIN_H; i++)
	// 	for (int j = 0; j < WIN_W; j++)
	// 		my_mlx_pixel_put(&game->img, j, i, game->texs.flr);
	draw_mini_map(game);
	draw_player(game);
	// raycasting(game);
	// printf("PLAYER POSITION:\nX:%lf Y:%lf\n", game->pl.posX, game->pl.posY);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	my_mlx_image_clear(&game->img);
	return (0);
}

void	draw_player(t_game_info *game)
{
	draw_square(&game->img, (CELL_SZ * game->pl.posY) + 1,( CELL_SZ * game->pl.posX) + 1, CELL_SZ - 2, create_trgb(0, 250, 102, 0));
	// draw_square(&game->img, CELL_SZ * game->pl.posY + 1, CELL_SZ * game->pl.posX + 1, CELL_SZ, create_trgb(0, 204, 102, 0));
	double x1, y1, x2, y2;
	x1 = (CELL_SZ * game->pl.posY) + (CELL_SZ / 2.0);
	y1 = (CELL_SZ * game->pl.posX) + (CELL_SZ / 2.0);
	x2 = x1 + (game->pl.dirX * 30);
	y2 = y1 + (game->pl.dirY * 30);
	// // x2 = x1 + game->pl.dirX;
	// // y2 = y1 + game->pl.dirY;
	draw_line(x1, y1, x2, y2, create_trgb(0, 255, 100, 0), &game->img);
	printf("X:%lf Y:%lf\nX:%lf Y:%lf New\n", x1, y1, x2, y2);
}

void	draw_mini_map(t_game_info *game)
{
	t_line *map;

	map = game->map;
	int		i;
	int		j;
	int		x1;
	int		y1;

	i = 0;
	while (map[i].val != NULL)
	{
		j = 0;
		while (map[i].val[j] != '\0')
		{
			// horizontal
			x1 = CELL_SZ * j;
			y1 = CELL_SZ * i;
			
			if (map[i].val[j] == '1')
				draw_square(&game->img, x1, y1, CELL_SZ, create_trgb(0,204, 255, 204));
			else if (map[i].val[j] == '0')
				draw_square(&game->img, x1, y1, CELL_SZ, create_trgb(0, 255, 255, 255));
			else if (map[i].val[j] == ' ')
				draw_square(&game->img, x1, y1, CELL_SZ, create_trgb(0, 33, 33, 33));
			else if (map[i].val[j] == 'D')
				draw_square(&game->img, x1, y1, CELL_SZ, create_trgb(0, 100, 100, 255));
			j++;
		}
		i++;
	}
}

void	raycasting(t_game_info *game)
{	
	// init variables for loop of wall raycasting
	int x;
	int mapX, mapY;
	double cameraX, rayDirX, rayDirY;
	double deltaDistX, deltaDistY;
	// loop for wall raycasting
	x = 0;
	while (x < WIN_W)
	{
		mapX = (int) game->pl.posX;
		mapY = (int) game->pl.posY;

		cameraX = 2 * x / (double)WIN_W - 1;
		rayDirX = game->pl.dirX + game->pl.planeX * cameraX;
		rayDirY = game->pl.dirY + game->pl.planeY * cameraX;
		
		deltaDistX = ternard(rayDirX == 0, 1e30, fabs(1 / rayDirX));
		deltaDistY = ternard(rayDirY == 0, 1e30, fabs(1 / rayDirY));

		//calculate step and initaial sideDist
		int side;  //was a NS or a EW wall hit?
		int stepX, stepY; //what direction to step in x or y-direction (either +1 or -1)
		double sideDistX, sideDistY;
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->pl.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->pl.posX) * deltaDistX;
		}
		if(rayDirY < 0)
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
			if(game->map[mapX].val[mapY] > 0)
				hit = 1;
		}
		x++;
	}
}

void draw_line(int x0, int y0, int x1, int y1, int color, t_img *img)
{
	
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1) {
		// put_pixel(x0, y0); // Draw the current pixel
		my_mlx_pixel_put(img, x0, y0, color);

		if (x0 == x1 && y0 == y1) {
			break; // If we have reached the end point, exit the loop
		}

		int e2 = 2 * err;

		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}

		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}
// {  
// 	int dx, dy, p, x, y;  
// 	dx=x1-x0;
// 	dy=y1-y0;
// 	x=x0;
// 	y=y0;
// 	p=2*dy-dx;
// 	while(x<x1)
// 	{
// 		if(p>=0)
// 		{
// 			my_mlx_pixel_put(img, x, y, color);
// 			// putpixel(x,y,7);
// 			y=y+1;
// 			p=p+2*dy-2*dx;
// 		}
// 		else
// 		{
// 			my_mlx_pixel_put(img, x, y, color);
// 			// putpixel(x,y,7);
// 			p=p+2*dy;}
// 			x=x+1;
// 		}
// }

void	draw_square(t_img *img, int x1, int y1, int size, int color)
{
	int i = x1, j = y1;
	
	while (i < x1 + size + 1)
	{
		j = y1;
		while (j < y1 + size + 1)
		{
			my_mlx_pixel_put(img, i, j, color);
			j++;
		}
		i++;
	}
}
