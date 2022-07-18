# GBARoboLib
GameBoy Advance Library which resembles arduino programming style

# Requirements
This library requires DevKit Advance to be properly installed in your system
http://devkitadv.sourceforge.net/ \
Optionally you can install Visual Boy Advance to test your programs

# Important Note
You will need something like the supercard SD adapter for GameBoy *(found on eBay)* in order to run your programs/roms to your GameBoy. However you'll need to fix the roms first or else they will not load. For that you need the Gbafix program which you have to compile it from source.\
Download the source from:\
https://github.com/devkitPro/gba-tools/blob/master/src/gbafix.c

* **In Linux**\
gcc -o gbafix gbafix.c

* **In Windows**\
You need to install gcc first. For example you can use TDM-GCC (https://jmeubank.github.io/tdm-gcc/)
Then run
gcc -o gbafix.exe gbafix.c

# Usage
Copy the directory robolib to your project folder _(where your main c file is)_. Include GBARoboLib to your main c file with the command\
#include "robolib/gbarobot.h"\
See the example codes _(helloworld.c and robot_avoid_obstacles_example.c)_ in this repository in order to understand how to use this library

# bat files
I have included bat files _(make_NAME_OF_EXAMPLE_CODE.bat)_ to automate the compile process in Windows\
To create your own, just copy one of these bat files and edit the second and the third line. Change the second line with the name of your main c file _(without the extention)_ and the third line with the path where you copied DevKit Advance bin directory in your system
