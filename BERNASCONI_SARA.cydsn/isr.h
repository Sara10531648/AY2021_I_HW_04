/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __INTERRUPT_ROUTINES_H
    #define __INTERRUPT_ROUTINES_H
    #include "cytypes.h"
    #include "stdio.h"
    
    //#define BYTE_TO_SEND 2
    #define TRANSMIT_BUFFER_SIZE 16//1+ BYTE_TO_SEND +1
    
    CY_ISR_PROTO(Custom_ISR_ADC);
    
    
    char DataBuffer[TRANSMIT_BUFFER_SIZE];
    //keyword usata da compilatore: durante compilazione se ho if(flag) e flag inizialmente a 0 non compila quella parte di codice
    volatile uint8 PacketReadyFlag;

#endif
/* [] END OF FILE */
