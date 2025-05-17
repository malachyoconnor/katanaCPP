Simple CPP project to take a group of jpegs and convert them into a PDF.

Directory structure must be the following:

TopLevelDirectory
 |- chapter001
    |- page001.jpeg
    |- page002.jpeg
    ...
 |- chapter002
...

Depends on Libharu: https://github.com/libharu/libharu

TODO:
 - Take user input
 - Improve performance
   - One approach could be to load images into a list first (async?) then read from memory