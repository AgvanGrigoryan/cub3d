
# 📍 cub3d

**cub3d** is a mini-project from 42 School written in C that implements a simple 3D engine using the **raycasting** technique, inspired by classic games like *Wolfenstein 3D*. The visualization is built using the **MiniLibX** graphics library, rendering a 3D view of a 2D maze map from the player's perspective.

---

## 🎯 Features

- Raycasting-based 3D engine
- Wall textures for all directions (NO, SO, WE, EA)
- Map parsing from `.cub` files
- Real-time movement (WASD + arrow keys)
- Collision detection (bonus)
- Mini-map, mouse look, and crosshair (bonus)
- Save current frame to BMP image (optional)
- Proper error handling for invalid maps

---

## 📁 Project Structure

```
cub3d/
├── includes/          # Header files
├── libft/             # Custom or external C library
├── minilibx-linux/    # MiniLibX graphics library
├── textures/          # Wall/sprite textures
├── maps/              # Example map files (.cub)
├── sources/           # Main engine source code
├── Makefile
└── README.md
```

---

## 🔧 Installation

1. Clone the repository with submodules:

```bash
git clone --recursive https://github.com/AgvanGrigoryan/cub3d.git
```

Or manually:

```bash
git clone https://github.com/AgvanGrigoryan/cub3d.git
cd cub3d
git submodule update --init --recursive
```

2. Compile the project:

- Build:
```bash
make
```

- To clean:
```bash
make fclean 
```

- To clean and rebuild:
```bash
make re
```

---

## 🚀 Running the Program

```bash
./cub3d path/to/map.cub
```

Example:
```bash
./cub3d maps/library.cub
```

The map must be valid and properly structured. The program exits with an error message if the map is invalid or the arguments are incorrect.

---

## 🎮 Controls

- `W` – Move forward  
- `S` – Move backward  
- `A` / `D` – Strafe left/right  
- `←` / `→` – Rotate view
- `Shift` – Sprint
- `E` – Open/Close the door
- Mouse – Look around (bonus)  
- `ESC` – Exit the game

---

## 📐 Map File Format (`.cub`)

A map file consists of two parts:

1. **Configuration**:
```
NO path/to/north_texture.xpm
SO path/to/south_texture.xpm
WE path/to/west_texture.xpm
EA path/to/east_texture.xpm
DO path/to/open_door_texture.xpm
DC path/to/closed_door_texture.xpm
F R,G,B                          # Floor color
C R,G,B                          # Ceiling color
```

2. **Map layout**:
   - `1` = wall  
   - `0` = empty space  
   - `D/O` = doors(open, closed)
   - `N/S/E/W` = player's start direction  
   - The map must be surrounded by walls and have no gaps

---

## 📊 Example Maps

Organized as:

```
maps/
├── good/        # Valid and playable maps
│   └── library.cub
└── bad/         # Invalid maps used for error testing
    └── invalid_format.buc
```

---

## 🧠 How It Works

- **Parsing**: Reads and validates the `.cub` map format
- **Initialization**: Creates window, loads textures, sets up input hooks
- **Raycasting**: Uses DDA algorithm to trace rays through the map
- **Rendering**: Calculates wall height and textures each column
- **Movement**: Updates player position and handles collisions
- **Bonus**: Mouse support, mini-map, crosshair

---

## 📚 Resources & References

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- Raycasting tutorials by Lode Vandevenne and Permadi
- Similar open-source projects for reference

---

## 👤 Author

Made as part of the 42 School curriculum  
**Authors**: [Agvan Grigoryan](https://github.com/AgvanGrigoryan), [Narek Tamazyan](https://github.com/natamazy)

---

## ✅ Final Thoughts

This project is an excellent introduction to computer graphics, raycasting algorithms, and low-level game engine design. It provides a foundation for more advanced experiments with lighting, sprites, enemy AI, and more.

Feel free to contribute, fork, or explore!
