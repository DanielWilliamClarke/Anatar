# Anarion

- Fresh repo to build a working version of my old first year programming project
- Using SFML 2.5 as a 2D renderer instead of Gwin

- using the MinGW32 compiler for C++ using `CMake` and `NMake`
  - Ensure that MinGW gcc and g++ compilers are in your PATH
  - Ensure that cmake and nmake are also in your PATH

- if forking this repo download and place the SFML sources files / binaries in `libraries`
  - This project is current using the following verison of SFML
https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-32-bit.zip

### To Build and Run

```cmd
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
nmake
./Anarion.exe
```
