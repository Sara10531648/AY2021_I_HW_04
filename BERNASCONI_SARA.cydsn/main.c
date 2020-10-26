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

#define MIDIUM 128
#define LOW 0

#define LAMP_ON MIDIUM
#define LAMP_OFF LOW


int32 PR_mv;
int32 PR_digit;
int32 POT_digit;
uint8_t LAMP_STATE=LAMP_OFF;
uint8_t PR;
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
AMux_Start();
//?
AMux_FastSelect(0);
ADC_DelSiG_Start();
Timer_Start();
UART_Start();
PWM_LAMP_Start();
isr_ADC_StartEx(Custom_ISR_ADC);



//DataBuffer[0]=0XA0;
//DataBuffer[TRANSMIT_BUFFER_SIZE-1]=0XC0;
//PacketReadyFlag=0;
//ADC_DelSiG_StartConvert();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        if( PR==1)
        {
            AMux_FastSelect(0);
            PR_digit=ADC_DelSiG_Read32();
            PR_mv=ADC_DelSiG_CountsTo_Volts(PR_digit);
            sprintf(DataBuffer," Sample %ld mV\r\n",PR_mv);
            UART_PutString(DataBuffer);
            PR=0;
            //NO LIGHT
            if( PR_mv<=2)
            switch(LAMP_STATE)
                {
                    case LAMP_ON :
                    {
                    AMux_FastSelect(1);
                    POT_digit=ADC_DelSiG_Read32();
                    //LIGHT INTENSITY IS SET BY THE POTENTIOMETER
                    PWM_LAMP_WriteCompare(POT_digit);
                   
                    }
                     break;
                case LAMP_OFF :
                    {
                    //PWM_LAMP_WriteCompare(128);
                    LAMP_STATE= LAMP_ON;
                    }
                    break;
                
                }
             else
                //THERE IS ENOUGH LIGHT IN THE AMBIENT
                if(LAMP_STATE==LAMP_ON)
                {
                    LAMP_STATE=LAMP_OFF;
                    //TURN OFF THE LAMP
                    PWM_LAMP_WriteCompare(LAMP_OFF);
                }
        }
    }
}
        
        
        /*if (PacketReadyFlag==1)
        {
            UART_PutString(DataBuffer);
            PacketReadyFlag=0;
            LAMP_STATE= Pin_LAMP_Read();
            if (value_mv<2 && LAMP_STATE==LAMP_OFF)
            //led on
                Pin_LAMP_Write(LAMP_ON);
            if (value_mv>=2 && LAMP_STATE==LAMP_ON)
                Pin_LAMP_Write(LAMP_OFF);*/
               
        
    
    


/* [] END OF FILE */
