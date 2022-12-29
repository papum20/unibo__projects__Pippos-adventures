# unibo__projects__Pippos-adventures
project for programming class in Computer Science at University of Bologna - year 2021-2022


## DISCLAIMERS:
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
## COMPILING AND RUNNING:
- there's a makefile;
- the executable created is called main (or main.exe if executing on linux/wsl).
## COMMANDS:
### IN-GAME:
- Arrows: movement
- WASD: hit/shoot in the four directions
- V: open locked door (if you have a key)
- C: open chest
### MENUS:
- B: open/close map
- M: open/close pause menu
- Arrows: choose menu options
- Enter: select menu entry
- Q: previous menu page
##RULES:
Pippo's Adventures is a rogue-like game with a top-down view:  
there are endless levels full of monsters to kill, items/weapons to find in chests, doors to open.  
Some doors are already open, and you can just step into them to pass to another room, whereas others need key to be unlocked (V button), which you can find in chests.  
There's also a "special room"/"boss room" for each level, with plenty of monsters to kill: once you enter that room you can't exit until you have killed all of them;
but if you manage to do that, you can go to the next level.  
You can also use the map (B button) to get some help to find the special room:
- P indicates the player position;
- B indicates the boss room.
  
TIP: remember, you can always check the commands either in the start menu or in the in-game menu (M button), from the "options" entry.
