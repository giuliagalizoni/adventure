#!/bin/bash

echo "🎮 Adventure Game Setup Script 🎮"
echo "=================================="

# Function to check if minilibX is installed
check_mlx() {
    echo "Checking for minilibX installation..."

    # Check common locations
    if [ -f "/usr/local/lib/libmlx.a" ]; then
        echo "✅ Found minilibX in /usr/local/lib/"
        return 0
    elif [ -f "/opt/homebrew/lib/libmlx.a" ]; then
        echo "✅ Found minilibX in /opt/homebrew/lib/"
        return 0
    elif [ -f "./minilibx/libmlx.a" ]; then
        echo "✅ Found minilibX in local directory"
        return 0
    else
        echo "❌ minilibX not found"
        return 1
    fi
}

# Function to install minilibX
install_mlx() {
    echo "📥 Installing minilibX..."

    # Try to clone and build minilibX locally
    if command -v git &> /dev/null; then
        echo "Cloning minilibX from GitHub..."
        git clone https://github.com/42Paris/minilibx-linux.git minilibx
        cd minilibx

        # Try to build
        if make; then
            echo "✅ minilibX built successfully!"
            cd ..
            return 0
        else
            echo "❌ Failed to build minilibX"
            cd ..
            return 1
        fi
    else
        echo "❌ Git not found. Please install git first."
        return 1
    fi
}

# Main setup process
echo ""
if check_mlx; then
    echo "Great! MinilibX is already installed."
else
    echo "MinilibX not found. Attempting to install..."
    if install_mlx; then
        echo "Installation completed!"
    else
        echo ""
        echo "⚠️  Manual Installation Required ⚠️"
        echo "Please install minilibX manually:"
        echo ""
        echo "Option 1 - Using Homebrew (if available):"
        echo "  brew install minilibx"
        echo ""
        echo "Option 2 - Manual compilation:"
        echo "  git clone https://github.com/42Paris/minilibx-linux.git"
        echo "  cd minilibx-linux"
        echo "  make"
        echo "  sudo cp libmlx.a /usr/local/lib/"
        echo "  sudo cp mlx.h /usr/local/include/"
        echo ""
        echo "Option 3 - For 42 students:"
        echo "  Use the minilibX provided in your 42 environment"
        echo ""
        exit 1
    fi
fi

echo ""
echo "🔨 Attempting to compile the game..."
if make; then
    echo ""
    echo "🎉 SUCCESS! Your adventure game is ready!"
    echo ""
    echo "To run the game:"
    echo "  ./adventure"
    echo ""
    echo "Or use:"
    echo "  make run"
    echo ""
    echo "💕 Happy Birthday! Enjoy your personalized adventure! 💕"
else
    echo ""
    echo "❌ Compilation failed. Please check the error messages above."
    echo "You may need to adjust the Makefile paths for your system."
fi
