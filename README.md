terrain-generator
=================

A simple terrain generator that uses the diamond-square algorithm for generating the map and SFML for displaying it.

Full disclosure: I heavily based this algorithm off of the one from [javagamexyz](http://javagamexyz.blogspot.com/2013/03/terrain-generation.html)

To use this program run it, it will display the map. Press enter to generate a new map. Press the + or - keys to zoom in and out.

The algorithm itself takes a few parameters

1. n: this determines the size of the map which is 2^n
2. wmult and hmult: these are the width and heigh multipliers that extend the map in either direction.
3. smoothness and fineness: these affect the overall shape of the maps.

It should also be noted that I currently have this set up to generate islands. I did this by initializing the edges to negative numbers.
