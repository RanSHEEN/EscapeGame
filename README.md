Escape Game
=

Program Languages
-
`C` `Makefile` `SDL2`

Commands
-
To build the project : 
```//Shell
make all
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

Installing SDL Libraries
-
System environment : `Ubuntu 16.04 x64`  
To install `SDL2` in Linux/Unix, use the following commands in terminal :
```//Shell  
sudo apt-get install libsdl2-dev
```     
To install `SDL2-image` : 
```//Shell
sudo apt-get install libsdl2-image-dev
``` 
To install `SDL2-mixer` : 
```//Shell
sudo apt-get install libsdl2-mixer-dev
```

Installing Cmocka Libraries
-
Install `CMocka` from official website : [Click Here To Download CMocka](https://cmocka.org/files/)         
To uncompress the package : 
```//Shell
xz -d cmocka-1.1.1.tar.xz
tar -xvf cmocka-1.1.1.tar
```
To install :    
```//Shell
cd cmocka-1.1.1
mkdir build
cd build
cmake ..
make
sudo make install
ldconfig
```

Code Test
-
Before running Test, install CMocka library (refer to the precedent subsection).

Open Terminal in the folder Tests and run the unit Tests:
```//Shell
make Run_Tests
```

When the tests are run, you can find the coverage infos in the folder Coverage_Info in the index.html document.

To clean the coverages-info :
```//Shell
make clean_coverage 
```

Memory leak
-
To Analyse the Memory leaks of the code :
```//Shell
 valgrind --leak-check=yes ./main 2> mem.txt
```
The Memory Leaks infos will be written in the document mem.txt.

/!\ SDL create Memory leaks that cannot be resolved


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
