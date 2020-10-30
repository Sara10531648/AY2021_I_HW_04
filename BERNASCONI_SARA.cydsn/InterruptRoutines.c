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
#include "InterruptRoutines.h"
#include "project.h"

CY_ISR(Custom_ISR_ADC)

{
    //READ TIMER STATUS REGISTER TO BRING INTERRUPT LINE LOW
    Timer_ReadStatusRegister();
    
    //IF I HAVE PRESSED B/b AND THE TIMER CALLS THE INTERRUPT PR IS SET TO 1
    PR=1;

}
CY_ISR(Custom_ISR_RX)
{
    //è NECESSARIO??no
    if(UART_ReadRxStatus()==UART_RX_STS_FIFO_NOTEMPTY)
    {
    //SAVE BYTE RECIVED   
    char recived=UART_ReadRxData();
    
    switch( recived){
       //IF B/b IS PRESSED THE DEVICE IS NOW ACTIVE WITH ALL ITS FUNCTIONALITIES
        case 'B':
        case 'b':
        {
         
            //TURN ON THE ON BOARD LED WHILE SENDING DATAS FROM UART TO TERMINAL(togli on)
            Pin_LED_Write(1);
             //START PWM
            PWM_LAMP_Start();
            //START TIMER
            Timer_Start();
           
            
        }
            break;
        
        //IF S/s IS PRESSED THE DEVICE IS NO MORE ACTIVE (NO SAMPLING, NO CONTROL ON THE LAMP)
        case 'S':
        case 's':
        {
            
            //TURN OFF LED
            Pin_LED_Write(0);
            //STOP TIMER 
            Timer_Stop();
            //TURN OFF LIGHT 
            PWM_LAMP_Stop();
            //SET PR=0 AS THE INITIAL STATE 
            PR=0;
         
            
        }
        break;
        
        default:
        break;
        }
    }
}
    
    
    
/* [] END OF FILE */
