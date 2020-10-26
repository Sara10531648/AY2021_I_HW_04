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
#include "isr.h"
#include "project.h"
//necessario se single ended
//value of pr

extern uint8_t PR;




CY_ISR(Custom_ISR_ADC)
{
    Timer_ReadStatusRegister();
    PR=1;
        
    //value_digit= ADC_DelSiG_Read32();
    //if (value_digit<0)
    //value_digit=0;
    //if (value_digit>65535)
    //value_digit=65535;
    
    //value_mv=ADC_DelSiG_CountsTo_Volts(value_digit);
   //DataBuffer[1]=value_digit >> 8;
    //DataBuffer[2]=value_digit & 0XFF;
    //sprintf(DataBuffer," Sample %ld mV\r\n",value_mv);
    
    //PacketReadyFlag=1;

}
/* [] END OF FILE */
