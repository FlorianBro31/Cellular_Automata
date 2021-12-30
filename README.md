# Cellular_Automata

A very basic Cellular Automata written in C using the SDL2 and SDL2_ttf libraries.

# Building

To build this project you will need the [SDL2 library](https://www.libsdl.org/download-2.0.php) and the [SDL2_ttf library](https://www.libsdl.org/projects/SDL_ttf/) installed.</br>
 
* Install the arial.ttf font and add it to the `assets/fonts` folder.
* type `make` and the game will build and launch.

# Controls

## Element Selection

* `1`: sand
* `2`: water
* `3`: concrete
* `4`: wood
* `5`: fire

You can also use the mousewheel to change the size of the cursor.</br>
Active/deactivate the deletion mode by pressing `x`.

## Frame by Frame mode

* Press `f` to activate/deactivate this mode.
* When in this mode press `->` to move a frame.

# Parameters

you can change the parameters of the simulation by editing the `Defines.h` file.

