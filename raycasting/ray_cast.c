/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azarda <azarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 02:27:06 by azarda            #+#    #+#             */
/*   Updated: 2023/08/24 18:00:32 by azarda           ###   ########.fr       */
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


double ft_destance(double x1, double y1, double x2, double y2)
{
	return(sqrt((x2 - x1) * (x2 - x1) +(y2 - y1) * (y2 -y1)));
}

void ray_cast(t_global *pub)
{

	//--------------------------------------------size map -----------------------------------------------
	int s_y_map = 0;
	int s_x_map = 0;

	int o = 0;

	while(pub->info->map[s_y_map])
	{
		while(pub->info->map[s_y_map][s_x_map] && o == 0)
			s_x_map++;
		o = 1;
		s_y_map++;;
	}
	//------------------------------------------------------------------------------------------------------


	t_player player = pub->info->player;
    // player.rotation_angle = normalize_angle(player.rotation_angle);  // dega normalizet de puis l7myer

	double ray_angel = normalize_angle(player.rotation_angle);

	double wallhit_x = 0;
	double wallhit_y  = 0;
	double distance = 0;


	//-----------------------------------------------------------------------------------------------------

	int is_down = 0;
	int is_up = 0;
	int is_right = 0;
	int is_left = 0;

    if (ray_angel > 0 && ray_angel < M_PI)
        is_down = 1;
    	is_up = !is_down;
    if (ray_angel < 0.5 * M_PI || ray_angel > 1.5 * M_PI)
        	is_right = 1;
    	is_left = !is_right;


	// ray_angel *= (M_PI / 180);
	//------------------------------------------------horisontal-------------------------------------------------

	double x_inter;
	double y_inter;

	double step_x;
	double step_y;

	y_inter = floor(player.pos.y / SQUARE_LEN) * SQUARE_LEN;
	if(is_down)
		y_inter += SQUARE_LEN;
	x_inter = player.pos.x + (y_inter - player.pos.y) / tan(ray_angel);

	step_y = SQUARE_LEN;
	if(is_up)
		step_y *= -1;
	step_x = SQUARE_LEN / tan(ray_angel);
	if(is_left && step_x > 0)
		step_x *= -1;
	if(is_right && step_x < 0)
		step_x *= -1;

	double next_horiso_x = x_inter;
	double next_horiso_y = y_inter;
	if(is_up)
		next_horiso_y--;

	int flag_horison = 0;
	int x;
	int y;
	while(1)
	{
		x = floor(next_horiso_x / SQUARE_LEN);
		y = floor(next_horiso_y / SQUARE_LEN);
		if(x >= s_x_map || y >= s_y_map || x < 0 || y < 0)
			break;
		else
		{

			// printf("y        %d  x      %d \n", y, x);
			// printf("y_maps   %d  x_map  %d \n", s_y_map, s_x_map);


			if(pub->info->map[y][x] == '1')
			{
				flag_horison = 1;
				break;
			}
			next_horiso_x += step_x;
			next_horiso_y += step_y;

			// pub->tess_x = next_horiso_x;
			// pub->tess_y = next_horiso_y;
		}
	}

	//------------------------------------vertical--------------------------------------------------


	double verti_x_inter;
	double verti_y_inter;

	double verti_step_x;
	double verti_step_y;

	verti_x_inter = floor(player.pos.x / SQUARE_LEN) * SQUARE_LEN;
	if(is_right)
		verti_x_inter += SQUARE_LEN;


	verti_y_inter = player.pos.y + (verti_x_inter - player.pos.x) *  tan(ray_angel);

	verti_step_x = SQUARE_LEN;
	if(is_left)
		verti_step_x *= -1;




	verti_step_y = SQUARE_LEN * tan(ray_angel);
	if(is_up && verti_step_y > 0)
		verti_step_y *= -1;
	if(is_down  && verti_step_y < 0)
		verti_step_y *= -1;

	double next_verti_x = verti_x_inter;
	double next_verti_y = verti_y_inter;
	if(is_left)
		next_verti_x--;

	int flag_vertical = 0;
	x = 0;
	y = 0;
	while(1)
	{
		x = floor(next_verti_x / SQUARE_LEN);
		y = floor(next_verti_y / SQUARE_LEN);
		if(x >= s_x_map || y >= s_y_map || x < 0 || y < 0)
			break;
		else
		{

			// printf("y        %d  x      %d \n", y, x);
			// printf("y_maps   %d  x_map  %d \n", s_y_map, s_x_map);


			if(pub->info->map[y][x] == '1')
			{
				flag_vertical = 1;
				break;
			}
			next_verti_x += verti_step_x;
			next_verti_y += verti_step_y;

			// pub->tess_x = next_verti_x;
			// pub->tess_y = next_verti_y;
		}
	}

	double  horisontal_distance = 135416843148613586154564683546514685146.85 ;
	double  vertical_distance = 135416843148613586154564683546514685146.85;
	if(flag_horison)
	{
		horisontal_distance = ft_destance(player.pos.x, player.pos.y, next_horiso_x, next_horiso_y) ;
	}
	if(flag_vertical)
	{
		vertical_distance = ft_destance(player.pos.x, player.pos.y, next_verti_x, next_verti_y);
	}
	if(horisontal_distance < vertical_distance)
	{
		pub->tess_x = next_horiso_x;
		
	}
	else
		pub->tess_x = next_verti_x;
	if(horisontal_distance < vertical_distance)
		pub->tess_y = next_horiso_y;
	else
		pub->tess_y = next_verti_y;





















//-----------------------------------------------------------------------------------------------------------------------
	// float new_x = 0;
	// float new_y = 0;



	// 	// printf("new y %f\n", new_y);
	// 	// printf("new x %f\n", new_x);



	// new_y = floor(player.pos.y / SQUARE_LEN) * SQUARE_LEN ;
	// if(is_down)
	// 	new_y += SQUARE_LEN;
	// new_x = player.pos.x + (new_y - player.pos.y) / tan(player.rotation_angle);


	// float new_step_x = 0;
	// float new_step_y = 0;


	// new_step_y = SQUARE_LEN;
	// new_step_x = SQUARE_LEN / tan(player.rotation_angle);




	// while(1)
	// {
	// 	// printf("new y %f\n", new_y);
	// 	// printf("new x %f\n", new_x);
	// 	// puts("-------------------------------------------------------------------------------");




	// 	int x = floor(new_x / SQUARE_LEN);
	// 	int y = floor(new_y / SQUARE_LEN);


	// 	// printf("y_map  ---->>>  %d x_map ->>>> %d \n", s_y_map, s_x_map);
	// 	// 	printf("y %d\n", y);
	// 	// printf("x %d\n", x);



	// 	if(y >= s_y_map || y < 0  || x >= s_x_map || x < 0 )
	// 	{
	// 		// puts( "HNA BREKA" );
	// 		break;
	// 	}
	// 	if (pub->info->map[y][x] == '1')
	// 		break;
	// 		new_x += new_step_x;
	// 		new_y += new_step_y;

	// }
	// 	// printf("new y %f\n", new_y);
	// 	// printf("new x %f\n", new_x);
	// // exit(0);


//-----------------------------------------------------------------------------------------------------------------------

	// float v_new_x = 0;
	// float v_new_y = 0;

	// v_new_x = floor(player.pos.x / SQUARE_LEN) * SQUARE_LEN ;
	// 	// if(is_up)
	// 	// v_new_x *= -1;
	// v_new_y = player.pos.y + (v_new_x - player.pos.x) * tan(player.rotation_angle);


	// float v_new_step_x = 0;
	// float v_new_step_y = 0;

	// v_new_step_x = SQUARE_LEN;
	// v_new_step_y = SQUARE_LEN * tan(player.rotation_angle);



	// while(1)
	// {
	// 	int j = floor(v_new_y / SQUARE_LEN);
	// 	int i = floor(v_new_x / SQUARE_LEN);
	// 	if(i >= s_y_map ||  i < 0 || j >= s_x_map || j < 0 )
	// 	{
	// 		// puts( "HNA BREKA" );
	// 		break;
	// 	}
	// 	if(pub->info->map[i][j] == '1')
	// 		break;
	// 	v_new_x += v_new_step_x;
	// 	v_new_y += v_new_step_y;
	// }

//------------------------------------------------------------passto_draw-------------------------------------------------------
// 	printf("------------------------ ray cast ------------------\n");

// 	if(v_new_x < new_x && v_new_x >= 0)
// 	{
// 		// printf("1  v new x  --> %f\n", v_new_x);
// 		pub->tess_x = v_new_x;

// 	}
// 	else if(new_x >= 0)
// 	{
// 		// printf("2  new x  --> %f\n", new_x);
// 		pub->tess_x = new_x;

// 	}

// 	if(v_new_y < new_y && v_new_y >= 0)
// 	{

// 		// printf("3  v new y  --> %f\n", v_new_y);
// 		// printf("3  new y  --> %f\n", new_y);
// 		pub->tess_y = v_new_y;

// 	}
// 	else if (new_y >= 0)
// 	{
// 		// printf("4  new y  --> %f\n", new_y);
// 		pub->tess_y = new_y;
// 	}

// 	printf("x go to dro  --->> %f\n", pub->tess_x );
// 	printf("y go to dro  --->> %f\n", pub->tess_y );
// 	// exit(0);

// 	// printf("x_size map %d\ny_size_map %d\n", s_x_map, s_y_map);
// 	// printf("x point to draw  %d\ny to mlx tom draw  %d\n", pub->tess_x, pub->tess_y);
// //-----------------------------------------------------------------------------------------------------------------------

// 	printf("==|%f|==\n",player.rotation_angle);
// 	// exit(0);



}
