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
    
    //2 BYTES FOR PHOTORESISTOR'S SIGNAL, 2 BYTES FOR POTENTIOMETER'S SIGNAL
    #define BYTE_TO_SEND 4
    //TRANSMIT 1 BYTE(HEAD)+4 BYTES FOR SIGNALS+1 BYTE (TAIL)
    #define TRANSMIT_BUFFER_SIZE 1+ BYTE_TO_SEND +1
    
    CY_ISR_PROTO(Custom_ISR_ADC);
    CY_ISR_PROTO(Custom_ISR_RX);
    
    
    uint8 DataBuffer[TRANSMIT_BUFFER_SIZE];
    //INTERRUPT FLAG
    volatile uint8 PR;

#endif
/* [] END OF FILE */
