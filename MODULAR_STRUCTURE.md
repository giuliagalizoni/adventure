# Adventure Game - Code Organization

## 📁 Modular Structure

The codebase has been reorganized into focused modules for better maintainability and understanding:

### 🎮 Core Files

- **`src/main.c`** - Entry point, window management, event handling
- **`src/game.c`** - Core game logic, utilities, cleanup
- **`includes/adventure.h`** - All structures, constants, and function declarations

### 🗺️ Game Systems

#### **`src/levels.c`** - Level Management
- `init_levels()` - Set up all 5 cities with maps and metadata
- `load_level()` - Load specific level and find player/Moka positions
- `advance_to_next_level()` - Progress through cities
- `check_level_complete()` - Validate level completion
- Contains all city maps: London, Paris, Rome, Berlin, Amsterdam

#### **`src/player.c`** - Player Logic
- `init_player()` - Initialize player position and stats
- `move_player()` - Handle movement with collision detection
- `is_valid_move()` - Validate moves (walls, bounds, exit conditions)
- `collect_item()` - Handle collectible pickup and progress tracking

#### **`src/rendering.c`** - Graphics & Display
- `render_game()` - Main render loop with screen clearing
- `draw_map()` - Render entire level with player/Moka positioning
- `draw_tile()` - Render individual tiles with sprite support
- `draw_filled_rectangle()` - Helper for solid color rendering
- `draw_ui()` - UI elements (currently console-based)

#### **`src/sprites.c`** - Asset Management
- `load_sprites()` - Load all XPM sprites with error handling
- `free_sprites()` - Clean up sprite memory
- Manages: player, Moka, collectibles (cider, croissant, gelato, döner, stroopwafel)

## 🎯 Benefits of This Structure

### **Separation of Concerns**
- **Levels**: Map data and progression logic isolated
- **Player**: Movement and interaction mechanics separate
- **Rendering**: All graphics code in one place
- **Sprites**: Asset loading centralized

### **Easier Maintenance**
- Each file has a single, clear responsibility
- Functions are logically grouped by purpose
- Easy to find and modify specific functionality

### **Better Understanding**
- New developers can focus on one system at a time
- Reduced complexity in each file
- Clear dependencies between modules

## 🔄 How Systems Interact

```
main.c (Events) → player.c (Movement) → levels.c (Map Logic) → rendering.c (Display)
                     ↓                       ↓                        ↓
               sprites.c (Assets) ←------- game.c (Core Logic) -----→ All modules
```

## 🛠️ Development Workflow

1. **Adding new levels**: Modify `src/levels.c`
2. **Changing player mechanics**: Edit `src/player.c`
3. **Improving graphics**: Update `src/rendering.c`
4. **Adding new sprites**: Extend `src/sprites.c`
5. **Core game changes**: Modify `src/game.c`

## 📦 Build System

The `Makefile` automatically compiles all modules:
```bash
make clean && make  # Rebuild everything
make                # Incremental build
./adventure         # Run the game
```

All modules share the same header (`adventure.h`) for consistency and type safety.
