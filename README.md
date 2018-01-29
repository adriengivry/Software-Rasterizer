# CPU Sotfware Rasterizer

Here is our student software rasterizer project made in 6 weeks in a group of 2. 
Our rasterizer exploit the CPU.

## Content

The project is divided into 7 main features :
- Z-Buffer
- Phong (Per-Vertex)
- Blinn-Phong (Per-Pixel)
- Wireframe with Backface Culling
- Bilinear filtering
- Alpha-Blending
- Anti-aliasing

There is an hidden "konami code" in the documentation which start a secret animation.

## How to build it

If you plan to build our project in optimal conditions, you should have :
- Windows
- Visual Studio 2017
- C++ 17

Libraries are included to the project, you don't need to setup anything, just press play.
64-bits and 32-bits systems are both supported (Debug and Release mode)

## External dependencies

For this project we used some external libraries :
- SDL2 to draw pixels on screen
- SDL2_ttf to draw UI
- SDL2_Image to import PNG files
- IrrKlang for audio (Yes, somewhere in the project there are some musics)

## Screenshots

### Z-Buffer
![alt text](screenshots/z-buffer.PNG?raw=true "Z-Buffer")

### Phong
![alt text](screenshots/phong.PNG?raw=true "Phong")

### Blinn-Phong
![alt text](screenshots/blinn-phong.PNG?raw=true "Blinn-Phong")

### Wireframe with Backface Culling
![alt text](screenshots/wireframe.PNG?raw=true "Wireframe with Backface Culling")

#### Bilinear filtering
![alt text](screenshots/bilinear-filtering.PNG?raw=true "Bilinear filtering")

### Alpha-Blending
![alt text](screenshots/alpha-blending.PNG?raw=true "Alpha-Blending")

### Anti-aliasing
![alt text](screenshots/anti-aliasing.PNG?raw=true "Anti-aliasing")

### Secret animation (Find the konami code in the doc to see it)
![alt text](screenshots/zelda.PNG?raw=true "Secret animation")

