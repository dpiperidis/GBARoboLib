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
 
#include "robolib/gbarobot.h"
#include <stdio.h>

#define THRESS 200
unsigned char navigate = 0;

void setup(){  
  // Enable motors
  setMotors(ON);
}

void loop(){

   // Read values from sesnors
   unsigned short leftIR = analogRead(A0);
   unsigned short rightIR = analogRead(A1);
   char ss[3];
   // Print to the screen the values from the sensors
   gotoXY(0,3);       
   Print("Left IR = ");       
   sprintf(ss,"%d",leftIR);
   Print(ss);
   Print("    "); //Print 4 spaces to erase whatever is left from previous value
   gotoXY(0,4);
   Print("Right IR = ");
   sprintf(ss,"%d",rightIR);
   Print(ss);
   Print("    "); //Print 4 spaces to erase whatever is left from previous value        
              
   if (UP_PRESSED){
       // Start moving
       moveMotors(FORWARD,FORWARD,FORWARD,FORWARD); 		   
       // start navigation
       navigate = 1;
       gotoXY(0,0);
       Print("Moving ");
   }
   if (A_PRESSED){
       // Stop Moving
       moveMotors(STOP,STOP,STOP,STOP);
       // stop navigation
       navigate = 0;
       gotoXY(0,0);
       Print("Stopped");
   }
       
   // Navigation code. Avoiding any objects
   if (navigate){
	  gotoXY(0,1);
      if ((leftIR>THRESS)&&(rightIR>THRESS)){
		  // Object at the front.
		  // Check which is greater
		  if (leftIR<rightIR){
             // Object at right. Turn left to avoid
			 Print("Turn Left ");
			 moveMotors(FORWARD,BACKWARDS,BACKWARDS,FORWARD);
		  }else{
			 // Object at left. Turn right to avoid
			 Print("Turn Right");
			 moveMotors(BACKWARDS,FORWARD,FORWARD,BACKWARDS);
		  }	              
      }else if (leftIR>THRESS){
		   // Object at left. Turn right to avoid
		   Print("Turn Right");
           moveMotors(BACKWARDS,FORWARD,FORWARD,BACKWARDS);
	  }else if (rightIR>THRESS){
		   // Object at right. Turn left to avoid
		   Print("Turn Left "); 		     
		   moveMotors(FORWARD,BACKWARDS,BACKWARDS,FORWARD);
	  }else{
		   // No object. Just go Forward
		   Print("Go Forward"); 		     
		   moveMotors(FORWARD,FORWARD,FORWARD,FORWARD); 
	  }
   }           
   
}


/* END OF FILE */
