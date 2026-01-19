# CUB3D Project Explanation

## 🎮 Project Overview
**CUB3D** is a 3D maze rendering engine built in C using the **raycasting algorithm**. The project simulates a first-person perspective view of a 3D environment based on a 2D map layout. It's inspired by classic games like Wolfenstein 3D.

## 📋 What the Project Does

### Core Functionality
The CUB3D engine takes a 2D map configuration and renders it as a 3D first-person perspective view using raycasting. You can navigate through the maze using keyboard controls and view textured walls.

### Key Features

#### 1. **Map Configuration & Parsing**
- Reads `.cub` map files that define:
  - Wall textures (North, South, East, West)
  - Floor and ceiling colors
  - 2D map layout with walls and walkable spaces
- Located in: `src/parsing/` and `src/parsing_bonus/`

#### 2. **Raycasting Engine**
- Uses the **DDA (Digital Differential Analyzer) Algorithm** to trace rays from the player's perspective
- Calculates where each ray hits a wall
- Determines distance to render depth
- Located in: `src/rander/` (files: `ddaAlgo.c`, `camera_plan.c`, `player_movment.c`)

#### 3. **Rendering System**
- Casts rays for each column of the screen
- Calculates wall height based on distance
- Textures walls by sampling texture images
- Located in: `src/rander/draw.c`, `load_textures.c`

#### 4. **Player Controls**
- **W/A/S/D keys**: Move forward/left/backward/right
- **Arrow Keys**: Rotate left/right
- **ESC**: Exit the program
- Located in: `src/rander/handle_key.c`

#### 5. **Bonus Features** (optional extensions)
- **Mini-map**: Shows 2D view of the maze with player position
- **Advanced rendering**: Additional visual enhancements
- Located in: `src/rander_bonus/` and `src/parsing_bonus/`

## 🏗️ Project Architecture

### File Organization

```
CUB3D/
├── src/
│   ├── main.c                    # Program entry point
│   ├── parsing/                  # Map & configuration parsing
│   │   ├── parse.c              # Main parsing logic
│   │   ├── parse_configurations.c # Parse texture & color settings
│   │   ├── parse_colors.c       # Color parsing
│   │   ├── parse_textures.c     # Texture path parsing
│   │   ├── parse_map.c          # 2D map layout parsing
│   │   ├── validate_map.c       # Map validation
│   │   └── parsing_utils.c      # Utility functions
│   │
│   └── rander/                   # Rendering engine (note: "rander" not "render")
│       ├── randring.c           # Main rendering loop
│       ├── camera_plan.c        # Camera plane calculations
│       ├── ddaAlgo.c            # DDA raycasting algorithm
│       ├── draw.c               # Wall drawing logic
│       ├── player_movment.c     # Player movement mechanics
│       ├── handle_key.c         # Keyboard input handling
│       ├── load_textures.c      # Load texture images
│       └── drwa_utils.c         # Drawing utilities
│
├── includes/
│   ├── cub3d.h                  # Main header file
│   └── cub3d_bonus.h            # Bonus features header
│
├── libraries/
│   ├── libft/                   # Custom C library functions
│   │   ├── ft_atoi.c           # String to integer
│   │   ├── ft_strdup.c         # String duplication
│   │   ├── ft_split.c          # String splitting
│   │   └── ...                 # Other utility functions
│   │
│   └── get_line/                # Custom line reading library
│       ├── get_line.c          # Read lines from file
│       └── get_line.h
│
├── maps/                        # Test map files
│   ├── map1.cub, map2.cub, etc. # Standard maps
│   └── map*_bonus.cub           # Bonus maps
│
└── Makefile                     # Build configuration
```

## 🔧 Technology Stack

| Component | Technology |
|-----------|-----------|
| **Language** | C |
| **Graphics** | MinilibX (MLX) - Linux library for graphics |
| **Algorithm** | Raycasting (DDA) |
| **Input** | X11 keyboard events |
| **Build** | Make |

## 🎯 How It Works - Technical Flow

### 1. **Initialization**
```
main() 
  → parse map file (.cub)
  → validate map layout
  → load textures
  → initialize MLX window
  → set up player position & direction
```

### 2. **Rendering Loop**
```
For each frame:
  → Handle keyboard input (W/A/S/D, arrows, ESC)
  → Update player position
  → For each pixel column on screen:
    • Cast a ray from player's position
    • Use DDA algorithm to find wall intersection
    • Calculate wall distance
    • Determine texture coordinate
    • Sample texture and draw pixel column
  → Display rendered frame
```

### 3. **Key Algorithms**

#### Raycasting (DDA Algorithm)
- Traces a ray from the player through each screen column
- Finds intersection with map walls
- Calculates perpendicular distance to avoid fish-eye distortion

#### Wall Texture Mapping
- Maps 3D wall coordinates to 2D texture coordinates
- Samples texture pixel based on distance and position
- Creates illusion of 3D textured walls

## 📊 Data Structures

### Main Game Structure
```c
typedef struct s_game
{
  t_player player;          // Player position, direction, camera
  t_map *map;               // 2D map array
  t_color floor_color;      // Floor RGB color
  t_color ceiling_color;    // Ceiling RGB color
  char *tex_paths[4];       // N, S, E, W texture paths
  t_texture textures[4];    // Loaded texture images
  // ... rendering context
} t_game;
```

## 🚀 Building & Running

```bash
# Build the project
make              # Standard version
make bonus        # With bonus features

# Run with a map
./cub3D maps/map1.cub
./cub3D_bonus maps/map1_bonus.cub
```

## 📝 Map File Format

```
NO ./path/to/north_texture.xpm
SO ./path/to/south_texture.xpm
EA ./path/to/east_texture.xpm
WE ./path/to/west_texture.xpm
F 220,100,0          # Floor color (RGB)
C 225,30,0           # Ceiling color (RGB)

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000002000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111011101111
10110111011100110110100010001
11010010010100011010010010001
```

## 🎓 Learning Outcomes

This project demonstrates:      
- **Low-level graphics programming** without high-level game engines
- **Algorithm implementation** (raycasting, DDA)
- **File parsing and validation** in C
- **Real-time rendering** and optimization
- **Keyboard input handling** with X11
- **Memory management** in C
- **Custom library development** (libft, get_line)

## 🐛 Project Versions

- **Standard Version**: Basic raycasting with wall texturing
- **Bonus Version** (`_bonus`): Enhanced features including mini-map

---

**Author**: CUB3D Development Team  
**Last Updated**: December 2025  
**Status**: Complete Game Engine
