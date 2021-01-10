// YX5300 MP3 player controled via USART
// PD5 - UART1-Tx	(D14)
// PD6 - UART1-Rx	(D15)
 
 
 #include "STM8S.h"
 #include "stm8s_delay.h" 
 #include "stm8s103_serial.h" //https://github.com/CircuitDigest/STM8S103F3_SPL/blob/master/stm8s103%20Libraries/stm8s103_Serial.h
 #define test_LED GPIOB, GPIO_PIN_5

//************ Command byte **************************/
#define CMD_NEXT_SONG     0X01  // Play next song.
#define CMD_PREV_SONG     0X02  // Play previous song.
#define CMD_PLAY_W_INDEX  0X03
#define CMD_VOLUME_UP     0X04
#define CMD_VOLUME_DOWN   0X05
#define CMD_SET_VOLUME    0X06

#define CMD_SNG_CYCL_PLAY 0X08  // Single Cycle Play.
#define CMD_SEL_DEV       0X09
#define CMD_SLEEP_MODE    0X0A
#define CMD_WAKE_UP       0X0B
#define CMD_RESET         0X0C
#define CMD_PLAY          0X0D
#define CMD_PAUSE         0X0E
#define CMD_PLAY_FOLDER_FILE 0X0F

#define CMD_STOP_PLAY     0X16
#define CMD_FOLDER_CYCLE  0X17
#define CMD_SHUFFLE_PLAY  0x18 //
#define CMD_SET_SNGL_CYCL 0X19 // Set single cycle.

#define CMD_SET_DAC 0X1A
#define DAC_ON  0X00
#define DAC_OFF 0X01

#define CMD_PLAY_W_VOL    0X22
#define CMD_PLAYING_N     0x4C
#define CMD_QUERY_STATUS      0x42
#define CMD_QUERY_VOLUME      0x43
#define CMD_QUERY_FLDR_TRACKS 0x4e
#define CMD_QUERY_TOT_TRACKS  0x48
#define CMD_QUERY_FLDR_COUNT  0x4f

/************ Options **************************/
#define DEV_TF            0X02

void sendCommand(int8_t command, int16_t dat);

char i = 0;

/*********************************************************/
/* MAIN CODE													   						     */
/*********************************************************/
void main(void)
 {
//Pin defanitions
//Declare PB5 as push pull Output pin
 
	GPIO_Init (test_LED, GPIO_MODE_OUT_PP_LOW_SLOW);
	GPIO_WriteHigh(test_LED); //LED OFF

	Serial_begin(9600);
	sendCommand(CMD_SEL_DEV, DEV_TF);		// Select SD card (only do this once) 
	
  GPIO_WriteLow(test_LED); 						// LED ON
	sendCommand(CMD_NEXT_SONG, 0);			// Play next song      


// Check for the unsolicited message that says it has finished playing .
	i = 0;
	while(i <600){
		i++;
		delay_ms(500);
		if (Serial_available())
		{
			i = 600;
			GPIO_WriteHigh(test_LED); //LED OFF
		}
    
	};


}

/*********************************************************/
/*Send command to the MP3      													 */
/*Parameter:-	int8_t 				command                      */
/*Parameter:-	int16_ dat  	parameter for the command    */
/*********************************************************/
void sendCommand(int8_t command, int16_t dat)
{
  delay_ms(20);
	Serial_print_char(0x7e);								// Start Byte
	Serial_print_char(0xff);								// Version
	Serial_print_char(0x06);								// Length
	Serial_print_char(command);							// Command
	Serial_print_char(0x00);								// Feedback (1-yes,0-No)
	Serial_print_char((int8_t)(dat >> 8));  // dataHI
	Serial_print_char((int8_t)(dat));       // dataLOW
	Serial_print_char(0xef);								// End Byte
	delay_ms(100);
}
