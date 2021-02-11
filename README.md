# TUII
PMS - Project Management System

![MainWindow](https://github.com/ntropy83/tu2/blob/master/img/MainWindow.png)

## version 1.3.0
- create and modify projects
- list them with infos
- add milestones and project advancements
- create a project evaluation

# Libraries and Dependencies
Created with QtCreator 4.14 / Qt 5.15 (Gcc 9.2.0, 64bit)

Needs package:

Ubuntu: qt5-default<br>
Arch: qt5-base

# Install
Arch User Repo: https://aur.archlinux.org/packages/tu2

# Build from scratch on Linux
Clone the repo and cd into the new folder

```
mkdir build
cd build
qmake ../Projektverwaltung.pro
make && make clean
```
The executable will go to the newly created build directory 

# Cross Compile
can be cross compiled as a standalone 32bit exe to Windows with mxe for Qt
(https://github.com/mxe/mxe)<br>

```
export PATH=<mxe root>/usr/bin:$PATH
<mxe root>/usr/i686-pc-mingw32/qt5/bin/qmake
make -f Makefile.Release && make clean -f Makefile.Release
```
