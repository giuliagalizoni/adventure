#include "adventure.h"
#include <stdio.h>

// Helper function for drawing filled rectangles
void	draw_filled_rectangle(t_game *game, int x, int y, int width, int height, int color)
{
	if (!game || !game->mlx || !game->win)
		return;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			mlx_pixel_put(game->mlx, game->win, x + i, y + j, color);
		}
	}
}

// Main render function
void	render_game(t_game *game)
{
	if (game->state == GAME_MENU)
	{
		draw_menu(game);
	}
	else
	{
		// Clear window with a nice background color
		mlx_clear_window(game->mlx, game->win);
		draw_map(game);
		draw_ui(game);
	}
}

// Draw city background across the first row
void	draw_city_background(t_game *game)
{
	void *bg_sprite = NULL;

	// Select the appropriate background sprite for current city
	switch (game->current_level)
	{
		case LONDON:
			bg_sprite = game->sprites.london_bg;
			break;
		case PARIS:
			bg_sprite = game->sprites.paris_bg;
			break;
		case ROME:
			bg_sprite = game->sprites.rome_bg;
			break;
		case AMSTERDAM:
			bg_sprite = game->sprites.amsterdam_bg;
			break;
		case BERLIN:
			bg_sprite = game->sprites.berlin_bg;
			break;
		default:
			return;
	}

	// Draw one large background image across the first two rows
	if (bg_sprite)
	{
		// Position: start at margin, cover full width and 2 rows height
		int bg_x = MARGIN;
		int bg_y = MARGIN;
		mlx_put_image_to_window(game->mlx, game->win, bg_sprite, bg_x, bg_y);
	}
}

// Draw the map
void	draw_map(t_game *game)
{
	if (!game || game->current_level < 0 || game->current_level >= MAX_CITIES)
		return;

	t_level *current = &game->levels[game->current_level];

	if (!current || !current->map || current->height <= 0 || current->width <= 0)
		return;

	// Draw city background first
	draw_city_background(game);

	for (int y = 0; y < current->height; y++)
	{
		if (!current->map[y])
			continue;

		for (int x = 0; x < current->width; x++)
		{
			char tile = current->map[y][x];

			// Skip drawing tiles in the first 2 rows (background area)
			if (y < 2)
			{
				// Only draw player or Moka if they're in the background area
				if (x == game->player.pos.x && y == game->player.pos.y)
					draw_tile(game, PLAYER, x, y);
				else if (x == game->moka_pos_x && y == game->moka_pos_y)
					draw_tile(game, MOKA, x, y);
				// Skip drawing walls/floors in background area
				continue;
			}

			// Normal tile drawing for rows 2 and below
			if (x == game->player.pos.x && y == game->player.pos.y)
				draw_tile(game, PLAYER, x, y);
			else if (x == game->moka_pos_x && y == game->moka_pos_y)
				draw_tile(game, MOKA, x, y);
			else
				draw_tile(game, tile, x, y);
		}
	}
}

// Draw a single tile (using sprites where available)
void	draw_tile(t_game *game, char tile, int x, int y)
{
	if (!game || !game->mlx || !game->win)
		return;

	// Bounds checking
	if (x < 0 || y < 0 || x >= 15 || y >= 11)
		return;

	int pixel_x = x * TILE_SIZE + 40;  // 40px margin from edge
	int pixel_y = y * TILE_SIZE + 40;
	int color;

	// Additional window bounds check
	if (pixel_x < 0 || pixel_y < 0 || pixel_x >= WIN_WIDTH || pixel_y >= WIN_HEIGHT)
		return;

	switch (tile)
	{
		case WALL:
			if (game->sprites.wall)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.wall, pixel_x, pixel_y);
			else
			{
				color = 0x8B4513;  // Fallback brown walls
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			break;
		case FLOOR:
			if (game->sprites.floor)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.floor, pixel_x, pixel_y);
			else
			{
				color = 0xF5F5DC;  // Fallback beige floor
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			break;
		case PLAYER:
			// Draw floor first
			if (game->sprites.floor)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.floor, pixel_x, pixel_y);
			else
			{
				color = 0xF5F5DC;  // Fallback beige floor
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			// Then draw player sprite based on direction and animation frame
			{
				void *player_sprite = NULL;

				// Select sprite based on direction and animation frame
				if (game->player.direction == DIR_LEFT)
				{
					if (game->player.animation_frame == 0 && game->player_left1)
						player_sprite = game->player_left1;
					else if (game->player.animation_frame == 1 && game->player_left2)
						player_sprite = game->player_left2;
				}
				else if (game->player.direction == DIR_RIGHT)
				{
					if (game->player.animation_frame == 0 && game->player_right1)
						player_sprite = game->player_right1;
					else if (game->player.animation_frame == 1 && game->player_right2)
						player_sprite = game->player_right2;
				}
				else if (game->player.direction == DIR_BACK)
				{
					if (game->player.animation_frame == 0 && game->player_back1)
						player_sprite = game->player_back1;
					else if (game->player.animation_frame == 1 && game->player_back2)
						player_sprite = game->player_back2;
				}
				else if (game->player.direction == DIR_FRONT)
				{
					// Only use animated sprites if player has moved, otherwise use base sprite
					if (game->player.move_count > 0)
					{
						if (game->player.animation_frame == 0 && game->player_front1)
							player_sprite = game->player_front1;
						else if (game->player.animation_frame == 1 && game->player_front2)
							player_sprite = game->player_front2;
					}
				}

				// Fallback to default front sprite if animated sprite not available
				if (!player_sprite)
					player_sprite = game->sprites.player_front;

				if (player_sprite)
					mlx_put_image_to_window(game->mlx, game->win, player_sprite, pixel_x, pixel_y);
				else
				{
					color = 0xFF1493;  // Fallback pink color
					draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
				}
			}
			break;
		case COLLECTIBLE:
			// Draw floor first
			if (game->sprites.floor)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.floor, pixel_x, pixel_y);
			else
			{
				color = 0xF5F5DC;  // Fallback beige floor
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			// Draw city-specific collectible sprite
			{
				void *collectible_sprite = NULL;
				switch (game->current_level)
				{
					case LONDON:
						collectible_sprite = game->sprites.cider;
						break;
					case PARIS:
						collectible_sprite = game->sprites.croissant;
						break;
					case ROME:
						collectible_sprite = game->sprites.gelato;
						break;
					case AMSTERDAM:
						collectible_sprite = game->sprites.stroopwafel;
						break;
					case BERLIN:
						collectible_sprite = game->sprites.doner;
						break;
				}

				if (collectible_sprite)
					mlx_put_image_to_window(game->mlx, game->win, collectible_sprite, pixel_x, pixel_y);
				else
				{
					// Fallback to colored rectangle if sprite not available
					color = 0xFFD700;  // Gold color
					draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
				}
			}
			break;
		case EXIT:
			// Draw floor first
			if (game->sprites.floor)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.floor, pixel_x, pixel_y);
			// Then draw exit sprite if available
			if (game->sprites.exit)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.exit, pixel_x, pixel_y);
			else
			{
				color = 0x00FF00;  // Fallback green exit
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			break;
		case MOKA:
			// Draw floor first
			if (game->sprites.floor)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.floor, pixel_x, pixel_y);
			else
			{
				color = 0xF5F5DC;  // Fallback beige floor
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			// Then draw Moka sprite if available
			if (game->sprites.moka)
				mlx_put_image_to_window(game->mlx, game->win, game->sprites.moka, pixel_x, pixel_y);
			else
			{
				color = 0xFF4500;  // Fallback orange color
				draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			}
			break;
		default:
			color = 0xF5F5DC;  // Default floor
			draw_filled_rectangle(game, pixel_x, pixel_y, TILE_SIZE - 2, TILE_SIZE - 2, color);
			break;
	}
}

// Draw UI elements (score, instructions, etc.)
void	draw_ui(t_game *game)
{
	if (!game || !game->mlx || !game->win)
		return;

	t_level *current = &game->levels[game->current_level];
	char progress_text[100];

	// Draw city-specific welcome message and instructions
	switch (game->current_level)
	{
		case LONDON:
			mlx_string_put(game->mlx, game->win, 10, 2, 0xFFFFFF, "Welcome to London! Let's grab all the pints of cider");
			mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "and run to the train station!");
			break;
		case PARIS:
			mlx_string_put(game->mlx, game->win, 10, 2, 0xFFFFFF, "Bonjour Paris! Collect delicious croissants");
			mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "before heading to the next city!");
			break;
		case ROME:
			mlx_string_put(game->mlx, game->win, 10, 2, 0xFFFFFF, "Ciao Roma! Gather all the gelato scoops");
			mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "and find your way to the exit!");
			break;
		case AMSTERDAM:
			mlx_string_put(game->mlx, game->win, 10, 2, 0xFFFFFF, "Hallo Amsterdam! Hunt for stroopwafels");
			mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "in the canals before moving on!");
			break;
		case BERLIN:
			mlx_string_put(game->mlx, game->win, 10, 2, 0xFFFFFF, "Guten Tag Berlin! Find all the doner kebabs");
			mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, "- our final destination!");
			break;
	}

	// Draw progress information
	snprintf(progress_text, sizeof(progress_text), "Progress: %d/%d %s collected",
		current->collected, current->total_collectibles, current->collectible_name);
	mlx_string_put(game->mlx, game->win, 10, WIN_HEIGHT - 80, 0xFFD700, progress_text);

	// Draw controls
	mlx_string_put(game->mlx, game->win, 10, WIN_HEIGHT - 60, 0xAAAAAA, "Controls: WASD or Arrow Keys to move, ESC to quit");
}

// Draw main menu screen
void	draw_menu(t_game *game)
{
	if (!game || !game->mlx || !game->win)
		return;

	// Clear window
	mlx_clear_window(game->mlx, game->win);

	// Draw menu background if available
	if (game->sprites.menu_bg)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->sprites.menu_bg, 0, 0);
	}
	else
	{
		// Fallback: draw a simple colored background
		for (int y = 0; y < WIN_HEIGHT; y++)
		{
			for (int x = 0; x < WIN_WIDTH; x++)
			{
				mlx_pixel_put(game->mlx, game->win, x, y, 0x1e3a8a); // Dark blue background
			}
		}
	}

	// Draw title using mlx_string_put (much simpler!)
	mlx_string_put(game->mlx, game->win, WIN_WIDTH / 2 - 80, 150, 0xFFFFFF, "OKO'S ADVENTURE");
	mlx_string_put(game->mlx, game->win, WIN_WIDTH / 2 - 80, WIN_HEIGHT - 100, 0xFFFFFF, "Press SPACE to Start");
}

