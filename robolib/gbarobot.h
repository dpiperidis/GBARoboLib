/* 
 * This file is part of the GBARoboLib distribution (https://github.com/dpiperidis/GBARoboLib).
 * Copyright (c) 2020 Dimitris Piperidis.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _GBAROBOT_H
#define _GBAROBOT_H 1

#define RGB(r,g,b) (unsigned short)((r)+((g)<<5)+((b)<<10))
#define WHITE 0xFFFF
#define BLACK 0x0000
#define RED 0x00FF
#define GREEN 0x0EE0
#define BLUE 0xEE00
#define MAGENTA 0xF00F


#define REG_DISPCNT *(unsigned long*)0x4000000
#define MODE_3 0x3
#define BG2_ENABLE 0x400

#define MEM_IO				0x04000000	// Register Base, all HW Registers are in here.
#define R_CTRLINPUT		*(volatile unsigned short*)(MEM_IO + 0x130)
#define A_PRESSED        (~R_CTRLINPUT & 0x0001)
#define B_PRESSED       ((~R_CTRLINPUT & 0x0002)>>1)
#define SELECT_PRESSED  ((~R_CTRLINPUT & 0x0004)>>2)
#define START_PRESSED   ((~R_CTRLINPUT & 0x0008)>>3)
#define RIGHT_PRESSED   ((~R_CTRLINPUT & 0x0010)>>4)
#define LEFT_PRESSED    ((~R_CTRLINPUT & 0x0020)>>5)
#define UP_PRESSED      ((~R_CTRLINPUT & 0x0040)>>6)
#define DOWN_PRESSED    ((~R_CTRLINPUT & 0x0080)>>7)
#define R_PRESSED       ((~R_CTRLINPUT & 0x0100)>>8)
#define L_PRESSED       ((~R_CTRLINPUT & 0x0200)>>9)



#define RCNT *(volatile unsigned short*)(MEM_IO+0x134)
#define RCNT_GPIO_MODE 0x8000
#define SC (1<<0)
#define SD (1<<1)
#define SI (1<<2)
#define SO (1<<3)
#define DIR_SC (1<<4)  /* ( 1=output , 0=input) */
#define DIR_SD (1<<5)  /* ( 1=output , 0=input) */
#define DIR_SI (1<<6)  /* ( 1=output , 0=input) */
#define DIR_SO (1<<7)  /* ( 1=output , 0=input) */

// Define constants
#define HIGH 1
#define LOW 0

#define true 1
#define false 0

#define ON 1
#define OFF 0

#define FORWARD 1
#define BACKWARDS -1
#define STOP 0

// define motor io
#define M1A (1<<5)
#define M1B (1<<4)
#define M2A (1<<6)
#define M2B (1<<3)
#define M3A (1<<2)
#define M3B (1<<0)
#define M4A (1<<7)
#define M4B (1<<1)

// define digital outputs
#define D0 (1<<8)
#define D1 (1<<9)
#define D2 (1<<10)
#define D3 (1<<11)
#define D4 (1<<12)
#define D5 (1<<13)
// Motors enable output (1-> motors enabled, 0 -> motors disabled)
#define ME (1<<14)

//define analog inputs
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 6


void Print(unsigned char *str);
void digitalWrite(unsigned short _pin, unsigned char state);
unsigned short analogRead(unsigned char _pin);
unsigned char digitalRead(unsigned short _pin);
void DrawPixel(int x, int y, unsigned short color);
void moveMotors(short M1, short M2, short M3, short M4);
void ClearScreen();
void DrawPixel(int x, int y, unsigned short color);
void SetTextBackgroundColor(unsigned short color);
void SetTextColor(unsigned short color);
void gotoXY(int x, int y);
void setMotors(unsigned char state);
void SetTextColor(unsigned short color);

static void _RobotInit(void);
static void _initialize(void);
static void _set_output(unsigned short data);
static void _drawChar(int left, int top, unsigned char letter);
static void _set_motor(short M, char mnum);
#endif
