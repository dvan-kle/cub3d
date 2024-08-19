# Cub3D - A 3D Game Engine in C

Welcome to **Cub3D**! This project is a 3D game engine inspired by the classic Wolfenstein 3D. It is written in C using the MiniLibX graphical library and serves as an introduction to basic raycasting techniques and 3D rendering.

## Key Features

- **Raycasting Engine**: Implements a basic raycasting algorithm to render 3D projections from a 2D map.
- **Textures**: Supports textured walls for a more immersive experience.
- **Map Parsing**: Reads and parses a `.cub` file to load the game map, player start position, and other configurations.
- **Player Movement**: Implements smooth player movement, including walking and turning, in a 3D environment.
- **Basic Collision Detection**: Prevents the player from walking through walls and out-of-bound areas.
- **Configurable Settings**: Customizable game settings through the map file, including textures, and more.

## Installation

To compile and run **Cub3D**, follow these steps:

1. Clone the repository:
    ```bash
    git clone https://github.com/dvan-kle/cub3d.git
    ```

2. Navigate to the project directory:
    ```bash
    cd cub3d
    ```

3. Compile the project using the provided Makefile:
    ```bash
    make
    ```

4. Run the game:
    ```bash
    ./cub3D map.cub
    ```

   Replace `map.cub` with the path to your map file.

## Usage

**Cub3D** requires a valid `.cub` map file to run. The map file should define the layout of the game world, textures, and other settings. Here's an example of how to run the game:

```bash
./cub3D maps/level1.cub
```

## Controls

- **W** / **Up Arrow**: Move forward
- **S** / **Down Arrow**: Move backward
- **A** / **Left Arrow**: Strafe left
- **D** / **Right Arrow**: Strafe right
- **Left Arrow**: Turn left
- **Right Arrow**: Turn right
- **ESC**: Exit the game

