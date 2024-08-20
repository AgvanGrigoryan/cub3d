/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aggrigor <aggrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 10:52:18 by aggrigor          #+#    #+#             */
/*   Updated: 2024/08/11 19:49:19 by aggrigor         ###   ########.fr       */
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
	// raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	my_mlx_image_clear(&game->img);
	return (0);
}

void	draw_player(t_game_info *game)
{
	int	line_len = 50;
	draw_square(&game->img, (CELL_SZ * game->pl.posY) + 1,( CELL_SZ * game->pl.posX) + 1, CELL_SZ - 2, create_trgb(0, 102, 153, 153));
	// draw_square(&game->img, CELL_SZ * game->pl.posY + 1, CELL_SZ * game->pl.posX + 1, CELL_SZ, create_trgb(0, 204, 102, 0));
	double x1, y1, x2, y2;
	x1 = (CELL_SZ * game->pl.posY) + (CELL_SZ / 2.0);
	y1 = (CELL_SZ * game->pl.posX) + (CELL_SZ / 2.0);

	// Rotate the direction vector to the left by 66 degrees
	double leftDirX = game->pl.dirX * cos(0.66) - game->pl.dirY * sin(0.66);
	double leftDirY = game->pl.dirX * sin(0.66) + game->pl.dirY * cos(0.66);

	// Rotate the direction vector to the right by 66 degrees
	double rightDirX = game->pl.dirX * cos(-0.66) - game->pl.dirY * sin(-0.66);
	double rightDirY = game->pl.dirX * sin(-0.66) + game->pl.dirY * cos(-0.66);
	x2 = x1 + (leftDirX * line_len);
	y2 = y1 + (leftDirY * line_len);
	draw_line(x1, y1, x2, y2, create_trgb(0, 0, 102, 255), &game->img);
	x2 = x1 + (rightDirX * line_len);
	y2 = y1 + (rightDirY * line_len);
	draw_line(x1, y1, x2, y2, create_trgb(0, 0, 102, 255), &game->img);
	draw_line(x2, y2, x1 + (leftDirX * line_len), y1 + (leftDirY * line_len), create_trgb(0, 0, 102, 255), &game->img);
	draw_line(x1, y1, x1 + (game->pl.dirX * (50 / 2) / tan(0.66 / 2)), y1 + (game->pl.dirY * (50 / 2) / tan(0.66 / 2)), create_trgb(0, 255, 0, 0), &game->img);

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
			else if (map[i].val[j] == ' ')
				draw_square(&game->img, x1, y1, CELL_SZ, create_trgb(0, 33, 33, 33));
			else if (map[i].val[j] == 'D')
				draw_square(&game->img, x1, y1, CELL_SZ, create_trgb(0, 100, 100, 255));
			else if (map[i].val[j] == '0' || (map[i].val[j] == 'W' || map[i].val[j] == 'N'
				|| map[i].val[j] == 'S' || map[i].val[j] == 'E'))
				draw_square(&game->img, x1, y1, CELL_SZ, create_trgb(0, 255, 255, 255));
			j++;
		}
		i++;
	}
	draw_player(game);
}

/*
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
			if(game->map[mapX].val[mapY] > 0)
				hit = 1;
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

		int texNum = (game->map[mapX].val[mapY] - 48) - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0) wallX = game->pl.posY + perpWallDist * rayDirY;
		else           wallX = game->pl.posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
	
		//x coordinate on the texture
		int texX = (int) (wallX * (double) texWidth);
		if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
		if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;
		x++;
	}
}
*/
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
