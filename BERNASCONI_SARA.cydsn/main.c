/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "isr.h"
#include "stdio.h"

#define HIGH 1
#define LOW 0

#define LAMP_ON HIGH
#define LAMP_OFF LOW


extern int32 value_mv;
uint8_t LAMP_STATE=0;
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
AMux_Start();
//?
AMux_FastSelect(0);
ADC_DelSiG_Start();
Timer_Start();
UART_Start();
isr_ADC_StartEx(Custom_ISR_ADC);



//DataBuffer[0]=0XA0;
//DataBuffer[TRANSMIT_BUFFER_SIZE-1]=0XC0;
PacketReadyFlag=0;
ADC_DelSiG_StartConvert();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        if (PacketReadyFlag==1)
        {
            UART_PutString(DataBuffer);
            PacketReadyFlag=0;
            LAMP_STATE= Pin_LAMP_Read();
            if (value_mv<2 && LAMP_STATE==LAMP_OFF)
            //led on
                Pin_LAMP_Write(LAMP_ON);
            if (value_mv>=2 && LAMP_STATE==LAMP_ON)
                Pin_LAMP_Write(LAMP_OFF);
               
        }
    
    }
}

/* [] END OF FILE */
