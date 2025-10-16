#include "adventure.h"
#include <stdio.h>

// Load all game sprites
int	load_sprites(t_game *game)
{
	if (!game || !game->mlx)
		return (0);

	// Initialize all sprite pointers to NULL first
	game->sprites.player_front = NULL;
	game->sprites.moka = NULL;
	game->sprites.cider = NULL;
	game->sprites.croissant = NULL;
	game->sprites.gelato = NULL;
	game->sprites.doner = NULL;
	game->sprites.stroopwafel = NULL;
	game->sprites.wall = NULL;
	game->sprites.floor = NULL;
	game->sprites.exit = NULL;
	game->sprites.menu_bg = NULL;
	game->sprites.london_bg = NULL;
	game->sprites.paris_bg = NULL;
	game->sprites.rome_bg = NULL;
	game->sprites.amsterdam_bg = NULL;
	game->sprites.berlin_bg = NULL;

	// Load player sprites
	int width, height;
	game->sprites.player_front = mlx_xpm_file_to_image(game->mlx,
		"assets/player_front.xpm", &width, &height);
	if (!game->sprites.player_front)
	{
		printf("Error: Could not load player_front.xpm\n");
		return (0);
	}

	// Load animation sprites (optional - won't fail if missing)
	game->player_left1 = mlx_xpm_file_to_image(game->mlx,
		"assets/player_left1.xpm", &width, &height);
	game->player_left2 = mlx_xpm_file_to_image(game->mlx,
		"assets/player_left2.xpm", &width, &height);
	game->player_right1 = mlx_xpm_file_to_image(game->mlx,
		"assets/player_right1.xpm", &width, &height);
	game->player_right2 = mlx_xpm_file_to_image(game->mlx,
		"assets/player_right2.xpm", &width, &height);



	// Load Moka sprite
	game->sprites.moka = mlx_xpm_file_to_image(game->mlx,
		"assets/moka.xpm", &width, &height);
	if (!game->sprites.moka)
	{
		printf("Error: Could not load moka.xpm\n");
		free_sprites(game);
		return (0);
	}

	// Load collectible sprites
	game->sprites.cider = mlx_xpm_file_to_image(game->mlx,
		"assets/cider.xpm", &width, &height);
	game->sprites.croissant = mlx_xpm_file_to_image(game->mlx,
		"assets/croissant.xpm", &width, &height);
	game->sprites.gelato = mlx_xpm_file_to_image(game->mlx,
		"assets/gelato.xpm", &width, &height);
	game->sprites.doner = mlx_xpm_file_to_image(game->mlx,
		"assets/döner.xpm", &width, &height);
	game->sprites.stroopwafel = mlx_xpm_file_to_image(game->mlx,
		"assets/stroopwafel.xpm", &width, &height);

	// Load environment sprites
	game->sprites.wall = mlx_xpm_file_to_image(game->mlx,
		"assets/wall.xpm", &width, &height);
	game->sprites.floor = mlx_xpm_file_to_image(game->mlx,
		"assets/floor.xpm", &width, &height);

	// Load menu background
	game->sprites.menu_bg = mlx_xpm_file_to_image(game->mlx,
		"assets/menu_bg.xpm", &width, &height);

	// Load city background sprites
	game->sprites.london_bg = mlx_xpm_file_to_image(game->mlx,
		"assets/london_bg.xpm", &width, &height);
	game->sprites.paris_bg = mlx_xpm_file_to_image(game->mlx,
		"assets/paris_bg.xpm", &width, &height);
	game->sprites.rome_bg = mlx_xpm_file_to_image(game->mlx,
		"assets/rome_bg.xpm", &width, &height);
	game->sprites.amsterdam_bg = mlx_xpm_file_to_image(game->mlx,
		"assets/amsterdam_bg.xpm", &width, &height);
	game->sprites.berlin_bg = mlx_xpm_file_to_image(game->mlx,
		"assets/berlin_bg.xpm", &width, &height);

	printf("✅ Sprites loaded successfully!\n");
	return (1);
}

// Free all loaded sprites
void	free_sprites(t_game *game)
{
	if (!game || !game->mlx)
		return;

	if (game->sprites.player_front)
		mlx_destroy_image(game->mlx, game->sprites.player_front);
	if (game->sprites.moka)
		mlx_destroy_image(game->mlx, game->sprites.moka);
	if (game->sprites.cider)
		mlx_destroy_image(game->mlx, game->sprites.cider);
	if (game->sprites.croissant)
		mlx_destroy_image(game->mlx, game->sprites.croissant);
	if (game->sprites.gelato)
		mlx_destroy_image(game->mlx, game->sprites.gelato);
	if (game->sprites.doner)
		mlx_destroy_image(game->mlx, game->sprites.doner);
	if (game->sprites.stroopwafel)
		mlx_destroy_image(game->mlx, game->sprites.stroopwafel);
	if (game->sprites.wall)
		mlx_destroy_image(game->mlx, game->sprites.wall);
	if (game->sprites.floor)
		mlx_destroy_image(game->mlx, game->sprites.floor);
	if (game->sprites.exit)
		mlx_destroy_image(game->mlx, game->sprites.exit);
	if (game->sprites.menu_bg)
		mlx_destroy_image(game->mlx, game->sprites.menu_bg);
	if (game->sprites.london_bg)
		mlx_destroy_image(game->mlx, game->sprites.london_bg);
	if (game->sprites.paris_bg)
		mlx_destroy_image(game->mlx, game->sprites.paris_bg);
	if (game->sprites.rome_bg)
		mlx_destroy_image(game->mlx, game->sprites.rome_bg);
	if (game->sprites.amsterdam_bg)
		mlx_destroy_image(game->mlx, game->sprites.amsterdam_bg);
	if (game->sprites.berlin_bg)
		mlx_destroy_image(game->mlx, game->sprites.berlin_bg);

	// Free animation sprites
	if (game->player_left1)
		mlx_destroy_image(game->mlx, game->player_left1);
	if (game->player_left2)
		mlx_destroy_image(game->mlx, game->player_left2);
	if (game->player_right1)
		mlx_destroy_image(game->mlx, game->player_right1);
	if (game->player_right2)
		mlx_destroy_image(game->mlx, game->player_right2);
}
