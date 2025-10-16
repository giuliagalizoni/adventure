#include "adventure.h"
#include <stdio.h>

// Initialize player position
void	init_player(t_game *game)
{
	if (!game)
		return;

	game->player.move_count = 0;
	game->player.sprite_char = 'P';
	game->player.direction = DIR_FRONT;
	game->player.animation_frame = 0;

	t_level *current = &game->levels[game->current_level];

	if (!current->map)
		return;

	// Find player and Moka positions on the map
	for (int y = 0; y < current->height; y++)
	{
		if (!current->map[y])
			continue;

		for (int x = 0; x < current->width; x++)
		{
			if (current->map[y][x] == 'P')
			{
				game->player.pos.x = x;
				game->player.pos.y = y;
				game->player.old_pos = game->player.pos;
				// Replace 'P' with floor in the map
				current->map[y][x] = FLOOR;
			}
			else if (current->map[y][x] == 'M')
			{
				game->moka_pos_x = x;
				game->moka_pos_y = y;
				// Replace 'M' with floor in the map
				current->map[y][x] = FLOOR;
			}
		}
	}
}

// Move player and handle collisions
int	move_player(t_game *game, int dx, int dy)
{
	if (!game)
		return (0);

	int new_x = game->player.pos.x + dx;
	int new_y = game->player.pos.y + dy;

	if (!is_valid_move(game, new_x, new_y))
		return (0);

	// Update player direction based on movement
	if (dx < 0)
		game->player.direction = DIR_LEFT;
	else if (dx > 0)
		game->player.direction = DIR_RIGHT;
	else if (dy < 0)
		game->player.direction = DIR_BACK;
	else if (dy > 0)
		game->player.direction = DIR_FRONT;

	// Toggle animation frame for movement animation
	game->player.animation_frame = (game->player.animation_frame + 1) % 2;

	// Update player position
	game->player.old_pos = game->player.pos;
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
	game->player.move_count++;

	// Moka stays in her static position - no following behavior

	// Check for collectibles
	char tile = game->levels[game->current_level].map[new_y][new_x];
	if (tile == COLLECTIBLE)
		collect_item(game, new_x, new_y);
	else if (tile == EXIT && check_level_complete(game))
	{
		game->state = GAME_LEVEL_COMPLETE;
		printf("\n✨ LEVEL COMPLETE! Press SPACE to continue to the next city! ✨\n");
	}

	return (1);
}

// Check if a move is valid (not into walls, within bounds)
int	is_valid_move(t_game *game, int x, int y)
{
	if (!game)
		return (0);

	t_level *current = &game->levels[game->current_level];

	// Check bounds
	if (x < 0 || x >= current->width || y < 0 || y >= current->height)
		return (0);

	// Check for walls
	char tile = current->map[y][x];
	if (tile == WALL)
		return (0);

	// Check if trying to move to exit without completing level
	if (tile == EXIT && !check_level_complete(game))
	{
		printf("🚪 Complete all objectives before using the exit!\n");
		return (0);
	}

	return (1);
}

// Collect item at given position
void	collect_item(t_game *game, int x, int y)
{
	t_level *current = &game->levels[game->current_level];

	current->map[y][x] = FLOOR;  // Remove collectible from map
	current->collected++;

	printf("Collected %s! (%d/%d)\n",
		current->collectible_name,
		current->collected,
		current->total_collectibles);

	if (check_level_complete(game))
	{
		printf("\n🎊 Level Complete! All %s collected in %s! 🎊\n",
			current->collectible_name, current->name);
		printf("Find the exit to continue to the next city!\n");
	}
}
