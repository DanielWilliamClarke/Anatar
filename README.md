# Annatar

![](./src/assets/p1.gif)

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

## Install Conan packages, generate CMake files and build

For now update profile.txt to contain the Build Config mode [`Debug` or `Release]

```Powershell
# cd into build location
cd build/<build-confiuration> -> so: cd build/x64-Debug

# Install Deps
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add skypjack https://api.bintray.com/conan/skypjack/conan
conan install --build=missing --profile ../../profile.txt ../..     

# then run cmake
cmake ..
```

then build

## Done

- [x] Create base entity class so players and enemies may implement / derive 
- [x] Create enemies and enemy movement
- [x] Player weapons
- [x] Flesh out player
- [x] Player enemy interactions
- [x] Stage background for fun (base space stage in place)
- [x] Skin player and enemies using previous assets before new ones are made
- [x] Better weapons: (now able to add new weapon types easily)
  - [x] beam weapons
  - [ ] homing projectiles
  - [ ] mines.
  - [ ] barriers
  - [ ] bolas's

## Next Up

- [ ] Game states - main menu, gameplay, pause, settings, highscores etc
- [ ] Level design: missions, bosses, enemy squadrons, mission select screen?
- [ ] Power ups
- [ ] Helpers: have own health, add buffs, ammo can fire autonmously or on player action (dies on timeout, ammo depletion and health loss)
  - Can be encountered mid level, will attach themselves to the player
- [ ] Limpets: like helpers but add debuffs or damage over time.
  - Can be encountered mid level, will attach themselves to the player
- [ ] Intelligent enemies: track and shoot towards player
- [ ] Bosses, multiple firing patterns, interesting mechanics, weak points?
- [ ] Enemy waves, Sqaudrons?
- [ ] Android app?
- [ ] Visualise weapon stats, as in weapon temp, weapon energy etc.
  - Visualise kills
- [ ] Highscore and points system?
- [ ] online coop - Boost ASIO?
