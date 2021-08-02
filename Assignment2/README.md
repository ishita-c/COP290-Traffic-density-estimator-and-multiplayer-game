Mario-Bros-In-A-Maze
(Built in C++ using SDL2.0)

Instructions on how to build and run the game:
Tested on Linux 64-bit (Distribution- Ubuntu 20.04)

## Install Dependencies

> sudo apt-get -y install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
(SDL2.0, SDL-mixer 2.0, SDL_ttf 2.0)
> sudo apt-get -y install libenet-dev
(enet for networking)


## Run
1. Clone the repo OR download zip and extract.
2. Open terminal and follow below commands:

For single Player:
> cd mario
> make
> ./mario-bros

For Multiplayer:
Run the folowing in a new terminal
> g++ -o server enet_server.cpp -lenet
>./server
Open two terminals and run:
>make
>./mario-bros

Select "Play with Luigi" option


## How to Play
Player Controls:	Up, Left, Down, Right:	↑ ← ↓ →


## Resources Used
* https://github.com/DarkMuffinJoe/Pacman
* https://github.com/schuay/pacman/tree/master/src
* https://github.com/ehauckdo/pacman
* https://github.com/lobo-old/killer-pacman
* https://github.com/mrnsapple/Arcade
* https://github.com/BeardedPlatypus/PacMan
* https://github.com/ndinhtuan/pacmansdl
* https://github.com/FMLPhongVan/Pacman
* https://github.com/Yizak/Pacman-clone
* https://github.com/AustinSmith29/pacman
* 

Graphics and Audio:
* https://github.com/Gabriel-Espinoza/Flutter.Soundboard/tree/master/assets
* https://github.com/pataruco/Class_sounds/tree/master/audiofiles
* https://github.com/pascaldevink/git-smb/tree/master/share/data/smb


