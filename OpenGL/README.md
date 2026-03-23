this is my OpenGL Project BL3M, BL3M is a WIP low-level 3D graphics engine and model viewer built from the ground up using C++ and the OpenGL 4.6 Core Profile. The project focuses on high-performance rendering, hardware abstraction, and sophisticated input handling for real-time 3D environments. 

Technical Stack

    Language: C++

    Graphics API: OpenGL 4.6 Core Profile

    Libraries:

        GLAD: Multi-Language GL Loader for managing modern OpenGL function pointers.

        GLFW: Multi-platform library for windowing, context creation, and input management.

    Development Environment: Linux/Unix-based workflows.


Key Features

    Core Rendering Loop: Implements a highly efficient frame-buffer-driven rendering cycle with dynamic viewport scaling.

    Advanced Input Management: Features a custom hardware abstraction layer that supports gamepad mapping via external database files (gamecontrollerdb.txt).

    Hardware Diagnostics: Integrated routines to poll and list connected HID (Human Interface Device) hardware, ensuring cross-device compatibility.

    Modular Event Callbacks: Uses function pointers and callbacks to handle system events (like window resizing) without interrupting the rendering pipeline.

How to Build & Run

    Dependencies: Ensure GLAD and GLFW are installed and linked in your C++ build environment.

    Gamepad Support: Ensure the 'gamecontrollerdb.txt' mapping file is present in the specified include directory.

    Compilation: Use a standard C++ compiler (G++/Clang) with the following include paths and linker flags:
    -lglfw -lGL -ldl -lpthread
