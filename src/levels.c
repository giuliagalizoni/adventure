#include "adventure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize all game levels with maps and metadata
int	init_levels(t_game *game)
{
	// London - Collect pints of cider 🍺
	game->levels[LONDON].name = "London";
	game->levels[LONDON].collectible_name = "Pints of Cider";
	game->levels[LONDON].width = 15;
	game->levels[LONDON].height = 11;
	game->levels[LONDON].total_collectibles = 3;
	game->levels[LONDON].collected = 0;

	// Simple London map (you can customize this!)
	static char london_map[11][16] = {
		"111111111111111",
		"111111111111111",
		"10P00C0000000E1",
		"1011110111101011",
		"100000000000001",
		"1011M01110110111",
		"100000C000000001",
		"1011101111011011",
		"100000000000001",
		"101110C111101111",
		"111111111111111"
	};

	// Paris - Collect croissants 🥐
	game->levels[PARIS].name = "Paris";
	game->levels[PARIS].collectible_name = "Croissants";
	game->levels[PARIS].width = 15;
	game->levels[PARIS].height = 11;
	game->levels[PARIS].total_collectibles = 4;
	game->levels[PARIS].collected = 0;

	static char paris_map[11][16] = {
		"111111111111111",
		"111111111111111",
		"10P0C00000C000E1",
		"1011101111011011",
		"100000000000001",
		"1011M01110110111",
		"100000C000C00001",
		"1011101111011011",
		"100000000000001",
		"101110111101111",
		"111111111111111"
	};

	// Rome - Collect gelato 🍦
	game->levels[ROME].name = "Rome";
	game->levels[ROME].collectible_name = "Gelato";
	game->levels[ROME].width = 15;
	game->levels[ROME].height = 11;
	game->levels[ROME].total_collectibles = 3;
	game->levels[ROME].collected = 0;

	static char rome_map[11][16] = {
		"111111111111111",
		"111111111111111",
		"10PC000000000E1",
		"1011110111101011",
		"100000000000001",
		"1011M01110110111",
		"100000C000000001",
		"1011101111011011",
		"100000000000001",
		"101110C111101111",
		"111111111111111"
	};

	// Berlin - collect döner 🥙
	game->levels[BERLIN].name = "Berlin";
	game->levels[BERLIN].collectible_name = "Döner";
	game->levels[BERLIN].width = 15;
	game->levels[BERLIN].height = 11;
	game->levels[BERLIN].total_collectibles = 4;
	game->levels[BERLIN].collected = 0;

	static char berlin_map[11][16] = {
		"111111111111111",
		"111111111111111",
		"10P0C00000C000E1",
		"1011101111011011",
		"100000000000001",
		"1011M01110110111",
		"100000C000C00001",
		"1011101111011011",
		"100000000000001",
		"111111111111111",
		"111111111111111"
	};

	// Amsterdam - collect stroopwafels 🧇
	game->levels[AMSTERDAM].name = "Amsterdam";
	game->levels[AMSTERDAM].collectible_name = "Stroopwafels";
	game->levels[AMSTERDAM].width = 15;
	game->levels[AMSTERDAM].height = 11;
	game->levels[AMSTERDAM].total_collectibles = 4;
	game->levels[AMSTERDAM].collected = 0;

	static char amsterdam_map[11][16] = {
		"111111111111111",
		"111111111111111",
		"10P0C00000C000E1",
		"1011101111011011",
		"100000000000001",
		"1011M01110110111",
		"10000C000C00001",
		"1011101111011011",
		"100000000000001",
		"111111111111111",
		"111111111111111"
	};

	// Allocate memory for maps and copy static data
	for (int level = 0; level < MAX_CITIES; level++)
	{
		game->levels[level].map = malloc(sizeof(char*) * game->levels[level].height);
		if (!game->levels[level].map)
		{
			// Clean up previous levels
			for (int cleanup = 0; cleanup < level; cleanup++)
			{
				for (int j = 0; j < game->levels[cleanup].height; j++)
					free(game->levels[cleanup].map[j]);
				free(game->levels[cleanup].map);
			}
			return (0);
		}

		for (int i = 0; i < game->levels[level].height; i++)
		{
			game->levels[level].map[i] = malloc(sizeof(char) * (game->levels[level].width + 1));
			if (!game->levels[level].map[i])
			{
				// Clean up this level's partial allocation
				for (int cleanup_i = 0; cleanup_i < i; cleanup_i++)
					free(game->levels[level].map[cleanup_i]);
				free(game->levels[level].map);
				// Clean up previous levels
				for (int cleanup = 0; cleanup < level; cleanup++)
				{
					for (int j = 0; j < game->levels[cleanup].height; j++)
						free(game->levels[cleanup].map[j]);
					free(game->levels[cleanup].map);
				}
				return (0);
			}

			// Copy the appropriate map
			if (level == LONDON)
			{
				strncpy(game->levels[level].map[i], london_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
			else if (level == PARIS)
			{
				strncpy(game->levels[level].map[i], paris_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
			else if (level == ROME)
			{
				strncpy(game->levels[level].map[i], rome_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
			else if (level == BERLIN)
			{
				strncpy(game->levels[level].map[i], berlin_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
			else if (level == AMSTERDAM)
			{
				strncpy(game->levels[level].map[i], amsterdam_map[i], game->levels[level].width);
				game->levels[level].map[i][game->levels[level].width] = '\0';
			}
		}
	}

	return (1);
}

// Load a specific level
void	load_level(t_game *game, int level_index)
{
	if (level_index >= MAX_CITIES)
		return;

	game->current_level = level_index;
	game->levels[level_index].collected = 0;

	// Player and Moka positions will be set by init_player()
	// Don't modify the map here - let init_player() handle it

	// Only set to PLAYING if we're not in menu mode
	if (game->state != GAME_MENU)
		game->state = GAME_PLAYING;
}

// Check if current level is complete
int	check_level_complete(t_game *game)
{
	return (game->levels[game->current_level].collected >=
			game->levels[game->current_level].total_collectibles);
}

// Advance to the next level
void	advance_to_next_level(t_game *game)
{
	if (game->current_level + 1 >= MAX_CITIES)
	{
		printf("🎉 CONGRATULATIONS! 🎉\n");
		printf("You've completed your romantic adventure through all cities!\n");
		printf("What an amazing journey through London, Paris, Rome, Berlin & Amsterdam!\n");
		printf("Time to plan your next real-world adventure! ✈️❤️\n");
		game->state = GAME_WON;
		return;
	}

	load_level(game, game->current_level + 1);
	print_level_info(game);
}
