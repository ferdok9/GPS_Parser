

#include <xc.h>
//#include <p24FJ256GB108.h>

#include "CONFIG.h"
#include "DataTypes.h"

#include <stdio.h>
#include <uart.h>
#include "UART.h"
#include "GPIOx.h"
#include "GPS_Parser.h"

#include "timer.h"

//volatile char cReceiveGPS = 0;

unsigned int state = 0;
unsigned char temp1;

char flag1 = 0;

void TimerInit(void);

int main(void)
{
    uint8 u8ForCountL = 0;
    //Disable Watch Dog Timer
    RCONbits.SWDTEN	 = 0;

    //Set up I/O Port
    AD1PCFGL	 =	0xFFFF;             //set to all digital I/O
    TRISB        =	0xF3FF;             //configure all PortB as input

    LedInit();
    
//    TimerInit();
    UARTsInit();



    while(1)
    {
        if( ReceiveGPSFlagMask == ( u16ByteFlags & ReceiveGPSFlagMask ) )
        {
            GPS_ReceiveChar(cReceiveGPS, GPS_Msg_Buff);
            u16ByteFlags &= ~ReceiveGPSFlagMask;
        }
        
        if( ReceiveMsgFlagMask == ( u16ByteFlags & ReceiveMsgFlagMask ) )
        {
            for(u8ForCountL = 0; ((GPS_Msg_Buff_Ptr - 1) >= u8ForCountL); u8ForCountL++)
            {
                UART3PutChar( GPS_Msg_Buff[u8ForCountL] );
            }

            u16ByteFlags &= ~ReceiveMsgFlagMask;
        }
    }

    return(0);
}

