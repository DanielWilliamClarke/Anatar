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

## Plan

- [x] Create base entity class so players and enemies may implement / derive 
- [x] Create enemies and enemy movement
- [x] Player weapons
- [x] Flesh out player
- [x] Player enemy interactions
- [x] Stage background for fun (base space stage in place)
- [x] Skin player and enemies using previous assets before new ones are made
- [x] Spatial partitioning for better collision detection performance, WE ARE USING A QUAD TREE
  - [x] Player -> enemy collisions
  - [ ] bullet -> bullet collisions? 
- [ ] Game states - main menu, gameplay, pause, settings, highscores etc 
- [ ] Buff / Debuff / Power up / Helper system 
  - [ ] player to collide with power ups and entity object is attached to the player
- [ ] Improve player control scheme
  - [ ] Demo mode (AI controlled player)
  - [ ] Weapon selection
- [ ] Finite state logic
  - [ ] Generic state machine functionality that can be dropped in to simplify logic for movement, weapons etc
- [ ] Visualise player stats, as in weapon temp, weapon energy, ammo, current weapon etc.
  - [x] Visualise damage
- [ ] Debug visualisation (both current and timeseries data)
  - [ ] total bullets on screen
  - [ ] total enemise
  - [ ] total memory usage
  - [ ] total cpu usage
- [ ] Level design: missions, bosses, enemy squadrons, mission select screen?
- [x] Better weapons: (now able to add new weapon types easily)
  - [x] beam weapons
  - [x] homing projectiles
  - [ ] mines.
  - [ ] barriers
  - [ ] bolas's
  - [ ] EMP's - or other debuff weapons

### Nice to haves:
- [ ] Intelligent enemies: track and shoot towards player
  - [ ] Bosses, multiple firing patterns, interesting mechanics, weak points? youtube.com/watch?v=V4ctJETN-mg?
  - [ ] Enemy waves, Sqaudrons?
- [ ] Buff - Can be encountered mid level, will attach themselves to the player
  - [ ] Helpers: have own health, add buffs, ammo can fire autonmously or on player action (dies on timeout, ammo depletion and health loss)
  - [ ] Stat buffs - shield regen, health regen, invincibility, damage multiplier
- [ ] Debuff - can be encountered mid level, will attach themselves to the player
  - [ ] stat debuffs or damage over time.
- [ ] Android app?
- [ ] Highscores?
- [ ] online coop - Boost ASIO, SFML network?
