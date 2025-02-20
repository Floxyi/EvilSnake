<p align="center">
  <img src="/assets/textures/EvilSnake.png" alt="EvilSnake Icon" width="200" />
</p>

<div align="center">
    <h1>EvilSnake</h1>
</div>

![EvilSnake Screenshot](/assets/textures/Screenshot.png)

**EvilSnake** is a simple, snake-inspired game built with C++ and [Raylib](https://www.raylib.com/). Reach 100 points, be aware of the two difficulty modes and compare your best time with your friends!

## Prerequisites

Before you begin, ensure that you have the following installed on your machine (macOS example):

- **C++ Compiler**: Install `clang++` via Xcode Command Line Tools (`xcode-select --install`)

- **CMake**: `brew install cmake`

- **Make**: Comes pre-installed on macOS

- **Raylib**: `brew install raylib`

## Development

### Clone the Repository

```bash
git clone https://github.com/Floxyi/EvilSnake.git
cd EvilSnake
```

### Run & Build the Project

- You can compile and run the game:

```bash
make run
```

- You can build the game for macOS:

```bash
make build-macos
```

- (Optional) You can export compiler commands for use with LSPs:

```bash
cd build/
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
```

- If you need to clean the build directories:

```bash
make clean
```

## Acknowledgments

The **Makefile** and **CMakeLists.txt** files were created with assistance from ChatGPT. Additionally, a few small parts of the game logic were optimized afterwards with ChatGPT’s guidance for improved performance and efficiency.

This project uses the **Thaleah Font** by Rick Hoppmann [Download here](https://tinyworlds.itch.io/free-pixel-font-thaleah) (no modifications made)

This project uses the **Round** by Herald [Download here](https://heraldod.itch.io/bitmap-fonts) (no modifications made)
