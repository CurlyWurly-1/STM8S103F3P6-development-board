# STM8S103F3P6-development-board

*Updating this repo is in progress*

The STM8S103F3P6 is a 20 pin PIC microcontroller development board with 16 GPIO pins. It is a cheap, quite powerful and easily available
This repository is for collecting "C" programs (COSMIC) that can be used to program the STM8S103F3P6 development board as seen in the picture below (via the STVD IDE)   

Please note:
 - The following "C" programs are stored in folder "CODE" of this repository  
   - STM8S_blink.c  
   - STM8S_uart.c
   - STM8S_adc.c 	 	 
 - When you buy this board, you only get the blue coloured development board as seen in the picture below. Be aware that the header pins are not provided. You will need to buy some header pins and solder them yourself.
 - To program the STM8S103, you also need a "ST-Link V2" USB device which connects to the boards 4 upright pins via a 4 wire dupont harness. (See below for more information about this) 
 - There are 2 ways to supply regulated 5V to this dev board. 
   - Via the supplied micro USB connector (N.B. the data pins are NOT connected - you can only power the board theough this USB port.
   - Via the "ST-Link V2" USB Device  - This technique works fine as long as you are not powering anything else from the development board.

<img src="images/STM8SF3P6_board.jpg" alt="Dev board"/>


# Development Board Schematic information
The Schematic for this board is pictured below and it has the following components:
 - Micro USB Connector  - used to supply power to the board only
 - Reset button         - Resets the microcontroller 
 - "Poweron" LED        - It is always on when power is applied to the board (annoyingly bright !!)
 - one LED              - This LED is connected to pin B5 - to light the LED, you need to output a low to sink current
 - ICSP pins            - White housing of 6 pins - used for the programming interface
 - 20 "Lower" pins      - It is usual to solder the 20 header pins below. This means you can plug the development board into a breadboard
 - 4  "Upper" pins      - It is usual to solder these 4 pins upwards. This means that while the development board is plugged into a breadboard, you can easily access these 4 pins for attaching to the "ST-Link V2" USB device. 


<img src="images/stm8blue-schematic.jpg" alt="Schematic"/>


# "ST-LINK V2" device
If you want to program the board as per these examples, you will also need a "ST-LINK V2" USB device like the one you see in the picture below - If you haven't already got one, make sure you buy it at the same time as you buy the STM8S103F3P6 Development board.  

This "ST-LINK V2" device is plugged into a PC's USB port and the 4 wire harness connects to 4 "upper" pins of the development board. Bear in mind that the harness is short, so consider getting a USB extender cable so you are not resticted in where you have to put the development board - Ideally you want it near you so you can easily see it and connect things to it.  

<img src="images/pickit3.jpg" alt="Pickit 3"/>


# How to get familiar with this board
- There are series of excellent blogs adn tutorials out there. Here are a ferw of them

  - STARTING STM8 MICROCONTROLLERS
    - http://embedded-lab.com/blog/starting-stm8-microcontrollers/
  - Getting Started with STM8S using STVD and Cosmic C Compilerck
    - https://circuitdigest.com/microcontroller-projects/getting-started-with-stm8s-using-stvd-and-cosmic-c-compiler
  - Blue-pill STM32 Programming Using ST-LINK V2 Dongle
    - https://www.youtube.com/watch?v=KgR3uM21y7o
  - GPIO Functions on STM8S using Cosmic C and SPL – Blinking and Controlling LED with Push Button
    - https://circuitdigest.com/microcontroller-projects/gpio-functions-on-stm8s-using-cosmic-c-and-spl-blinking-led-with-push-button
  - ADC on STM8S using Cosmic C Compiler – Reading Multiple ADC Values and Displaying on LCD
    - https://circuitdigest.com/microcontroller-projects/adc-on-stm8s-using-c-compiler-reading-multiple-adc-values-and-displaying-on-lcd
  - Getting Started with STM8 Microcontrollers
    - https://maker.pro/custom/tutorial/getting-started-with-stm8-microcontrollers


# How to set up and install the software and components
The above info covers this, however, please note the following tips and tricks
 - Remember you have to install the COSMIC compiler, the STVD software and the STVP software

 - Download this "STM8S103" folder and all its contents to a new folder (e.g. call it "C:\ZST_STM8S103")

 - Create your workspaces in this folder ("C:\ZST_STM8S103")

 - When you have to, set the C compiler to "C:\Program Files (x86)\COSMIC\FSE_Compilers\CXSTM8"

 - When you have to set a file to be used by the programmer for the "Program memory", set it to the "S19" file from folder "Debug"

 - Execute STVD
  - Set compatability mode for program "C:\Program Files (x86)\STMicroelectronics\st_toolset\stvd\stvdebug.exe" to be "Windows XP SP 3".
    This is to remove the error that says "no access to file default.wed".

  - Replace C:\Program Files (x86)\STMicroelectronics\st_toolset\stvp\tools.cnf. (N.B. You will find the file in the folder) 
    This is to stop STVD crashing when you press "programmer" 

  - In your project, highlight folder "SRC" and add both files "stm8s_delay.c" and "stm8s_gpio.c" 
    These have been separated because they are different for each chip

  - In your project, highlight folder "INC" and add file "stm8s.h"
    In this file, you will have already uncommented the line sothat it points to "STM8S103" 

  - Highlight the workspace file (e.g. "zst_workspace"), right click and press "Settings" to display the "Settings" window. 
    Change the following and press "OK" 
    - Change "Settings for" to "Debug"   (top left) and then select tab "C Compiler" - Change "C language" to default   
    - Change "Settings for" to "Release" (top left) and then select tab "C Compiler" - Change "C language" to default  


# How to Program the STM8S103F3P6 development board
 - Ensure the COSMIC compiler, The STVD IDE and STVP programmer are installed in your PC as per what you have seen in the links above
 - On your PC, 
   - If you haven't already done so, prepare the folder as downloaded and described in the previous section e.g. a folder called; C:\ZST_WORKSPACE_FOLDER
   - Execute STVD and open the workspace file  
   - Highlight which project you want to use by right clikcing and setting as the "active" project 
   - Press "Build" -> "Rebuld All" (check that there are no errors)
   - Press the "Programmer" button and after about 4 seconds, a window will be displayed. Press "start" to program your device
