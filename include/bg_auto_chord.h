#ifndef __BG_AUTO_CHORD_H__
#define __BG_AUTO_CHORD_H__

#include<stdint.h>

typedef enum
{
    SUCCESS = 0,
    INVALID_INPUT,
    KEY_ERR,

}BG_ERR;


typedef struct _BG_Chord
{
    BG_ERR (*SetMode)(uint8_t);
    BG_ERR (*SetKey)(int8_t);
    BG_ERR (*Enable)(uint8_t);
    BG_ERR (*Auto_Chord)(uint8_t*,uint8_t,uint8_t);
    uint8_t (*Status)(void);
    uint8_t (*GetMode)(void);

}BG_Chord;

extern BG_Chord BG_chord;


#endif 