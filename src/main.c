#include "adventure.h"
#include <stdio.h>
#include <string.h>

// Initialize the game window and mlx
int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);

	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT,
		"Adventure Game - A Journey Through Our Cities 💕");
	if (!game->win)
		return (0);

	game->current_level = 0;
	game->state = GAME_MENU;

	// Initialize levels and player
	if (!init_levels(game))
		return (0);

	// Load sprites
	if (!load_sprites(game))
	{
		printf("Error: Failed to load sprites\n");
		return (0);
	}

	// Don't initialize player/level yet - we're starting in menu mode

	return (1);
}

// Handle key presses
int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_game(game);

	// Handle SPACE key in menu to start game
	if (keycode == KEY_SPACE && game->state == GAME_MENU)
	{
		// Initialize the game properly when starting
		load_level(game, 0);  // Start with London
		init_player(game);
		game->state = GAME_PLAYING;
		// print_level_info(game);  // Skip for now to debug
		render_game(game);
		return (0);
	}

	// Handle SPACE key for level progression (works in any state)
	if (keycode == KEY_SPACE && game->state == GAME_LEVEL_COMPLETE)
	{
		advance_to_next_level(game);
		return (0);
	}

	// Only allow movement when game is playing
	if (game->state != GAME_PLAYING)
		return (0);

	// Movement with WASD or arrow keys
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		move_player(game, 0, -1);
		render_game(game);
	}
	else if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		move_player(game, 0, 1);
		render_game(game);
	}
	else if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		move_player(game, -1, 0);
		render_game(game);
	}
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		move_player(game, 1, 0);
		render_game(game);
	}

	return (0);
}

// Close game and free resources
int	close_game(t_game *game)
{
	free_game(game);
	exit(0);
	return (0);
}

// Main game loop
int	game_loop(t_game *game)
{
	update_game(game);
	render_game(game);
	return (0);
}

// Main function
int	main(void)
{
	t_game	game;

	// Initialize game structure to zero/null
	memset(&game, 0, sizeof(t_game));

	printf("🎮 Starting Oko's Adventure! 🎮\n");
	printf("Loading game assets...\n");

	if (!init_game(&game))
	{
		printf("Error: Failed to initialize game\n");
		return (1);
	}

	// Set up event handlers
	mlx_hook(game.win, 2, 1L<<0, key_press, &game);  // Key press
	mlx_hook(game.win, 17, 1L<<17, close_game, &game); // Window close
	mlx_loop_hook(game.mlx, game_loop, &game);        // Main loop

	// Don't print level info since we start in menu mode
	// print_level_info(&game);

	// Start the game loop
	mlx_loop(game.mlx);

	return (0);
}
