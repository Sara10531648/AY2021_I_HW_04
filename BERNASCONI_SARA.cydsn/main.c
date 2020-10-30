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
#include "InterruptRoutines.h"
#include "stdio.h"


//LAMP STATES
#define LAMP_ON 1
#define LAMP_OFF 0

//THE THRESHOLD BELOW WHICH THE LAMP MUST TURN ON IN mV
#define THRESHOLD 2500

//AMUX CHANNELS
#define CHANNEL_PR 0
#define CHANNEL_POT 1

//VARIABLES TO SAVE OUTPUT OF SAMPLING
int32 PR_digit;
int32 POT_digit;

//VARIABLES TO SAVE CONVERTION IN mV
int32 PR_mv;
int32 POT_mv;

//LAMP IS OFF WHEN THE DVICE TURNS ON
uint8_t LAMP_STATE=LAMP_OFF;
 
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //START UART,ADC,AMUX
    UART_Start();
    AMux_Init();
    ADC_DelSiG_Start();

    //ENABLE INTERRUPTS
    isr_RX_StartEx(Custom_ISR_RX);
    isr_ADC_StartEx(Custom_ISR_ADC);

    //SET INTERRUPT FLAG 
    PR=0;
    
    //SET HEAD & TAIL OF STANDARD PACKET
    DataBuffer[0]=0XA0;
    DataBuffer[TRANSMIT_BUFFER_SIZE-1]=0XC0;

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        
        if( PR)
        {   PR=0;
            //SELECTION OF PHOTORESISTANCE CHANNEL
            AMux_FastSelect(CHANNEL_PR);
            PR_digit=ADC_DelSiG_Read32();
            PR_mv=ADC_DelSiG_CountsTo_mVolts(PR_digit);
           
            //NOT ENOUGH LIGHT-->LAMP MUST TURN ON
            if( PR_mv<=THRESHOLD)
            //SAVE THE STATUS AT WHICH THE LAMP MUST BE IN THIS CYCLE
                LAMP_STATE=LAMP_ON;
            else 
            LAMP_STATE=LAMP_OFF;
            //cambia qui lamp state
            switch(LAMP_STATE)
                {
                    case LAMP_ON :
                    {
                    //SELECTION OF POTENTIOMETER CHANNEL
                    AMux_FastSelect(CHANNEL_POT);
                    POT_digit=ADC_DelSiG_Read32();
                    if (POT_digit<0)    POT_digit=0;
                    if (POT_digit>65535)    POT_digit=65535;
                    //LIGHT INTENSITY IS SET BY THE POTENTIOMETER
                    PWM_LAMP_WriteCompare(POT_digit);
                    POT_mv=ADC_DelSiG_CountsTo_mVolts(POT_digit);
                    }
                     break;
                    
                case LAMP_OFF :
                    {
                    //TURN OFF THE LAMP
                    PWM_LAMP_WriteCompare(LAMP_OFF);
                    //IF THE LAMP IS OFF POTENTIOMETER IS NOT SAMPLED
                    POT_mv=-1;
                    }
                     break;
                    
                default:
                break;
                }
        
            //SAVE SAMPLED DATA IN BUFFER
            DataBuffer[1]=PR_mv >> 8;
            DataBuffer[2]=PR_mv & 0XFF;
            DataBuffer[3]=POT_mv >> 8;
            DataBuffer[4]=POT_mv & 0XFF;
            
            //SEND DATA BUFFER TO TERMINAL
            UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE);
        }
    }
}
        
        
        
               
        
    
    


/* [] END OF FILE */
