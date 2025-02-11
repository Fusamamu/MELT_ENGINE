# MELT - 3D Game Engine

MELT is a 3D game engine designed for entity management. It leverages SDL, OpenGL, GLEW, GLM, and an Entity-Component-System (ECS) architecture for performance and flexibility.

## Features

- **Entity-Component-System (ECS)**: Decouples data and logic for scalable and maintainable game code.
- **OpenGL Rendering**: Utilizes OpenGL for high-performance graphics rendering.
- **SDL Integration**: Handles window management, input, and other system-level operations.
- **GLM for Math**: Leverages GLM for vector and matrix math operations.
- **GLEW for OpenGL Extensions**: Ensures compatibility with various OpenGL versions and extensions.

## Getting Started

### Prerequisites

To build and run MELT, you'll need the following:

- **SDL2**: Simple DirectMedia Layer for handling windows, input, and more.
- **GLEW**: OpenGL Extension Wrangler Library for managing OpenGL extensions.
- **GLM**: OpenGL Mathematics library for handling mathematical operations.
- **OpenGL**: A compatible version of OpenGL (preferably 3.3 or higher).
- **C++17**: MELT requires a C++17 compatible compiler.

### Building the Engine

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Fusamamu/MELT_ENGINE.git
   cd MELT_ENGINE
   ```

2. **Install Dependencies:**
   Make sure SDL2, GLEW, and GLM are installed on your system. On Debian-based systems, you can use:
   ```bash
   sudo apt-get install libsdl2-dev libglew-dev libglm-dev
   ```

3. **Build the Engine:**
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

4. **Run the Engine:**
   ```bash
   ./MELT
   ```

## License

MELT is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

## Contact

For any questions or feedback, please reach out via [sukumDuangpattra@gmail.com](mailto:email@example.com).

