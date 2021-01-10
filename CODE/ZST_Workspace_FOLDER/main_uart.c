/*Tutorial Number:3
 * Website: https://circuitdigest.com/search/node/STM8S
 * Code by: Aswinth Raj
 */
 /*Control on-board LED through USART
 * PD5 - UART1-Tx	(D14)
 * PD6 - UART1-Rx	(D15)
 */
 //Required Headers
 #include "STM8S.h"
 #include "stm8s103_serial.h" //https://github.com/CircuitDigest/STM8S103F3_SPL/blob/master/stm8s103%20Libraries/stm8s103_Serial.h
 #define test_LED GPIOB, GPIO_PIN_5
 //Main Code 
 void main(void)
 {
 
//Variable declarations
 
char ch;
 
//Pin defanitions
//Declare PB5 as push pull Output pin
 
GPIO_Init (test_LED, GPIO_MODE_OUT_PP_LOW_SLOW);
Serial_begin(9600);
Serial_print_string("Enter command");
Serial_newline();
while (1) //Loop function 
{
   if(Serial_available())
   {
Serial_print_string("You have pressed: ");
ch = Serial_read_char();
Serial_print_char(ch);
Serial_newline();
 
if (ch == '0')
GPIO_WriteHigh(test_LED); //LED OFF
 
if (ch == '1')
GPIO_WriteLow(test_LED); //LED ON
}
}
}
