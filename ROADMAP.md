# CUB3D Project Roadmap

This roadmap tracks the mandatory `src/` raycasting engine and parsing pipeline. Status reflects the code on 25 Nov 2025.

## Phase 0: Parsing & Configuration
- [x] Validate allowed map tokens and capture player spawn (`src/parsing/validate_map.c`).
- [x] Normalize map rows before leak checks via `fill_map_with_spaces`.
- [ ] Harden cleanup on parser failures so `init_game` frees partially built state.
- [ ] Reconcile texture bookkeeping: `tex_paths` holds four entries while `load_all_textures` iterates five.

## Phase 1: Engine Bring-Up
- [x] Initialize MiniLibX context and window (`src/rander/randring.c`).
- [x] Allocate the frame buffer image and expose pixel data (`init_image`).
- [x] Clamp window size to 1920×1080 when maps exceed the target scale (`win_scal`).
- [ ] Centralize MLX teardown paths so every early return releases window, images, and display.

## Phase 2: Frame Preparation
- [x] Paint ceiling and floor colors each frame (`src/rander/drwa_urils.c`).
- [ ] Rename `drwa_urils.c` to `draw_utils.c` and update both Makefiles.

## Phase 3: Raycasting Core
- [x] Generate per-column ray direction using camera plane math (`src/rander/draw.c`).
- [x] Perform DDA stepping until a solid tile is reached (`src/rander/raycasting.c`).
- [ ] Guard against zero-length rays to avoid division-by-zero in `delta_dist`.
- [ ] Extend hit detection to support doors or other interactive tiles.

## Phase 4: Wall Projection & Texturing
- [x] Compute perpendicular wall distance and slice height.
- [x] Derive texture coordinates and sample the active wall texture.
- [ ] Introduce a depth buffer to prepare for sprites and doors.
- [ ] Add simple distance-based shading for visual depth cues (polish).

## Phase 5: Player Control & Interaction
- [x] Keyboard hooks for WASD and arrow keys (`src/rander/handle_key.c`).
- [x] Move and rotate the player with collision checks (`src/rander/player_movment.c`).
- [ ] Wire `keys.e` to an `open_door` helper; remove leftover debug prints.
- [ ] Mirror the bonus mouse-look handler in the mandatory build.

## Phase 6: Mini-map & UI
- [ ] Optimise minimap drawing; current implementation iterates the full screen each frame (`src/rander/mini_map.c`).
- [ ] Add a directional arrow or ray indicator to the player marker.
- [ ] Render the minimap in its own overlay buffer to decouple HUD from the 3D frame.

## Phase 7: Polish & QA
- [ ] Audit error messages for consistency and user-friendly wording.
- [ ] Write regression tests for parsing edge cases (duplicate players, open maps, RGB bounds).
- [ ] Document build steps and runtime controls in `README.md`.
- [ ] Profile frame time on large maps and tune movement/rotation speeds accordingly.

---

**Immediate Next Steps**
1. Fix the texture array mismatch in `init_data` and `load_all_textures` before enabling door textures.
2. Implement `open_door` and hook `keys.e` so interactable tiles work in both builds.
3. Refactor the minimap renderer to operate on map bounds only for better performance.
