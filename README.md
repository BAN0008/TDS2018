# TDS2018
## Dependencies
[SFML 2](https://www.sfml-dev.org/download/sfml/2.4.2/)
[mingw\(For compiling in windows\)](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)
## Compile
```bash
g++ src/AStar.cpp src/Wall.cpp src/NPC.cpp src/Player.cpp src/GameObject.cpp src/Global.cpp src/Main.cpp -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -g -o build/debug/a.out
```
