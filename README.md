# unibo__projects__Pippos-adventures
project for programming course in Computer Science at University of Bologna - year 2021-2022.

![in_game_sword](./doc/img/action_sword.png)

Other images in [doc/img/](./doc/img/)  

## Install

Use the provided makefile and run the created executable, in the `bin/` folder:
*	linux :
	*	```bash
		git clone git@github.com:papum20/unibo__projects__Pippos-adventures.git pippos-adventures && \
   			cd pippos-adventures && \
			# compile
   			make && \
   			# run
			./bin/pippos-adventures
		```
   *	```bash
		# compile
     	make
     	# run the executable ./bin/pipppos-adventures
      	./bin/pippos-adventures
		```

### notes

The previous makefile generator, now in the `scripts/` folder, doesn't work; besides, the new one is more generalized, using wildcards.  


## The game

### Description and rules

Pippo's Adventures is a rogue-like game with a top-down view:  
there are endless levels full of monsters to kill, items/weapons to find in chests, doors to open.  
Some doors are already open, and you can just step into them to pass to another room, whereas others need key to be unlocked (V button), which you can find in chests.  
There's also a "special room"/"boss room" for each level, with plenty of monsters to kill: once you enter that room you can't exit until you have killed all of them;
but if you manage to do that, you can go to the next level.  
You can also use the map (B button) to get some help to find the special room:
- P indicates the player position;
- B indicates the boss room.

### Commands

#### in game

- Arrows: movement
- WASD: hit/shoot in the four directions
- V: open locked door (if you have a key)
- C: open chest

#### menus

- B: open/close map
- M: open/close pause menu
- Arrows: choose menu options
- Enter: select menu entry
- Q: previous menu page
  
TIP: remember, you can always check the commands either in the start menu or in the in-game menu (M button), from the "options" entry.


## Requirements

The terminal on which the game is supposed to be run should meet the following requirements:
- support for changing colors (needed for ncurses)
- not too small: the game window size adjustes accordingly to the available screen (terminal) dimensions,
given in number of characters fitting in one row/column;  
however, with a terminal window too small - i.e. showing too few characters - 
you won't be able to see the minimum number of icons/images/sprites you're supposed to see to play the game,  
while with a screen which is big enuogh, the size of the map which you'll see around the player will depend on the terminal size.  
Thus, if you encounter a problem of visualization, the following could be some solutions:
	- set the terminal full-screen;
	- reduce the font size/increase the number of characters showed in the terminal;
	- zoom out the screen of your computer;
	- zoom out your terminal.
  
So, linux terminals and wsl are ok, windows cmd and PowerShell not.


### Possible issues

*   if the terminal window is too small, you may not be able to see the game properly, or a `Segmentation fault` error may occur (although it probably got fixed lately): try to enlarge it
*	using `ncurses`, colors only depend on your own terminal :
	*	if you can't see them, ensure they are supported, or try to change terminal
	*	if they look strange or the game isn't clearly visible... I don't know how to change them, but it's your terminal's fault, so do a research on how to change them


## Extra

some files used for testing and analyzing are here: https://github.com/papum20/unibo__projects__Pippos-adventures-extra
