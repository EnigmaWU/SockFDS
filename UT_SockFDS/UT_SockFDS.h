#ifndef __UT_SOCKFDS_H__
#define __UT_SOCKFDS_H__

#define SFH_MAGIC 0x53464D47 // "SFMG"

typedef enum 
{
    SFT_I_FRAME = 1,
    SFT_P_FRAME = 2,

} SockFrameType_T;

//SockFDS_Srv send SockFrame to each acceped SockUsr.
//SockFrame is a byte stream with SockFrameHeader and SockFrameBody.
//SockFrameHeader is SockFrameHeader_T.
//SockFrameBody is byte stream following SockFrameHeader, and it's length is SockFrameHeader.length.
typedef struct 
{
    unsigned int Magic;//SFH_MAGIC
    SockFrameType_T Type;
    unsigned int Length;
    unsigned int SeqID;
    
} SockFrameHeader_T, *SockFrameHeader_pT;

#endif // __UT_SOCKFDS_H__