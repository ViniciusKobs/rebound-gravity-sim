#!/bin/bash

rm app
gcc src/main.c src/settings.h src/space/universe.h src/tui/menu.c src/tui/tui.c src/tui/tui.h src/vector/vector.c src/vector/vector.h src/sim/sim.c src/sim/sim.h src/view/view.c src/view/view.h src/space/universe.c -lrebound -lSDL2 -lncurses -lm -o app
