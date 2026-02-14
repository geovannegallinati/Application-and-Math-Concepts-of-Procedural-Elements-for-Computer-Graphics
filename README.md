# Application and Math Concepts of Procedural Elements for Computer Graphics

A pure C implementation of a real-time 3D rendering pipeline that displays a rotating house in the terminal using ASCII characters.

The full mathematical documentation with paired C code explanations is available as a PDF:

[Application and Math Concepts of Procedural Elements for Computer Graphics.pdf](docs/Application%20and%20Math%20Concepts%20of%20Procedural%20Elements%20for%20Computer%20Graphics.pdf)

## Features

- Homogeneous coordinates and 4×4 matrix transformations
- Translation, scaling, and rotation (X, Y, Z axes)
- Orthographic and perspective projection
- Back-face culling via surface normals
- Painter's algorithm (depth sorting)
- DDA line rasterization
- Scan-line polygon filling
- Lambert diffuse shading with ASCII luminance ramp

## Building

The project is written in C99 with no external dependencies. All source files are in the root directory.

### macOS

GCC is included with [Xcode Command Line Tools](https://developer.apple.com/xcode/resources/). Install with:

```bash
xcode-select --install
```

```bash
gcc -Wall -Wextra -O2 -std=c99 -o house3d *.c -lm
```

### Linux

GCC is available via your package manager. Install with:

- **Ubuntu/Debian:** `sudo apt install gcc`
- **Fedora:** `sudo dnf install gcc`
- **Arch:** `sudo pacman -S gcc`

See [GCC installation guide](https://gcc.gnu.org/install/) for more details.

```bash
gcc -Wall -Wextra -O2 -std=c99 -o house3d *.c -lm
```

### Windows (MinGW / MSYS2)

Install GCC via [MSYS2](https://www.msys2.org/). After installing MSYS2, run:

```bash
pacman -S mingw-w64-x86_64-gcc
```

Then compile:

```bash
gcc -Wall -Wextra -O2 -std=c99 -o house3d.exe *.c -lm
```

> **Note:** The code includes built-in Windows compatibility. On Windows it uses `Sleep()` from `<windows.h>` automatically. No source modifications needed.

## Usage

```
./house3d [options]
```

| Option     | Description                                        |
|------------|----------------------------------------------------|
| `-w`       | Wireframe only                                     |
| `-f`       | Filled faces only                                  |
| `-b`       | Both wireframe + filled faces (default)            |
| `-p`       | Perspective projection (default: orthographic)     |
| `-s speed` | Rotation speed in degrees per frame (default: 3.0) |
| `-h`       | Show help                                          |


Press `Ctrl+C` to exit.

### Examples

```bash
./house3d                # default: both mode, orthographic
./house3d -w             # wireframe only
./house3d -f -p          # filled faces with perspective
./house3d -b -s 5.0      # both mode, faster rotation
```

## Examples

Below are GIFs showing each rendering mode, with the exact command used:

**Wireframe (Orthographic):**
```bash
./house3d -w
```
![Wireframe](gifs/Wireframe.gif?v=2)

**Filled Faces with Perspective:**
```bash
./house3d -f -p
```
![Filled Faces with Perspective](gifs/Filled%20Faces%20with%20Perspective.gif?v=2)

**Both Mode (Orthographic):**
```bash
./house3d -b
```
![Both Mode Orthographic](gifs/Both%20Mode%20Orthographic.gif?v=2)

## Source Files

| File           | Description                              |
|----------------|------------------------------------------|
| `main.c`       | Entry point, argument parsing, main loop |
| `matrix.c/h`   | 4×4 matrix and vector operations         |
| `transform.c/h`| Geometric transformations (T, S, Rx, Ry, Rz) |
| `geometry.c/h` | House model definition and normals       |
| `projection.c/h`| Orthographic and perspective projection |
| `render.c/h`   | Framebuffer, DDA, scan-line, shading     |
| `pipeline.c/h` | Complete rendering pipeline              |

## Reference

Rogers, David F. *Procedural Elements for Computer Graphics*. 2nd edition. McGraw-Hill, 1998.
