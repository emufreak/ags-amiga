# Adventure Game Studio

Adventure Game Studio (AGS) - is the IDE and the engine meant for creating and running videogames of adventure (aka "quest") genre. Created by Chris Jones back in 1999, AGS was open-sourced in 2011. Since then continues to be developed by contributors. Both Editor and Engine are licensed under the Artistic License 2.0; for more details see [License.txt](License.txt). 

For community forums, games and more, go to the website: [www.adventuregamestudio.co.uk](https://www.adventuregamestudio.co.uk)

## This Repository

This repository is an attempt to port the Engine to the Commodore Amiga. At the time being this is a one man project in experimental status.

Goals
- A working Adventure game engine for Amiga to be able to easily create Adventure games for Amiga classic
- It's a welcome side effect if existing AGS Game work on Amiga. As not all features can be ported this is not a main objective.
- IDE port is NOT planned. Game development can happen with the existing tools on Windows.
- Target Platform is an Amiga with some extra Mem and 68020/68030 and OCS or AGA. So more or less the system the average Amiga User of 2024 has at home.

Approach
1. Removing all the SDL and Audio stuff we should end up with a "headless" engine that can perfectly handle an adventure game. Unfortunately it has no means of input and output and is useless
2. This version of the engine can then be ported to Amiga. Except some memory allocations everything should be standard C++ that runs on every platform.
3. Now input and output gets added again and handled natively by Amiga calls.

## Current State

Atm the whole source code compiles on Linux and it's just a maimed version of the Original AGS source where a lot of the SDL Library calls were removed already (Part 1d afs described above)