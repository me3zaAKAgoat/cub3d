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

- [x] Sanitize AV and AC
- [ ] Add sanitization of the map (all void is covered by walls)
  - check if any HORIZONTAL TERM is precedented with a WALL element
  - check if any array starts with a WALL element
  - check if any VOID is surrounded by VOID and WALL element
  - check if first and last array are all WALL or VOID elements
- [ ] sanitize if the map contains a player or not also!!
- [ ] Thouroughly check for any makefile errors !!
- [ ] find out a way to exit and clean all heap memory gracefully in order to fully utilize leak detectors as they flag even heap memory in use at exit 
- [ ] check that all functions that use malloc are failure safe
  - ft strdup in parsing 
- [ ] test parsing of different maps
- [ ] modularize square and circle drawing functions
- [ ] there's duplication in minimap raycasting file
- [ ] add more sanitization for surface colors
- [ ] minimap casted rays are a bit jagged and are visibly imperfect !!
- [ ] use ray casting to do wall collisions
  - get the viewing angle and then calculate the rays hit and then decide wether to move or not move depending on 

## prio

- [ ] parsing should account for doors !!
- [ ] check that the view angle and all the important macros are the same on bonus and mandatory 
- [ ] !!!!!!!! can phase through walls in collisions.
- [ ] fix hitbox/wall collisions
- [ ] remove fps counter pre ship
- [x] put textures on maps
- [ ] change the parsing so it stores the texture not the path to the xpmf file
- [ ] check all failure cases that could be caused by textures
- [ ] begin the exit protocol that clears global

# Questions

- should we rectangle our map
- !!!!!!!!!!!!!!!!! if we dont rectangle the map should we take teh max width/height or the min and why
- how to test peformance

# Childish play

- have boxes inside the map that act same as walls (valorant triple boxes)
- find a way to turn valorant walls into pixel art form