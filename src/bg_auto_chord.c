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
    .span = 3,
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
    uint8_t low_string_val[3];
    uint8_t i;
    uint8_t string;
    uint8_t chord_count;
    uint8_t count;
    uint8_t rule_count;
    uint8_t check_flag;
    uint8_t loop_count;
    for(i = 0; i<6; i++)
        if(chord_rule[property].intervallic[i]!=0)
            rule_count = i+1;

    for (string = 0; string < 3; string++)
    {
        for (i = 0; i<12; i++)
        {
            if(tone == (base_tone[low_string]+i)%12){

                printf("***********************************************\n");
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
                
                //Update low string's value;
                low_string_val[count] = chord_run_data.chord_result[chord_run_data.result_count][count];
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
    uint8_t chord_rules[rule_count+1];
    chord_rules[0] = tone;
    for(i=1; i<rule_count+1; i++)
    {
        chord_rules[i] = (chord_rule[property].intervallic[i-1]+tone)%12;
    }
    printf("***********************************************\n");  
    for(i=0; i<rule_count+1; i++)
    {
        printf("chord rules is %d\n",chord_rules[i]); 
    }
    

    for(chord_run_data.result_count = 0; chord_run_data.result_count<3; chord_run_data.result_count++){
         
         check_flag = 0;
         loop_count = 0;
         string = chord_run_data.chord_result[chord_run_data.result_count][6]+1;
         printf("string is %d",string);
         printf("***********************************************\n");
         while(string<6&&loop_count<6){
         
             for (i = 0; i<13; i++){  
                        
                        printf("chord is %d run tone is %d,string is %d, fret is %d, right tone is %d\n",chord_run_data.result_count,(base_tone[string]+i)%12,string ,i,chord_rules[count]);
                        if(((base_tone[string]+i)%12==(chord_rules[count])%12)
                            && string < 6 
                        ){
                              printf("flag is %d\n",check_flag);
                              if(check_flag==1){

                                
                                if( 
                                   i<=low_string_val[chord_run_data.result_count]
                                //    ||low_string_val[chord_run_data.result_count]-chord_run_data.span<i
                                ){
                                    
                                    printf("intervallic is %d string is %d fret is %d\n", count, string, i);
                                    chord_run_data.chord_result[chord_run_data.result_count][string] = i; 
                                    string++;
                                    
                                    if(low_string_val[chord_run_data.result_count]>i){
                                        if(low_string_val[chord_run_data.result_count]-i>2){
                                            string = chord_run_data.chord_result[chord_run_data.result_count][6]+1;
                                            check_flag=2;
                                            printf("flag in\n");
                                        }
                                    }else{
                                         if(i-low_string_val[chord_run_data.result_count]>2){
                                             string = chord_run_data.chord_result[chord_run_data.result_count][6]+1;
                                             check_flag=2;
                                        }

                                    }
                                    
                                }
                                    
                              }
                              else if (check_flag==2)
                              {
                                 if( i < chord_run_data.span+low_string_val[chord_run_data.result_count]
                                    && i>= low_string_val[chord_run_data.result_count]
                                 ){
                                        
                                      
                                       printf("intervallic is %d string is %d fret is %d\n", count, string, i);
                                        chord_run_data.chord_result[chord_run_data.result_count][string] = i; 
                                        string++;
                                        
                                  }
                              }
                              else{

                                if( 
                                   chord_run_data.span+low_string_val[chord_run_data.result_count]>i
                                //    ||low_string_val[chord_run_data.result_count]-chord_run_data.span<i
                                ){
                                    if(i<low_string_val[chord_run_data.result_count]) check_flag =1;
                                    else check_flag =2;
                                    printf("intervallic is %d string is %d fret is %d\n", count, string, i);
                                    chord_run_data.chord_result[chord_run_data.result_count][string] = i; 
                                    string++;
                                    
                                }
                                
                                
                              }
                                

                            }
    

                    
                }
            loop_count++;
            count++;
            i=0;
            if(count>rule_count) count=0;
            printf ("count add is %d\n", count);
                
                
         }
            

    }

    
    

   


    for(uint8_t k=0; k<3; k++){

   
        printf("***********************************************\n");
         for(i=0; i<7; i++)       
            printf("The Chord count is %d  string is %d  val is %d \n"
                , k, i, chord_run_data.chord_result[k][i]);
            
     }
        
    

    return SUCCESS;


}

uint8_t BG_chord_status(void){

    return chord_run_data.enable;

}

uint8_t BG_chord_getmode(void){

     return chord_run_data.mode;

}