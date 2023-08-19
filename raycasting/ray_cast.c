/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:27:06 by azarda            #+#    #+#             */
/*   Updated: 2023/08/19 22:01:39 by azarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// float norm(float raymagic)
// {
// 	raymagic = remainder(raymagic, TWO_PI);
// 	if(raymagic < 0)
// 	{
// 		raymagic =  TWO_PI + raymagic;
// 	}
// 	return(raymagic);
// }

// void castoneray(float raymagic, int i)
// {
// 	raymagic = norm(raymagic);


// }

// void ray_cast(t_global *pub)
// {
// 	t_player player = pub.info->player;

// 	// printf("--> %p\n", player);
// 	double raymagic = player.rotation_angle - (FOV_ANGLE / 2);
// 	int i = 0;
// 	while (i < WIDTH)
// 	{
// 		castoneray(raymagic, i);
// 		raymagic += FOV_ANGLE / WIDTH;
// 		i++;
// 	}

// }


void ray_cast(t_global *pub)
{

	t_player player = pub->info->player;
	
	// player.rotation_angle *= P_ROTATION_SPEED;
//-----------------------------------------------------------------------------------------------------------------------
	double new_x;
	double new_y;
	
	new_y = floor(player.pos.y / SQUARE_LEN) * SQUARE_LEN ;
	if(player.rotation_angle > PI &&  player.rotation_angle < 0)
		new_y += SQUARE_LEN;
	new_x = player.pos.x + (new_y - player.pos.y) / tan(player.rotation_angle);

//-----------------------------------------------------------------------------------------------------------------------

	double new_step_x;
	double new_step_y;

	
	new_step_y = SQUARE_LEN;
	new_step_x = SQUARE_LEN / tan(player.rotation_angle);
	
	double test_x = new_step_x;
	double test_y = new_step_y;
	
	
	// while (pub->info->map[(int)new_step_x][(int)new_step_y] != '1')
	// {
	// 	new_step_x += test_x; 
	// 	new_step_y += test_y; 
	// }
	
	int test = (int)(new_step_x / SQUARE_LEN);
	
	printf("new x int  %d\n", test);

	// exit(0);

	// printf("yaha  ->>  %c\n ", pub->info->map[(int)new_y][(int)new_x]);
	
	new_x += new_step_x;
	new_y += new_step_y;

//------------------------------------------------------------passto_draw-------------------------------------------------------
	printf("------------------------ray cast ------------------\n");


	printf("x.player ===== %f\n", player.pos.x);
	printf("y.player ===== %f\n", player.pos.y);

	printf("x ===== %f\n", new_x);
	printf("y ===== %f\n", new_y);
	pub->tess_x = new_x;
	pub->tess_y = new_y;
//-----------------------------------------------------------------------------------------------------------------------


	// draw_line(pub->window_img, player.pos, (t_pos){.x = player.pos.x + (cos(player.rotation_angle) * 30), .y = player.pos.y + (sin(player.rotation_angle) * 30)});
	
	// draw_line(pub->window_img, player.pos, (t_pos){.x = player.pos.x + (cos(player.rotation_angle) * 30), .y = player.pos.y + (sin(player.rotation_angle) * 30)});
	printf("==|%f|==\n",player.rotation_angle);
	// exit(0);



}
