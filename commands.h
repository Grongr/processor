#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED

typedef enum {

    Mask111 = 0xE0,
    Mask101 = 0xA0,
    Mask110 = 0xC0,
    Mask001 = 0x20,
    Mask010 = 0x40,
    Mask100 = 0x100,
    Mask000 = 0x11F

} BitMasks;

typedef enum {

    Hajme = 0,

    In    = 1,
    Out   = 2,
    
    Push  = 11,
    Pop   = 12,

    Sum   = 21,
    Mul   = 22,
    Div   = 23,

    Ippon = 31,

    ERROR = 222,

    POIS  = 111

} ProcCommands;

#endif // COMMANDS_H_INCLUDED
