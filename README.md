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

- [ ] might need map max width and max height
- [ ] Orientation should be flipped the bigger the ray angle gets the more the ray turns anti clock wise
- [ ] Sanitize AV and AC
- [ ] Add sanitization of the map (all void is covered by walls)
  - check if any HORIZONTAL TERM is precedented with a WALL element
  - check if any array starts with a WALL element
  - check if any VOID is surrounded by VOID and WALL element
  - check if first and last array are all WALL or VOID elements
- [ ] Make a ray structure
  - Ray length
  - Ray angle offset
- [ ] Thouroughly check for any makefile errors !!
- [ ] find out a way to exit and clean all heap memory gracefully in order to fully utilize leak detectors as they flag even heap memory in use at exit 
- [ ] check that all functions that use malloc are failure safe
  - ft strdup in parsing 
- [ ] create a minimap
  - cast rays to represent the FOV of the player
- [ ] test parsing of different maps
- [ ] theres some gibberish regarding N W E S and PLayer in elements structure
- [ ] modularize square and circle drawing functions
- [ ] should make a function to replace mlx pixel put that adds absolute value and a modulo window/image heigh to avoid undefined behaviour6
- [ ] tehres duplication in minimap raycasting file
- [ ] THE PLAYER DOES NOT GO WHERE THE VIEWING ANGLE IS DIRECTED !!!!!
- [ ] put the width and the height of the map in a struct to help for checks in vertical and horizontal raycasters
  - why is it needed anyways
# Questions

- how many units should my player be moving
- what is fishbowl effect
- should minimap be on its own seperate image and have the 3d game on a another image
- what is the best hook to use to update the minimap
  - its mlx key hook
- should I use mlx key hook or mlx loop hook
  - which one is more costly and what does each one do best
- for all the increment calculations what if the values are PI/2 or 0 what happens to tan then
- should we rectangle our map
- if we dont rectangle the map should we take teh max width/height or the min and why 