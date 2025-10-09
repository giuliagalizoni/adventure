# Adventure ## Cities & Collectibles
- 🇬🇧 **London**: Pints of Cider (3 to collect)
- 🇫🇷 **Paris**: Croissants (4 to collect)
- 🇮🇹 **Rome**: Gelatos (5 to collect)
- 🇩🇪 **Berlin**: Döner (6 to collect)
- 🇳🇱 **Amsterdam**: Stroopwafels (7 to collect)

A### Game Elements Visual Guide:**
- 🟫 **Brown blocks:** Walls (can't pass through)
- 🟡 **Yellow dots:** Collectibles (city treats)
- 🟢 **Green square:** Exit (unlocked after collecting all items)
- 🟣 **Pink square:** You, the player!
- 🟠 **Orange dot:** Moka, your dog companiononalized adventure game built with minilibX as a birthday present! 🎮

## Story
Join me on a romantic journey through our favorite cities - London, Paris, Rome, Berlin, and Amsterdam! Collect special treats from each city while exploring with our beloved dog Moka.

## Cities & Collectibles
- 🇬🇧 **London**: Fish & Chips (3 to collect)
- 🇫🇷 **Paris**: Croissants (4 to collect)
- 🇮🇹 **Rome**: Gelatos (5 to collect)
- 🇩🇪 **Berlin**: Döner (6 to collect)
- 🇳🇱 **Amsterdam**: Stroopwafels (7 to collect)## How to Play
1. Use **WASD** or **Arrow Keys** to move around
2. Collect all the special items in each city
3. Find the **green exit** once you've collected everything
4. Look for **Moka** (in orange) in each city!
5. Press **SPACE** when a level is complete to continue
6. Press **ESC** to quit

## Game Elements
- 🟫 **Brown blocks**: Walls (can't pass through)
- 🟡 **Yellow dots**: Collectibles (city treats)
- 🟢 **Green square**: Exit (unlocked after collecting all items)
- 🟣 **Pink square**: You, the player!
- � **Orange dot**: Moka, our dog companion

## Compilation & Running

### Easy Setup
Run the setup script to automatically install dependencies and compile:
```bash
./setup.sh
```

### Manual Setup
If the automatic setup doesn't work, install minilibX manually:

**Option 1 - Try Homebrew (may not work on all systems):**
```bash
brew install minilibx
```

**Option 2 - Manual compilation:**
```bash
git clone https://github.com/42Paris/minilibx-linux.git
cd minilibx-linux
make
# Copy files to system directories (may need sudo)
cp libmlx.a /usr/local/lib/
cp mlx.h /usr/local/include/
```

**Option 3 - Local installation:**
```bash
git clone https://github.com/42Paris/minilibx-linux.git minilibx
cd minilibx
make
cd ..
```

### Build and Run
```bash
# Compile the game
make

# Run the game
make run

# Or run directly
./adventure
```

### Clean Up
```bash
# Remove object files
make clean

# Remove everything
make fclean

# Rebuild everything
make re
```

## Game Features
- **Multiple themed levels** with increasing difficulty
- **Collectible system** with different items per city
- **Simple collision detection**
- **Level progression** - complete one city to unlock the next
- **Moka companion** appears in every level
- **Move counter** to track your steps
- **Beautiful city-themed maps** representing our travels

## Technical Details
- Built with **minilibX** graphics library
- Written in **C** following 42 school standards
- Uses **tile-based rendering** system (40×40 pixel tiles)
- **Optimized window size** (680×480) perfectly fits the 15×10 map
- **Event-driven** input handling
- **Modular design** for easy expansion

## Future Enhancements Ideas
- Add sprite images instead of colored squares
- Include background music for each city
- Add simple enemies or obstacles
- Create more detailed, larger maps
- Add animation for player movement
- Include a high-score system
- Add sound effects for collecting items

## Controls Summary
| Key | Action |
|-----|--------|
| W / ↑ | Move Up |
| S / ↓ | Move Down |
| A / ← | Move Left |
| D / → | Move Right |
| SPACE | Continue to next level (when complete) |
| ESC | Quit game |

---

*Made with love for your birthday! I hope this brings back wonderful memories of our travels together. 💕*

*P.S. - Moka says woof! 🐕*
