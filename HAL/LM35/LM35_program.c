 /******************************************************************************
 *
 * Module: LM35 Temperature Sensor
 *
 * File Name: LM35_program.c
 *
 * Description:  contain Implementation of LM35 Driver
 * 
 * Author: Hesham Shehata
 *
 *******************************************************************************/


/**************************                   INCLUDES                   **************************/
#include "../../MCAL/ADC/ADC_interface.h"
#include "LM35_interface.h"
#include "LM35_config.h"
#if(ADC_Interrupt_State_interface == ADC_Interrupt_Enable_interface)
    #define F_CPU 8000000 
    #include <util/delay.h>

#endif
uint8 LM35_GetTemperature(void)
{
    uint8 Temp = 0;
    #if(ADC_Interrupt_State_interface == ADC_Interrupt_Enable_interface)
        /*  Start conversion only   */
        ADC_OnlyStartConversionGeneral(LM35_PIN);
        /*  Delay until convertion end and g_adcResult update by ISR as it need 13 clock cycle */
        _delay_ms(1);
        /*  calculate Temperature  */
        Temp =(uint8) ( ((uint32)g_adcResult * SENSOR_MAX_TEMPERATURE * REFRENCE_Volt_AVCC_OR_AREF_OR_internal_interface) / (ADC_MAX_VALUE * SENSOR_MAX_VOLT_VALUE) );
    #elif(ADC_Interrupt_State_interface == ADC_Interrupt_Disable_interface)
        /*  Start converion     */
        uint16 adc_value = ADC_ReadChannelSingleConvertion(LM35_PIN);
        /*  calculate Temperature  */
        Temp =(uint8) ( ((uint32)adc_value * SENSOR_MAX_TEMPERATURE * REFRENCE_Volt_AVCC_OR_AREF_OR_internal) / (ADC_MAX_VALUE * SENSOR_MAX_VOLT_VALUE) );
    #endif

    return Temp;
}

