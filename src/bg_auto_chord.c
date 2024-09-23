#include "bg_auto_chord.h"
#include "bg_chord_config.h"
#include<stdio.h>

const uint8_t base_tone [6] = {40,45,50,55,59,64};

BG_ERR BG_chord_enable(uint8_t enable);
BG_ERR BG_chord_setmode(uint8_t mode);
BG_ERR BG_chord_setkey(int8_t key);
BG_ERR BG_chord_Auto_Chord(uint8_t * chord, uint8_t tone, uint8_t property);
uint8_t BG_chord_status(void);
uint8_t BG_chord_getmode(void);
uint8_t BG_chord_getkey(void);

BG_Chord BG_chord = {

    .Enable = BG_chord_enable,
    .SetMode = BG_chord_setmode,
    .SetKey = BG_chord_setkey,
    .Auto_Chord = BG_chord_Auto_Chord,
    .Status = BG_chord_status,
    .GetMode = BG_chord_getkey,

};

typedef struct _Chord_run_data
{
    uint8_t mode;
    uint8_t enable;
    uint8_t span;
    uint8_t key;
    uint8_t result_count;
    uint8_t chord_result[3][7];
    uint8_t last_chord;
    
}Chord_run_data;


Chord_run_data chord_run_data = {

    .mode = 0,
    .enable = 0,
    .span = 4,
    .last_chord = 0,
    .key = 0,
    .result_count = 0,
    .chord_result = {0}

};

BG_ERR BG_chord_enable(uint8_t enable){
    
    if(enable>1) return INVALID_INPUT;

    chord_run_data.enable = enable;

    return SUCCESS;

}

BG_ERR BG_chord_setkey(int8_t key){

   if(key<-12||key>12) return KEY_ERR;
   
   chord_run_data.key = key;

   return SUCCESS; 

}

uint8_t BG_chord_getkey(void){

    return chord_run_data.key;

}


BG_ERR BG_chord_setmode(uint8_t mode){
    
    if(mode>1) return INVALID_INPUT;

    chord_run_data.mode = mode;

    return SUCCESS;

}


void OutPutChord(uint8_t *chord)
{
    for(uint8_t i = 0; i<6; i++)
        chord[i] += base_tone[i]+chord[i];

}

BG_ERR BG_chord_Auto_Chord(uint8_t * chord, uint8_t tone, uint8_t property){

    uint8_t low_string=0;
    uint8_t i;
    uint8_t string;
    uint8_t chord_count;
    uint8_t count;
    uint8_t rule_count;
    uint8_t check_flag;

    for(i = 0; i<6; i++)
        if(chord_rule[tone].intervallic[i]==0)
            rule_count = i+1;

    for (string = 0; string < 3; string++)
    {
        for (i = 0; i<12; i++)
        {
            if(tone == (base_tone[low_string]+i)%12){
                
                count = 0;
                while(count<low_string){

                    chord_run_data.chord_result[chord_run_data.result_count][count]=0xff;
                    printf("The value is %d\n",chord_run_data.chord_result[chord_run_data.result_count][count]);
                    
                    count++;
                }
                chord_run_data.chord_result[chord_run_data.result_count][6]
                 = low_string;
                chord_run_data.chord_result[chord_run_data.result_count][low_string]
                 = i;
                 printf("The value2 is %d\n",chord_run_data.chord_result[chord_run_data.result_count][count]);
                chord_run_data.result_count++;
                
                #ifdef CHORD_DEBUG
                    printf("The Chord count is %d ,string is %d, val is %d \n"
                    ,chord_run_data.result_count,low_string,i);
                #endif

                
            }
        } 
   
        low_string++;
    
    }

    count = 0;
    for(chord_run_data.result_count = 0; chord_run_data.result_count<3; chord_run_data.result_count++){
        
        for(string = chord_run_data.chord_result[chord_count][6]+1; string<6; string++){
            
             for (i = 0; i<12; i++){  
                
                // if(count>2){
                //      if((tone+chord_rule[tone].intervallic[count])%12==i){

                //         chord_run_data.chord_result[chord_run_data.result_count][string] = i; 
                   
                //         count++;
                //     }

                // } else 
                // {
                    
                    
                        if((base_tone[string]+i)%12==(chord_rule[tone].intervallic[count]+tone)%12){

                            chord_run_data.chord_result[chord_run_data.result_count][string] = i; 
                            //check_flag = 1;
                            count++;

                        }else{

                                
                        } 

                    
                    
                }

                
                
             }
            

        }

    }
    

   


    for(uint8_t k=0; k<3; k++)
         for(i=0; i<7; i++)       
        printf("The Chord count is %d  val is %d \n"
            ,k,chord_run_data.chord_result[k][i]);
            
    
        
    

    return SUCCESS;


}

uint8_t BG_chord_status(void){

    return chord_run_data.enable;

}

uint8_t BG_chord_getmode(void){

     return chord_run_data.mode;

}