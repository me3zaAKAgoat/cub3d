- parse the map into a 2d array consisting of integers each with a value that I can compare to 3 macros : WALL, PLAYER, TERRAIN
- sanitize the input file's name and content
- figure out the structures needed :

- Map data :

  - TEXTURES : NO, SO, WE, EA
  - COLORS : floor, ceil
  - 2d array holding 2d map data

- player data : angle from initial looking position
- MLX data : win, image


# Chores

- [ ] Thouroughly check for any makefile errors !!
- [ ] find out a way to exit and clean all heap memory gracefully in order to fully utilize leak detectors as they flag even heap memory in use at exit 

- [ ] test parsing of different maps
- [ ] add more sanitization for surface colors
- [ ] look for all function that use malloc and check if they're failure safe
- [ ] norminette

## prio

- [ ] check that the view angle and all the important macros are the same on bonus and mandatory 
- [ ] remove fps counter pre ship
- [ ] check all failure cases that could be caused by textures
- [ ] begin the exit protocol that clears global

# Childish play

- have boxes inside the map that act same as walls (valorant triple boxes)
- find a way to turn valorant walls into pixel art form