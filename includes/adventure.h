#ifndef ADVENTURE_H
# define ADVENTURE_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

// Window settings
# define WIN_WIDTH 680   // 15 tiles * 40px + 40px margins on each side
# define WIN_HEIGHT 560  // 11 tiles * 40px + 40px top margin + 40px bottom + UI space
# define TILE_SIZE 40
# define MARGIN 40       // Margin around the game area

// Key codes (for macOS)
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_SPACE 49

// Map elements
# define WALL '1'
# define FLOOR '0'
# define PLAYER 'P'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define MOKA 'M'  // Your dog companion!

// Game states
typedef enum e_game_state
{
	GAME_MENU,
	GAME_PLAYING,
	GAME_LEVEL_COMPLETE,
	GAME_WON,
	GAME_PAUSED
}	t_game_state;

// City levels
typedef enum e_city
{
	LONDON = 0,
	PARIS = 1,
	ROME = 2,
	AMSTERDAM = 3,
	BERLIN = 4,
	MAX_CITIES = 5
}	t_city;

// Position structure
typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

// Player structure
typedef struct s_player
{
	t_position	pos;
	t_position	old_pos;
	int			move_count;
	char		sprite_char;
}	t_player;

// Level information
typedef struct s_level
{
	char		*name;
	char		*collectible_name;
	char		**map;
	int			width;
	int			height;
	int			total_collectibles;
	int			collected;
}	t_level;

// Sprites structure
typedef struct s_sprites
{
	void		*player_front;
	void		*moka;
	void		*cider;
	void		*croissant;
	void		*gelato;
	void		*doner;
	void		*stroopwafel;
	void		*wall;
	void		*floor;
	void		*exit;
	void		*menu_bg;
	void		*london_bg;
	void		*paris_bg;
	void		*rome_bg;
	void		*amsterdam_bg;
	void		*berlin_bg;
}	t_sprites;

// Game structure
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_sprites	sprites;
	t_level		levels[MAX_CITIES];
	int			current_level;
	t_player	player;
	t_game_state state;
	int			moka_pos_x;  // Moka's position
	int			moka_pos_y;
}	t_game;

// Function prototypes

// Initialization
int		init_game(t_game *game);
int		init_levels(t_game *game);
void	init_player(t_game *game);
int		load_sprites(t_game *game);
void	free_sprites(t_game *game);

// Level management
void	load_level(t_game *game, int level_index);
int		check_level_complete(t_game *game);
void	advance_to_next_level(t_game *game);

// Game logic
int		game_loop(t_game *game);
void	update_game(t_game *game);
void	render_game(t_game *game);

// Input handling
int		key_press(int keycode, t_game *game);
int		close_game(t_game *game);

// Player movement
int		move_player(t_game *game, int dx, int dy);
int		is_valid_move(t_game *game, int x, int y);
void	collect_item(t_game *game, int x, int y);

// Rendering
void	draw_filled_rectangle(t_game *game, int x, int y, int width, int height, int color);
void	draw_tile(t_game *game, char tile, int x, int y);
void	draw_map(t_game *game);
void	draw_ui(t_game *game);
void	draw_menu(t_game *game);

// Utility functions
void	free_game(t_game *game);
void	print_level_info(t_game *game);

#endif
