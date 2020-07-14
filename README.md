# Annatar

- Fresh repo to build a working version of my old first year programming project
- Using SFML 2.5 as a 2D renderer instead of Gwin

- Developing in Visual Studio Community 2019
  - Build system = CMake
  - Compiler = Ninja
  - x64

- Open and build in Visual Studio Community 2019

- if forking this repo download and place the SFML sources files / binaries in `libraries`
  - This project is current using the following verison of SFML

https://www.sfml-dev.org/files/SFML-2.5.1-windows-vc15-64-bit.zip


## Next Up

- Create base entity class so players and enemies may implement / derive - ✓
- Create enemies and enemy movement ✓
- Player weapons ✓
- Flesh out player ✓
- Skin player and enemies using previous assets before new ones are made ✓
- Player enemy interactions ✓
- Stage background for fun ✓ (base space stage in place)
- Game states - main menu, gameplay, pause, settings, highscores etc
- Level design: missions, bosses, enemy squadrons
- Power ups
- more intelligent enemies, track player, shoot at player
- Bosses, multiple firing patterns, interesting mechanics, weak points?
- enemy Waves?
- mission select screen? 
- Android app?
- better weapons: beam weapons, seeker missiles, bombs

## Install Conan packages

For now update profile.txt to contain the Build Config mode [`Debug` or `Release]

```Powershell
# Install Deps
cd build
conan install --build=missing --profile ../profile.txt ..     

# then run cmake
cmake ..
```

then build
