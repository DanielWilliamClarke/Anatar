# Annatar

![](./src/assets/p1.gif)

- Fresh repo to build a working version of my old first year programming project
- Using SFML 2.6.1 as a 2D renderer

- Developing in ~~Visual Studio Community 2022~~ CLion
  - Build system = CMake
  - Compiler = Ninja
  - x64

## Plan

### Game states

- [x] main menu, 
- [x] gameplay, 
- [ ] pause, 
- [ ] settings, 
- [ ] highscores etc 

### Next up 2024

- [ ] Modernise code to c++20 (ranges etc)
- [ ] Swap Cmake for bazel
- [ ] Configuration based entities (build entities from json configs)
- [ ] Configuration based levels (enemy waves, level background etc)
- [ ] smarter enemy motion
- [ ] Buffs, Debuffs, and weapon upgrades 
- [ ] Greater control over weapons (weapon selection? multiple weapons controlled via number keys?)
- [ ] perhaps play with play rotation

### Gameplay

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
- [x] implement debug renderer that can be turned on with key press
- [ ] Buff / Debuff / Power up / Helper system 
  - [ ] player to collide with power ups and entity object is attached to the player
- [ ] Improve player control scheme
  - [ ] Demo mode (AI controlled player)
  - [ ] Weapon selection
- [x] Finite state logic
  - [ ] Generic state machine functionality that can be dropped in to simplify logic for movement, weapons etc
- [x] Better weapons: (now able to add new weapon types easily)
  - [x] beam weapons
  - [x] homing projectiles
  - [ ] mines.
  - [ ] barriers
  - [ ] bolas's
  - [ ] EMP's - or other debuff weapons

### Visuals

- [ ] Visualise player stats, as in weapon temp, weapon energy, ammo, current weapon etc.
  - [x] Visualise damage
- [ ] Debug visualisation (both current and time series data)
  - [ ] total bullets on screen
  - [ ] total enemies
  - [ ] total memory usage
  - [ ] total cpu usage
- [ ] Level design: missions, bosses, enemy squadrons, mission select screen?
- [ ] Better player and enemy graphics
- [ ] Procedural planets / asteroids / other celestial objects - <https://deep-fold.itch.io/pixel-planet-generator>

### Nice to haves / Ideas:
- [ ] Intelligent enemies: track and shoot towards player
  - [ ] Bosses, multiple firing patterns, interesting mechanics, weak points? youtube.com/watch?v=V4ctJETN-mg?
  - [ ] Enemy waves, Sqaudrons?
- [ ] Buff - Can be encountered mid level, will attach themselves to the player
  - [ ] Helpers: have own health, add buffs, ammo can fire autonmously or on player action (dies on timeout, ammo depletion and health loss)
  - [ ] Stat buffs - shield regen, health regen, invincibility, damage multiplier
- [ ] Debuff - can be encountered mid level, will attach themselves to the player
  - [ ] stat debuffs or damage over time.
- [ ] Highscores?
- [ ] online coop - Boost ASIO, SFML network?
