ConversionMaster is a robust command-line interface (CLI) application authored in C. It serves as a centralized utility for performing complex unit conversions and mathematical approximations across five scientific and economic domains: Mathematics, Chemistry, Physics, Economics, and Basic Physical Measurements. This was my first ever project at ISU!

Technical Stack

    Language: C (Standard: C99/C11)

    Compilers: Optimized for GCC/MinGW (x86_64-w64-mingw32-gcc)

    Libraries: <stdio.h>, <math.h>, <stdlib.h>, <ctype.h>

    Architecture: Procedural state-machine design using nested switch-case structures for sub-menu navigation.

Key Features

    Computational Mathematics: Tools for percentage change, slope-intercept calculations, and calculus-based approximations.

    Scientific Domain Utilities:

        Chemistry: Stoichiometric mole-to-gram conversions and Combined Gas Law solvers.

        Physics: Kinematics (v=d/t) and Newtonian mechanics (F=ma) solvers.

        Basics: Temperature (Kelvin/Celsius/Fahrenheit), fluid dynamics, and metric-to-imperial distance conversions.

    Interactive CLI: A "classic" terminal GUI with ASCII art headers and modular sub-menus.

    Cross-Platform Readiness: Designed for Windows/Linux environments with specific instructions for MinGW cross-compilation.

Compilation & Execution

To ensure the executable is portable (.exe) compile with the following flags:

x86_64-w64-mingw32-gcc lab06.c -o ConversionMaster.exe

Run the application:
./ConversionMaster.exe
