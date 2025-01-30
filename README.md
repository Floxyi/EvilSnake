# EvilSnake

A simple 2D game built with C++ and [Raylib](https://www.raylib.com/).

## Prerequisites

Make sure you have the following installed on your machine:

- **C++ Compiler** (e.g., `clang++` on macOS or `g++` on Linux)
- **CMake** (for building the project)
- **Raylib** (for graphics and game-related functionality)

### Installing Raylib

You can install Raylib using Homebrew on macOS:

```bash
brew install raylib
```

Alternatively, follow the [Raylib installation instructions](https://www.raylib.com/).

## Setup

Follow these steps to set up the project locally:

1. Clone the repository:

    ```bash
    git clone https://github.com/Floxyi/EvilSnake.git
    cd EvilSnake
    ```

2. Build and run the project:

    ```bash
    make run
    ```

3. (Optional) Export compiler commands for use with LSPs:

    ```bash
    cd build/
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
    ```
