# GBARoboLib
GameBoy Advance Library which resembles arduino programming style

# Reguirements
This library requires DevKit Advance to be properly installed in your system
http://devkitadv.sourceforge.net/
Optionally you can install Visual Boy Advance to test your programs

# Important Note
You will need somethong like the supercard SD adapter for GameBoy (found on eBay) in order to run your programs/roms. However you need to fix the roms first or else they will not load. For that you will need the Gbafix which you have to compile from source.
Download the source from:
https://github.com/devkitPro/gba-tools/blob/master/src/gbafix.c

# In Linux
gcc -o gbafix gbafix.c

# In Windows
You need to install gcc first. For example you can use TDM-GCC (https://jmeubank.github.io/tdm-gcc/)
Then run
gcc -o gbafix.exe gbafix.c
