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

- Sanitize AV and AC
- Add sanitization of the map (all void is covered by walls)
- Make a ray structure
  - Ray length
  - Ray angle offset
- Thouroughly check for any makefile errors !!
- check that all functions that use malloc are failure safe
  - ft strdup in parsing 
- find out a way to exit and clean all heap memory gracefully in order to fully utilize leak detectors as they flag even heap memory in use at exit 
- create a minimap
  - cast rays to represent the FOV of the player
- test parsing of different maps

# Questions

