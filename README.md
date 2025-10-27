# Adventure ## Cities & Collectibles
- 🇬🇧 **London**: Pints of Cider
- 🇫🇷 **Paris**: Croissants
- 🇮🇹 **Rome**: Gelatos
- 🇳🇱 **Amsterdam**: Stroopwafels
- 🇩🇪 **Berlin**: Döner


## Story
Join me on a romantic journey through our favorite cities - London, Paris, Rome, Berlin, and Amsterdam! Collect special treats from each city while exploring with our beloved dog Moka.

1. Use **WASD** or **Arrow Keys** to move around
2. Collect all the special items in each city
3. Find the **green exit** once you've collected everything
4. Look for **Moka** in each city!
5. Press **SPACE** when a level is complete to continue to the next city
6. Press **ESC** to quit

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

## Technical Details
- Built with **minilibX** graphics library
- Written in **C** following 42 school standards
- Uses **tile-based rendering** system (40×40 pixel tiles)
- **Event-driven** input handling
- **Professional project structure** with organized directories
- **XPM sprite assets** ready for implementation

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
