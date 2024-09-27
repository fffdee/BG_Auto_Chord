#ifndef __BG_CHORD_CONFIG_H__
#define __BG_CHORD_CONFIG_H__
 
#include<stdint.h>

#define CHORD_DEBUG

#ifdef CHORD_DEBUG
//#define   HIGH_DEBUG_LEVEL  
//#define   SUPER_DEBUG_LEVEL 
#endif

#define SIMPLEFY_MODE 0             
#define NORMAL_MODE   1
#define ENJOY_MODE    2


typedef struct{
		
		char* first_name;
        char* second_name;
		uint8_t Tone_value;

}Chord_tone;

typedef struct{
		
		char* name;
		uint8_t intervallic[6];

}Chord_rule;

Chord_tone chord_tone[12] = {

	{"C","C",0},
    {"SC","bB",1},	
    {"D","D",2},	
    {"SD","bE",3},	
    {"E","E",4},
    {"F","F",5},
    {"SF","bG",6},
    {"G","G",7},
    {"SG","bA",8},
    {"A","A",9},
    {"SA","bB",10},
    {"B","B",11},

};

Chord_rule chord_rule[] = {

		{"3",{4,7,0,0,0,0}},
		{"m",{3,7,0,0,0,0}},
		{"+",{4,8,0,0,0,0}},
		{"°",{3,6,0,0,0,0}},
		{"maj7",{4,7,11,0,0,0}},
		{"m7",{3,7,10,0,0,0}},
		{"7",{3,7,10,0,0,0}},			

};

#endif