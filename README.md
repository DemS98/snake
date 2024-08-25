# snake

Simple Snake game written with [SDL3](https://github.com/libsdl-org/SDL).

## Required dependencies

* **SDL3** (x64 libraries already provided in [lib/](./lib/))
* **libfreetype-dev** (`sudo apt install libfreetype-dev` for Debian based systems)

## Compile

Just run `make`.

To remove intermediate object files, `make clean`.

To compile with debug informations: `make CFLAGS=-DDEBUG`

### Compile for other architectures

You need to compile:

* [libSDL3](https://github.com/libsdl-org/SDL)
* [libSDL3_mixer](https://github.com/libsdl-org/SDL_mixer)
* [libSDL3_ttf](https://github.com/libsdl-org/SDL_ttf)

for your architecture and put the **static** library files in [lib/](./lib/), as the x86 counterpart.

Alternatively, you can download the libraries through a package manager and edit the [Makefile](./Makefile) to refer those
libraries.

## Play

Just move the snake with the arrow keys.

## Scope

This was just a simple test to learn SDL3.

## Resources references

- [Nova Mono font](https://fonts.google.com/specimen/Nova+Mono)
- [Eat sound](https://www.youtube.com/watch?v=Zm7Sbb9bzi8)
- [Death sound](https://www.youtube.com/watch?v=S7lvrg4yzAc)