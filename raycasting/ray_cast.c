/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:27:06 by azarda            #+#    #+#             */
/*   Updated: 2023/08/20 00:39:43 by azarda           ###   ########.fr       */
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



float    normalize_angle(float angle)
{
    angle = remainder(angle, (M_PI * 2));
    if (angle < 0)
        angle = (M_PI * 2) + angle;
    return (angle);
}


void ray_cast(t_global *pub)
{

	t_player player = pub->info->player;
	int is_down = 0;
	int is_up = 0;

    player.rotation_angle = normalize_angle(player.rotation_angle);
    if (player.rotation_angle > 0 && player.rotation_angle < M_PI)
        is_down = 1;
    	is_up = !is_down;
    // if (player.rotation_angle < 0.5 * M_PI || player.rotation_angle > 1.5 * M_PI)
    //     maps->hit.is_right = 1;
    // maps->hit.is_left = !maps->hit.is_right;

	// player.rotation_angle *= P_ROTATION_SPEED;




	printf("angl rey cast  ---->>> %f\n", player.rotation_angle);



//-----------------------------------------------------------------------------------------------------------------------
	float new_x;
	float new_y;

	new_y = floor(player.pos.y / SQUARE_LEN) * SQUARE_LEN ;
	if(is_down)
		new_y += SQUARE_LEN;
	new_x = player.pos.x + (new_y - player.pos.y) / tan(player.rotation_angle);

//-----------------------------------------------------------------------------------------------------------------------

	float new_step_x;
	float new_step_y;


	new_step_y = SQUARE_LEN;
	new_step_x = SQUARE_LEN / tan(player.rotation_angle);




	// printf("new_x ===== %f\n", new_x);
	// printf("new_y ===== %f\n\n", new_y);



	// exit(0);




	while(pub->info->map[(int)floor(new_y / SQUARE_LEN)][(int)new_x / SQUARE_LEN] != '1')
	{
		new_x += new_step_x;
		new_y += new_step_y;

	}
	// int test = floor(new_x / SQUARE_LEN);
	// printf("test_x -->> %d\n", test);
	// int test_y = floor(new_y / SQUARE_LEN);
	// printf("test_y -->> %d\n", test_y);

	// printf("yaha  ->>  %c\n ", pub->info->map[test_y][test]);
//------------------------------------------------------------passto_draw-------------------------------------------------------
	printf("------------------------ray cast ------------------\n");


	pub->tess_x = new_x;
	pub->tess_y = new_y;
//-----------------------------------------------------------------------------------------------------------------------


	// draw_line(pub->window_img, player.pos, (t_pos){.x = player.pos.x + (cos(player.rotation_angle) * 30), .y = player.pos.y + (sin(player.rotation_angle) * 30)});

	// draw_line(pub->window_img, player.pos, (t_pos){.x = player.pos.x + (cos(player.rotation_angle) * 30), .y = player.pos.y + (sin(player.rotation_angle) * 30)});
	printf("==|%f|==\n",player.rotation_angle);
	// exit(0);



}
