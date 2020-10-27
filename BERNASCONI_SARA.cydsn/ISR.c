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
//value of pr
#include "UART.h"
#include "Timer.h"
#include "PWM_LAMP.h"

extern uint8_t PR;

uint8_t Remote=0;


CY_ISR(Custom_ISR_ADC)

{
    Timer_ReadStatusRegister();
    if (Remote==1)
    PR=1;

}
CY_ISR(Custom_ISR_RX)
{
    if(UART_ReadRxStatus()==UART_RX_STS_FIFO_NOTEMPTY)
    {
        
    char recived=UART_ReadRxData();
    switch( recived){
        case 'B':
        case 'b':
        {
            UART_PutString("sono on\r\n");
            Remote=1;
            Pin_LED_Write(1);
            Timer_Start();
            
        }
            break;
        case 'S':
        case 's':
        {
            Remote=0;
            Pin_LED_Write(0);
            Timer_Stop();
            PWM_LAMP_WriteCompare(0);
            PR=0;
            UART_PutString("sono off\r\n");
        }
        break;
        default:
        break;
    }
    }
}
    
    
    
/* [] END OF FILE */
