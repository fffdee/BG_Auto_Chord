#ifndef __BG_CHORD_CONFIG_H__
#define __BG_CHORD_CONFIG_H__
 
#include<stdint.h>

#define CHORD_DEBUG

#ifdef CHORD_DEBUG
#define   NORMAL_DEBUG_LEVEL 
#define   HIGH_DEBUG_LEVEL  
//#define   SUPER_DEBUG_LEVEL 
#endif

#define FACTORY_MODE_CHOICE CHOICE_SIMPLEFY_MODE    //Chose the chord mode for factory setting

#define CHOICE_SIMPLEFY_MODE 0             
//#define CHOICE_NORMAL_MODE   1
#define CHOICE_ENJOY_MODE    1

#define CONFIG_ENABLE_INT    1                   //Config Model state for factory setting   
#define CONFIG_SPAN_INT      2                  //Config Max guitar fret span for factory setting
#define CONFIG_KEY_INT       0                   //Config guitar key for factory setting
#define CONFIG_MAX_RULE_INT  4
#define CONFIG_MAX_FRET_INT  12


//Define the data struct to record per var state while model working.
typedef struct _Chord_run_data
{
    uint8_t mode;
    uint8_t enable;
    uint8_t span;
    uint8_t key;
    uint8_t result_count;
    uint8_t rule_count;
    uint8_t chord_rule[6];
    uint8_t chord_result[6][7];
    uint8_t last_chord[7];

} Chord_run_data;

//Define the struct for convert chord name from string to int.
typedef struct{
		
		char* first_name;
        char* second_name;
		uint8_t Tone_value;

}Chord_tone;

//chord's property
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
		{"maj7",{4,7,11,0,0,0}},
		{"m7",{3,7,10,0,0,0}},
		{"7",{4,7,10,0,0,0}},
        {"+",{4,8,0,0,0,0}},			

};

#endif