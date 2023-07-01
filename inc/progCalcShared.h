#ifndef PROG_CALC_SHARED_H
#define PROG_CALC_SHARED_H

extern "C" {

#define CSTM_EVENT_TYPE_BYTE		2010
#define CSTM_EVENT_TYPE_WORD		2011
#define CSTM_EVENT_TYPE_DWORD    	2012

#define CSTM_EVENT_OP_AND			2020
#define CSTM_EVENT_OP_OR			2021
#define CSTM_EVENT_OP_XOR			2022
#define CSTM_EVENT_OP_NOT			2023

#define CSTM_EVENT_LSH				2030
#define CSTM_EVENT_RSH				2031

#define CSTM_EVENT_MODE_SIGNED		2040
#define CSTM_EVENT_MODE_UNSIGNED	2041

#define CSTM_EVENT_INPUT_STRING     2050

#define CSTM_EVENT_HEX			    2060
#define CSTM_EVENT_DEC			    2061
#define CSTM_EVENT_OCT			    2062
#define CSTM_EVENT_BIN			    2063

typedef enum
{
    MODE_SIGNED = 0,
    MODE_UNSIGNED,
    MODE_UNKNONW
}mode_signed_t;

typedef enum 
{
    LENGTH_8BIT = 0,
    LENGTH_16BIT,
    LENGTH_32BIT,
    LENGTH_UNKNONW
}length_t;

typedef enum
{
    TYPING_MODE_HEX = 0,
    TYPING_MODE_DEC,
    TYPING_MODE_OCT,
    TYPING_MODE_BIN,
    TYPING_MODE_UNKNOWN
}typingmode_t;

}// extern C

#endif

