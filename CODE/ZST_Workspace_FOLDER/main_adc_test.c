// reads value on ADC channel 2, which is AIN2 on Pin PC4 (pin 14)
// and send it via UART 

#include "stm8s.h"
#include "stdafx.h"

#define WITH_UART_EXP 1

	 char count = 0;
	 char digit[5] = "";

int main( void ){

  uint16_t 	i; // Always use standardized variable types...
  uint16_t 	nCount 					= 0;
  uint16_t 	adc_value 			= 0;
  uint8_t 	adc_h 					= 0;
  uint8_t 	adc_l 					= 0;
  uint16_t 	nAdc_Buffer[10] = {0,0,0,0,0,0,0,0,0,0};
  uint16_t 	nAdc_Hold 			= 0;

    // Reset GPIO port B and set up output for onboard LED  (pin 5)
  GPIO_DeInit(GPIOB);
	GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
		
    //Initialization of the clock
    /* Clock divider to HSI/1 */
    //CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);

  UART_Config();						// UART Config
  ADC_Config();							// ADC  Config
  ADC1_StartConversion();		// Start your ADC engine!
    		
    // The main loop
  while(1){

		delay_ms(500);
// Light on board LED
    GPIO_WriteLow(GPIOB, GPIO_PIN_5);

// Read 10 times (it works, but not a great idea)
    for ( nCount = 0; nCount< 10; nCount++){
      nAdc_Buffer[nCount] = ADC1_GetConversionValue();
      nAdc_Hold += nAdc_Buffer[nCount];
    }
// Overwrite average into first cell 
		nAdc_Buffer[0] = nAdc_Hold / 10;
    adc_value = nAdc_Buffer[0];
    adc_h = (uint8_t)((adc_value & 0xff00)>>8);
    adc_l = (uint8_t)((adc_value & 0x00ff));

    for ( nCount = 0; nCount< 10; nCount++){
      nAdc_Buffer[nCount] = 0;
    }
    nAdc_Hold = 0;

    #ifdef WITH_UART_EXP
//        UART1_SendData8((uint8_t)0x00);
//				UART1_SendData8((uint8_t)adc_h);
//				UART1_SendData8((uint8_t)0x20);
//				UART1_SendData8((uint8_t)adc_l);
//				UART1_SendData8((uint8_t)adc_value);
			if (adc_value == 0){
				UART1_SendData8((char)'0');															// Single space
				while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); 	// wait for sending
				UART1_SendData8((char)' ');															// Single space
				while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); 	// wait for sending
			}else{	
			while (adc_value != 0) //split the int to char array 
			{
				digit[count] = adc_value%10;
				count++;
				adc_value = adc_value/10;
			}
			while (count !=0) //print char array in correct direction 
			{
				UART1_SendData8(digit[count-1] + 0x30);								// Send number as a character
				while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); // wait for sending 
				count--; 
			}

			UART1_SendData8((char)' ');															// Single space
			while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); 	// wait for sending

//				UART1_SendData8((uint8_t)0x0A);												// Line Feed
//				while (UART1_GetFlagStatus(UART1_FLAG_TXE) == RESET); // wait for sending
	};
		#endif // WITH_UART_EXP

// LED Off
		GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
	}
}

static void UART_Config(void){
    //Reset uart
  UART1_DeInit();
  UART1_Init((uint32_t) 9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE );

}

static void ADC_Config( void ){
//  GPIO_Init(GPIOB, GPIO_PIN_0, GPIO_MODE_IN_FL_NO_IT );
	GPIO_Init (GPIOC, GPIO_PIN_4, GPIO_MODE_IN_FL_IT);
	ADC1_DeInit();
//  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_0, ADC1_PRESSEL_FCPU_D2, ADC1_EXTTRIG_TIM,DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL0, DISABLE );
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, ADC1_CHANNEL_2, ADC1_PRESSEL_FCPU_D2, ADC1_EXTTRIG_TIM,DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL2, DISABLE );
}



