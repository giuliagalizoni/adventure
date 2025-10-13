#include "adventure.h"
#include <stdio.h>

// Main game update function
void	update_game(t_game *game)
{
	// Game logic updates go here
	// Currently most logic is handled in event-driven functions
	(void)game;
}

// Print level information to console
void	print_level_info(t_game *game)
{
	t_level *current = &game->levels[game->current_level];

	printf("\n=== Welcome to %s! ===\n", current->name);
	printf("🎯 Collect all %d %s to unlock the exit!\n",
		current->total_collectibles, current->collectible_name);
	printf("🐕 Look for Moka somewhere in the city!\n");
	printf("Controls: WASD or Arrow Keys to move, ESC to quit\n");
	printf("Progress: %d/%d %s collected\n",
		current->collected, current->total_collectibles, current->collectible_name);
}

// Free all game resources
void	free_game(t_game *game)
{
	if (!game)
		return;

	// Free sprites
	free_sprites(game);

	// Free level maps
	for (int i = 0; i < MAX_CITIES; i++)
	{
		if (game->levels[i].map)
		{
			for (int j = 0; j < game->levels[i].height; j++)
			{
				if (game->levels[i].map[j])
					free(game->levels[i].map[j]);
			}
			free(game->levels[i].map);
		}
	}

	// Close window and clean up MLX
	if (game->win && game->mlx)
		mlx_destroy_window(game->mlx, game->win);
}
