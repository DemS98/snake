# snake

Simple Snake game written with [SDL3](https://github.com/libsdl-org/SDL).

## Required dependencies

* **SDL3** (x64 libraries already provided in [lib/](./lib/))
* **libfreetype-dev** (`sudo apt install libfreetype-dev` for Debian based systems)

## Compile

Just run `make`.

To remove intermediate object files, `make clean`.

To compile with debug informations: `make CFLAGS=-DDEBUG`

## Play

Just move the snake with the arrow keys.

## Scope

This was just a simple test to learn SDL3.

## Resources references

- [Nova Mono font](https://fonts.google.com/specimen/Nova+Mono)
- [Eat sound](https://www.youtube.com/watch?v=Zm7Sbb9bzi8)
- [Death sound](https://www.youtube.com/watch?v=S7lvrg4yzAc)