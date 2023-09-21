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
- [ ] Sanitize AV and AC
- [ ] Add sanitization of the map (all void is covered by walls)
  - check if any HORIZONTAL TERM is precedented with a WALL element
  - check if any array starts with a WALL element
  - check if any VOID is surrounded by VOID and WALL element
  - check if first and last array are all WALL or VOID elements
- [ ] Thouroughly check for any makefile errors !!
- [ ] find out a way to exit and clean all heap memory gracefully in order to fully utilize leak detectors as they flag even heap memory in use at exit 
- [ ] check that all functions that use malloc are failure safe
  - ft strdup in parsing 
- [ ] test parsing of different maps
- [ ] modularize square and circle drawing functions
- [ ] there's duplication in minimap raycasting file
- [ ] !!!!!!!! put the width and the height of the map in a struct to help for checks in vertical and horizontal raycasters
  - why is it needed anyways
- [ ] add more sanitization for surface colors
# Questions

- should we rectangle our map
- !!!!!!!!!!!!!!!!! if we dont rectangle the map should we take teh max width/height or the min and why
- even after fishbowl theres a go pro effect still