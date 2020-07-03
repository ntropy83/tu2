![QMake Build Matrix](https://github.com/ntropy83/tu2/workflows/QMake%20Build%20Matrix/badge.svg)
[![Language Grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/vim/vim.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/ntropy83/TUII/context:cpp)

# TUII
PMS - Project Management System

![MainWindow](https://github.com/ntropy83/tu2/blob/master/img/MainWindow.png)

## version 1.0.0
- create and modify projects
- list them with infos
- add milestones and project advancements
- create a project evaluation

# Libraries and Dependencies
Created with QtCreator 4.11 / Qt 5.14 (Gcc 9.2.0, 64bit)

Needs package:

Ubuntu: qt5-default<br>
Arch: qt5-base

# Build instructions in Linux
Clone the repo and cd into the new folder

```
mkdir build
cd build
qmake ../Projektverwaltung.pro
make && make clean
```
The executable will go to the newly created build directory 

# Cross Compile
can be cross compiled as 32bit program to Windows with mxe for Qt
(https://github.com/mxe/mxe)<br>
The 32bit cross-compiled windows version is in the release of the repo

```
export PATH=<mxe root>/usr/bin:$PATH
<mxe root>/usr/i686-pc-mingw32/qt5/bin/qmake
make -f Makefile.Release && make clean -f Makefile.Release
```
