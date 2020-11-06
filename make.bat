@echo off
set name=robot_avoid_obstacles_example
set path=C:\files\devkitadv\bin;%path%

IF EXIST "%CD%\%name%.gba" (
  del "%CD%\%name%.gba"
)

gcc -o "%CD%\%name%.elf" "%CD%\%name%.c" "%CD%\robolib\gbarobot.c"

IF EXIST "%CD%\%name%.elf" (
  objcopy -O binary "%CD%\%name%.elf" "%CD%\%name%.gba"
  gbafix "%CD%\%name%.gba"
  del "%CD%\%name%.elf"
)
pause
