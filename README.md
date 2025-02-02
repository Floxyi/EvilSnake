![EvilSnake Screenshot](/assets/textures/Screenshot.png)

# EvilSnake

**EvilSnake** is a simple, engaging 2D game built with C++ and [Raylib](https://www.raylib.com/).

## Table of Contents

- [Prerequisites](#prerequisites)
- [Setup](#setup)
- [Usage](#usage)

## Prerequisites

Before you begin, ensure that you have the following installed on your machine:

- **C++ Compiler** (e.g., `clang++` on macOS or `g++` on Linux)
- **CMake** (used for building the project)
- **Raylib** (provides graphics and game-related functionality)

### Installing Raylib

#### macOS

You can install Raylib using Homebrew:

```bash
brew install raylib
```

#### Other Platforms

For Linux or Windows, please refer to the [Raylib installation instructions](https://www.raylib.com/).

## Setup

Follow these steps to set up the project locally:

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/Floxyi/EvilSnake.git
    cd EvilSnake
    ```

2. **Build and Run the Project:**

    You can compile and run the game using `make`:

    ```bash
    make run
    ```

3. **(Optional) Export Compiler Commands:**

    For enhanced code navigation with Language Server Protocols (LSPs), export the compile commands:

    ```bash
    cd build/
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
    ```

## Usage

After successfully building the project, execute the game by running:

```bash
./build/evilsnake
```
