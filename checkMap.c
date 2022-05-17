/*
*
* Copyright (C) Copyright IBM Corp. 1977, 2014
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
* * Contributors:
*   Colin Paice
*
*/
/* Include standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

/* Include mqseries headers */
#include <cmqc.h>
#include <cmqcfc.h>
#include <cmqxc.h>
#include <cmqstrc.h>

typedef char * (*pProcess)(MQLONG value);

struct tagValueLabel
{	
 MQLONG value;	
 char * name1;
 char * name2; 
};
typedef struct tagValueLabel ValueLabel;

  //
  struct tagDoIt 
{ 
  MQLONG   which; 
  pProcess routine; 
}; 
typedef struct tagDoIt doIt; 
                                           
  #ifdef no                                         
  // use this when testing the PYQMI Processing  
  #define MQMAP(a,b) {a,(pProcess) b } 

  doIt types[]  =
  {
  #include <MQMAP.h> 
  {99999999, MQTT_STR}
  }
   #endif  

// use this section for normal processing
   #define MQMAP(a,b) {a,#a,#b}
   ValueLabel  types[] = { 
    #include <MQMAP.h>    
   };
 
   

int main(int argc, char *argv[] )
{
  int i;
  int count = sizeof(types)/sizeof(types[0]);
  int previous = 0;
  printf("// if any are out of order; after processing use sort -k5,5 to get them in order\n"); 
  printf("// Then replace MQMAP.h with the generated file \n");
 
  for ( i = 0;i<count;i++)
  {
 
    if (previous >= types[i].value)
    {
           printf("Problems with %s, %d value is out of sequence %d\n",types[i].name1, types[i].value,previous);
    }
    previous = types[i].value;
 
    //  create the formatting list
    printf("    MQMAP(%s, %s),  // %5d\n", types[i].name1,types[i].name2,types[i].value);       
  }
}
