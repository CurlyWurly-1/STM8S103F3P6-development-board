#include "STM8S.h"
#include "stm8s_delay.h" 
 
void main (void)
{
  bool i = 0;

// 	The following line deinitialises the GPIO. 
//	When you reconfigure or setup a hardware peripheral 
//	for the first time, you must deinitialize it before 
//	using it. Whilst this is not mandatory, this is 
//	considered good practise because it removes any chance 
//	of wrong/conflicting configurations. 
  GPIO_DeInit(GPIOB);
//   GPIO_DeInit(GPIOD);

/*	After deinitialisation, we need to set up the GPIOs. 
		Inputs can be with or without internal pull-up resistors
		Outputs can be either push-pull totem-pole 
		or open drain types. 
		Each pin can be individually configured and does not 
		have any dependency on another. 
		
		EXAMPLE GPIO SETUP CODE LINES
		1) GPIO_Init(GPIOB, GPIO_PIN_7, GPIO_MODE_IN_FL_NO_IT)
		The above code would set GPIO PB7 as a floating input 
		with no interrupt capability. This example is 
		appropriate for an input that is physically wired up
		with an external "pull up" resistor
		2) GPIO_Init(GPIOD, GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST); 
		The above code would set GPIO PB7 as a fast	push-pull
		output. 
*/

// set pin 5 (LED) to be a fast	push-pull output with a 
// default value of HIGH (LED is off - to light it, you have
// to set a value of LOW to Sink current)
	GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
	

	i = 0;															// Set I to LOW
	GPIO_WriteLow(GPIOB, GPIO_PIN_5);		// Turn on LED by outputting a LOW
	while(1) 														// Main Loop code 	
  {
      switch(i)
      {
        case 0:
        {
            delay_ms(50);
						i ^= 1;
						break;
        }
        case 1:
        {
            delay_ms(450);
						i ^= 1;
						break;
        }
      }
// This is neat command to toggle the GPIO output
		GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
		}
	}