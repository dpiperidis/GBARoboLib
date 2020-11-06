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

#include "font.h"
#include "gbarobot.h"
#include <math.h>

// video buffer
unsigned short* videoBuffer = (unsigned short*)0x6000000;

unsigned short _outputs = 0x8000; //Stop motors and set chip select pin of the adc to high


unsigned short _textcolor = WHITE;
unsigned short _color = WHITE;
unsigned short _textbackcolor = BLACK;
volatile int _curX = 0;
volatile int _curY = 0;


int main(void){
   _initialize();
   setup();
   for(;;) loop();
   
   return 0;
}

static void _initialize(){
   _RobotInit();
   ClearScreen();
}

static void _RobotInit(){
   // Set to general purpose communication
   // Also is setting SC, SD, SO, SI to inputs
   RCNT = RCNT_GPIO_MODE;
   // SET SC, SD, SO to outputs (Keep SI to input)
   RCNT |= DIR_SC;
   RCNT |= DIR_SD;
   RCNT |= DIR_SO;
   //Set LOW
   RCNT &= ~SD;
   RCNT &= ~SC;
   RCNT &= ~SO;

   // switch to video mode 4 (240x160 8bit double buffered)
   REG_DISPCNT = (MODE_3 | BG2_ENABLE);

   // Stop motors (and disable motors output)
   _set_output(_outputs);
}

static void _set_output(unsigned short data){
   unsigned char i;
   // make sure clock is low
   RCNT &= ~SC;

   for (i=0; i<16; i++){
      // output LSB
      if (data & 0x01) RCNT |= SD;
      else RCNT &= ~SD;
      // Raise clock pin
      RCNT |= SC;
      // shift data to right
      data = data >>1;
      // set clock pin to low
      RCNT &= ~SC;
   }
   // output data
   RCNT |= SO;
   RCNT &= ~SO;
}

static void _drawChar(int left, int top, unsigned char letter){
  int x, y;
  int draw;  
  /*if (letter>127){
	  char ss[6];
           sprintf(ss,"%d",letter);
           Print(ss);
	   return;
	  //letter -= 29;
  }*/
  for(y=0; y<8; y++){
    // grab pixel from the font char
    draw = font[(letter-32)*8 + y];
     for(x=0; x<8; x++){
         // if pixel is 1, then draw it
         if (draw & 0x01) DrawPixel(left + x, top + y, _textcolor);
         else  DrawPixel(left + x, top + y, _textbackcolor);
         draw >>= 1;
     }
  }
}

static void _set_motor(short M, char mnum){
    if (!M)
       switch (mnum){
       case 1: _outputs &= ~(M1A|M1B);
               break;
       case 2: _outputs &= ~(M2A|M2B);
               break;
       case 3: _outputs &= ~(M3A|M3B);
               break;
       case 4: _outputs &= ~(M4A|M4B);
               break;
       }
    else{
       if (M>0){
           switch (mnum){
           case 1: _outputs |= M1A;
                   _outputs &= ~M1B;
                   break;
           case 2: _outputs |= M2A;
                   _outputs &= ~M2B;
                   break;
           case 3: _outputs |= M3A;
                   _outputs &= ~M3B;
                   break;
           case 4: _outputs |= M4A;
                   _outputs &= ~M4B;
                   break;
           }
       }else{
           switch (mnum){
           case 1: _outputs &= ~M1A;
                   _outputs |= M1B;
                   break;
           case 2: _outputs &= ~M2A;
                   _outputs |= M2B;
                   break;
           case 3: _outputs &= ~M3A;
                   _outputs |= M3B;
                   break;
           case 4: _outputs &= ~M4A;
                   _outputs |= M4B;
                   break;
           }
       }
    }
}

unsigned short analogRead(unsigned char _pin){
    unsigned char i;

   // Set chip select to low
   _outputs &= ~(1<<15);
   _set_output(_outputs);

   unsigned short commandout = _pin;
   commandout |= 0x18; //  # start bit + single-ended bit
   commandout <<= 3; //    # we only need to send 5 bits here

   for (i=0; i<5; i++) {
     if (commandout & 0x80)
        RCNT |= SD;
     else
        RCNT &= ~SD;

      // Raise clock pin
      RCNT |= SC;
      // shift data to left
      commandout <<= 1;
      // set clock pin to low
      RCNT &= ~SC;

   }

   unsigned short adcout = 0;
   // read in one empty bit, one null bit and 10 ADC bits
   for (i=0; i<12; i++) {
     // set and reset clock pin
     RCNT |= SC;
     RCNT &= ~SC;
     adcout <<= 1;
     if (RCNT&SI)
       adcout |= 0x1;
   }

  //set chip select to high
   _outputs |= (1<<15);
   _set_output(_outputs);

   adcout >>= 1; // first bit is 'null' so drop it
   return adcout;
}

unsigned char digitalRead(unsigned short _pin){
  if (analogRead(_pin)>512) return HIGH;
  else return LOW;
}

void digitalWrite(unsigned short _pin, unsigned char state){
  if (state) _outputs |= _pin;
  else _outputs &= ~_pin;
  _set_output(_outputs);
}


void DrawPixel(int x, int y, unsigned short color){
   videoBuffer[y*240 + x] = color;
}

void SetTextBackgroundColor(unsigned short color){
  _textbackcolor = color;
}

void SetTextColor(unsigned short color){
  _textcolor = color;
}

void SetColor(unsigned short color){
  _color = color;
}

void gotoXY(int x, int y){
	_curX = 8*x;
	_curY = 8*y;
}

void Print(unsigned char *str){
   while (*str){
	   if (*str<200){
	      if (*str=='\n'){
		     _curY += 8;
		     _curX = 0;
	      }else if (*str=='\r'){
		     _curX = 0;
          }else{
		    _drawChar(_curX, _curY, *str);
            _curX += 8;
	      }
       }
	   *str++;
   }
}

void moveMotors(short M1, short M2, short M3, short M4){
   _set_motor(M1, 1);
   _set_motor(M2, 2);
   _set_motor(M3, 3);
   _set_motor(M4, 4);
   _set_output(_outputs);
}

void setMotors(unsigned char state){
   if (state) _outputs |= ME;
   else _outputs &= ~ME;
   _set_output(_outputs);
}

void ClearScreen(){
  // Claer screen
  int x,y;
  for(y=0; y<127; y++){
     for(x=0; x<159; x++){
         DrawPixel(x, y, BLACK);
     }
  }
}
