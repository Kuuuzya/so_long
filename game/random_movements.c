/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   enemy_move.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: skuznets <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/26 17:42:28 by skuznets		  #+#	#+#			 */
/*   Updated: 2024/07/26 17:44:31 by skuznets		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */


#include "../so_long.h"

void	initialize_directions(int directions[4][2])
{
	directions[0][0] = 1;
	directions[0][1] = 0;
	directions[1][0] = -1;
	directions[1][1] = 0;
	directions[2][0] = 0;
	directions[2][1] = 1;
	directions[3][0] = 0;
	directions[3][1] = -1;
}

static void	get_valid_directions(t_data *data, int ex, int ey, \
t_valid_dirs *valid_dirs)
{
	int	directions[4][2];
	int	i;
	int	new_x;
	int	new_y;

	initialize_directions(directions);
	valid_dirs->valid_count = 0;
	i = 0;
	while (i < 4)
	{
		new_x = ex + directions[i][0];
		new_y = ey + directions[i][1];
		if (new_x >= 0 && new_x < data->width / TILE_SIZE && \
new_y >= 0 && new_y < data->height / TILE_SIZE && \
data->map[new_y][new_x] != '1' && \
data->map[new_y][new_x] != 'E' && \
data->map[new_y][new_x] != 'X' && \
data->map[new_y][new_x] != 'C')
		{
			valid_dirs->valid_directions[valid_dirs->valid_count][0] = new_x;
			valid_dirs->valid_directions[valid_dirs->valid_count][1] = new_y;
			valid_dirs->valid_count++;
		}
		i++;
	}
}

static void	move_enemy_to_new_position(t_data *data, \
t_position new_pos, t_position old_pos)
{
	if (data->map[new_pos.y][new_pos.x] == 'P')
		end_game(data, "You loose!!!");
	else
	{
		data->map[new_pos.y][new_pos.x] = 'X';
		data->map[old_pos.y][old_pos.x] = '0';
	}
}

void	move_enemy_random(t_data *data, int ex, int ey)
{
	t_valid_dirs	valid_dirs;
	int				random_index;
	t_position		new_pos;
	t_position		old_pos;

	get_valid_directions(data, ex, ey, &valid_dirs);

	if (valid_dirs.valid_count > 0)
	{
		random_index = rand() % valid_dirs.valid_count;
		new_pos.x = valid_dirs.valid_directions[random_index][0];
		new_pos.y = valid_dirs.valid_directions[random_index][1];
		old_pos.x = ex;
		old_pos.y = ey;
		move_enemy_to_new_position(data, new_pos, old_pos);
	}
}