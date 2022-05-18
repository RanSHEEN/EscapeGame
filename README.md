Escape Game
=

Program Languages
-
`C` `Makefile` `SDL2`

Commands
-
To build the project : 
```//Shell
make
```
To execute the menu launcher : 
```//Shell
./main
```
To clean it all : 
```//Shell
make clean
```

Description
-
Project realised in the course **Projet et Methode** in our 3rd year of Electronic and Computer Science course at the INSA Rennes.
This program corresponds to the **game engine of an escape game**.
The **game engine** follows the functioning of a state's machine and the **graphic interface** was made using the SDL2 library.
Coding files are seperated in **4 categories** : Model, View, Controller and Test (for the "tests unitaires") according to the **MVC program structure**.
Compiling creates all the `.a` files of a static library in a specific `'lib'` file that is then called in the `main.c` file when launching the program.

Installing SDL and Cmocka Libraries
-
###SDL
System environment : `Ubuntu 16.04 x64`  
To install `SDL2` in Linux/Unix, use the following commands in terminal :
```//Shell  
sudo apt-get install libsdl2-dev
```     
```//Shell
sudo apt-get install libsdl2-image-dev
``` 
```//Shell
sudo apt-get install libsdl2-mixer-dev
```
###CMocka


Authors
-
Marie QUELO     
Margot BEDAT    
Ran XIN     
Kuilong LI

Special Thanks to
-
Karol DESNOS (Academic Adviser)     
Huichun ZHEN (Character Designer)   
Robin DESPLANQUES   
Enzo LEVEQUE & Tanguy RAUFFLET
