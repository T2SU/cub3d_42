# cub3d - My first RayCaster with miniLibX

## Summary

- You have to draw a realistic 3D using RayCaster.
- My cub3D was developed using Metal via mlx, and is only compatible with macOS.
- [Subject](https://github.com/T2SU/cub3d_42/blob/master/subject.en.pdf)

## Build & Run

- To build and run this, you will need a macOS system. (Apple Silicon or Intel)

1. Clone the repository

```
git clone https://github.com/T2SU/cub3d_42.git
```

2. Navigate to the cloned repository directory and build it. This will create the bonus subject output.

```
make bonus
```

3. Run the game with the bonus map.

```
./cub3D ./maps/map_bonus.cub
```

## Controls

|   Function   |             Input             |
| :----------: | :---------------------------: |
|     Move     |          W, A, S, D           |
|     Aim      |    Mouse move, Keyboard ←→    |
|     Fire     |  Mouse left click, Left ctrl  |
|   Interact   |             Space             |
| WeaponSwitch | 1 ~ 3 (Kick, Pistol, Shotgun) |

## Cheats

|                          Function                          | Input |
| :--------------------------------------------------------: | :---: |
|                      Toggle God mode                       |  F1   |
|                    Toggle Infinity ammo                    |  F2   |
| Toggle transcendence mode<br/>(Enemy doesn't shoot player) |  F3   |
|                    Toggle one shot mode                    |  F4   |

## Result

- Final mark: (115/100)
- Complete Bonus List: (15/18)
  - [x] Wall collisions.
  - [x] A skybox.
  - [x] Floor and/or ceiling texture.
  - [x] An HUD.
  - [ ] Ability to look up and down.
  - [ ] Jump or crouch.
  - [x] A distance related shadow effect.
  - [x] Life bar.
  - [x] More items in the maze.
  - [x] Object collisions.
  - [x] Earning points and/or losing life by picking up objects/traps.
  - [x] Doors which can open and close.
  - [x] Secret doors.
  - [x] Animations of a gun shot or animated sprite.
  - [ ] Several levels.
  - [x] Sounds and music.
  - [x] Rotate the point of view with the mouse.
  - [x] Weapons and bad guys to fight!

## Screenshot

![Screenshot1](https://github.com/T2SU/cub3d_42/blob/master/screenshot1.png)
![Screenshot2](https://github.com/T2SU/cub3d_42/blob/master/screenshot2.png)
![Screenshot3](https://github.com/T2SU/cub3d_42/blob/master/screenshot4.png)

## Playthrough Video

- [Youtube](https://youtu.be/FKgrcHuAg20)

## Useful links

- [mlx_example by taelee42 (Korean)](https://github.com/taelee42/mlx_example)
- [Raycasting tutorial translation by 365kim (Korean)](https://github.com/365kim/raycasting_tutorial)
- [Wikipedia Raycasting](https://en.wikipedia.org/wiki/Ray_casting)
- [Raycasting Summary (Korean)](https://www.notion.so/Raycasting-Summary-acab4d4772f74f72a229d96ed12590ef)
- [Make Your Own Raycaster](https://www.youtube.com/watch?v=gYRrGTC7GtA)
- [Wolfenstein's Map Renderer](https://www.youtube.com/watch?v=eOCQfxRQ2pY)

## CREDIT for Library/Utilities/Resources

- All rights belong to proper right holder.

### LIBRARY

#### MiniLibX by Charlie Root

- ver. Apple Metal (minilibx_mms_20200219_beta)
  by Olivier Crouzet <ol@42.fr>

#### MIDImyAPP - play/stop utility

- (http://www.bibiko.de/music/MIDImyAPP/)

### SOUND

#### Music ::

- The Sisters of Mercy - Black Planet ; Instrumental Cover by PythonBlue
- (https://soundcloud.com/pythonblue/sisters-of-mercy-black-planet)
- Jun Ishikawa - Dedede's Royal Payback (Nintendo 3DS; Kirby Triple Deluxe OST)
- (https://www.youtube.com/watch?v=wYmMty5O86k)
- The little dinasour dooly Cinematic Ending song
- (https://www.youtube.com/watch?v=LUOPgy-CFfo)

#### SFX ::

- Doom - id Software (from doom2.wad)
- Quake II - id Software
- Half-life - Valve Software

### SPRITE

#### Burning Drum, Candles, Hud Images, Ammo, Medikit ::

- Doom - id Software
- Doom HD Textures And Sprites by BohdanZPM
- (https://www.moddb.com/mods/doom-hd-textures-and-sprites-pack/downloads/doom-hd-textures-and-sprites-pack1)

#### Weapon ::

- Duke Nukem 3D - 3D Realms (Apogee Software)
- Duke Nukem 3D Upscale Pack 1.1b w. Nuclear Winter sprites
- (https://www.moddb.com/games/duke-nukem-3d/addons/duke-nukem-3d-upscale-pack-11-w-nuclear-winter-sprites)

#### Money ::

- Bundles of Dollars
- (https://www.hiclipart.com/free-transparent-background-png-clipart-iirow)

#### Crosshair ::

- 64 crosshairs pack by para
- (https://opengameart.org/content/64-crosshairs-pack)

#### Health Bar ::

- Nxoe Theme Hud March Ui - Hud PNG
- (https://flyclipart.com/nxoe-theme-hud-march-ui-hud-png-873195#)

### TEXTURE

#### Brick (Mandatory Part) ::

- (https://www.pinterest.com/pin/782430135244108623/)

#### Floor, Wall ::

- Doom - id Software
- Doom HD Textures And Sprites by BohdanZPM
- (https://www.moddb.com/mods/doom-hd-textures-and-sprites-pack/downloads/doom-hd-textures-and-sprites-pack1)

#### Skybox ::

- Box 'O Skies v3 by Mechadon
- (https://www.doomworld.com/forum/post/1969145)

#### Door ::

- Wolfenstein 3D - id Software
- Doom II - Wolfenstein Door 02 by Hoover1979
- (https://www.deviantart.com/hoover1979/art/Doom-II-Wolfenstein-Door-02-698895747)

### FONT

#### Modern Society

- (https://themeui.net/modern-society-free-font/)

#### Nanum Gothic (NHN NAVER Corp.)

- (https://hangeul.naver.com/font)
