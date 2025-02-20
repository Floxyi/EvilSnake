<p align="center">
  <img src="/assets/textures/EvilSnake.png" alt="EvilSnake Icon" width="200" />
</p>

<div align="center">
    <h1>EvilSnake</h1>
</div>

![EvilSnake Screenshot](/assets/textures/Screenshot.png)

**EvilSnake** is a simple, snake-inspired game built with C++ and [Raylib](https://www.raylib.com/).

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

You can compile and run the game:

```bash
make run
```

You can build the game for macOS:

```bash
make build-macos
```

If you need to clean the build directories:

```bash
make clean
```

## Acknowledgments

The **Makefile** and **CMakeLists.txt** files were created with assistance from ChatGPT. Additionally, certain parts of the game logic were optimized with ChatGPT’s guidance, leveraging integrated C++ methods such as **std::any_of**, **std::find_if**, and **std::strftime** for improved performance and efficiency.
