/**
  @page F7_DualCDC USB Device Composite Application
  
  @verbatim
  ******************************************************************************
  * @file    USB_Device/F7_DualCDC/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USB Composite DualCDC application.
  ******************************************************************************
  *
  * Copyright (c) 2024 STMicroelectronics International N.V. All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim
  
@par Application Description

Use of the USB device application based on the Composite Classe.

This is a typical application on how to use the STM32F7xx USB OTG Device peripheral, it shows how to develop a composite USB Device communication Class "CDC ACM" based application.

The application is designed to emulate an USB-to-UART bridge following the Virtual COM Port (VCP) implementations, the code provides all required device descriptors associated to both Classes descriptor report to build a composite compliant USB Dual_CDC_device

At the beginning of the main program the HAL_Init() function is called to reset all the peripherals,
initialize the Flash interface and the systick. The user is provided with the SystemClock_Config()
function to configure the system clock (SYSCLK) to run at 216 MHz. The Full Speed (FS) USB module uses
internally a 48-MHz clock which is coming from a specific output of two PLLs: main PLL or PLL SAI.
In the High Speed (HS) mode the USB clock (60 MHz) is driven by the ULPI.

The 48 MHz clock for the USB FS can be derived from one of the two following sources:
  – PLL clock (clocked by the HSE): If the USB uses the PLL as clock source, the PLL VCO clock must be programmed
    to output 432 MHz frequency (USBCLK = PLLVCO/PLLQ).
  – PLLSAI clock (clocked by the HSE): If the USB uses the PLLSAI as clock source, the PLLSAI VCO clock must be programmed
    to output 384 MHz frequency (USBCLK = PLLSAIVCO/PLLSAIP).

When the VCP application is started, the STM32 MCU is enumerated as serial communication port and is
configured in the same way (baudrate, data format, parity, stop bit) as it would configure a standard 
COM port. The 7-bit data length with no parity control is NOT supported.

During enumeration phase, three communication pipes "endpoints" are declared in the CDC class
implementation (PSTN sub-class):
 - 1 x Bulk IN endpoint for receiving data from STM32 device to PC host:
   When data are received over UART they are saved in the buffer "UserTxBuffer". Periodically, in a 
   timer callback the state of the buffer "UserTxBuffer" is checked. If there are available data, they
   are transmitted in response to IN token otherwise it is NAKed.
   The polling period depends on "CDC_POLLING_INTERVAL" value.
    
 - 1 x Bulk OUT endpoint for transmitting data from PC host to STM32 device:
   When data are received through this endpoint they are saved in the buffer "UserRxBuffer" then they
   are transmitted over UART using interrupt mode and in meanwhile the OUT endpoint is NAKed.
   Once the transmission is over, the OUT endpoint is prepared to receive next packet in
   HAL_UART_TxCpltCallback().
    
 - 1 x Interrupt IN endpoint for setting and getting serial-port parameters:
   When control setup is received, the corresponding request is executed in CDC_Itf_Control().
   In this application, two requests are implemented:
    - Set line: Set the bit rate, number of Stop bits, parity, and number of data bits 
    - Get line: Get the bit rate, number of Stop bits, parity, and number of data bits
   The other requests (send break, control line state) are not implemented.
   
@note 
This application uses UART as a communication interface. The UART instance and associated resources
(GPIO, NVIC) can be tailored in "usbd_cdc_interface.h" header file according to your hardware 
configuration. Moreover, this application can be customized to communicate with interfaces other than UART.
For that purpose a template CDC interface is provided in: 
Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src directory.

**To test the CDC part, the user can check device manager, the expected behavior to see to seperate serial com port **
   This is useful for test and performance measurements.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application needs to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
For more details about the STM32Cube USB Device library, please refer to UM1734 
"STM32Cube USB Device library".
      
@par Keywords

Connectivity, USB_Device, USB, High Speed, Joystick, Mouse, OTG, CDC, UART, USB-to-RS232, Bridge, VCP, Com port

@Note If the user code size exceeds the DTCM-RAM size or starts from internal cacheable memories (SRAM1 and SRAM2),that is shared between several processors,
      then it is highly recommended to enable the CPU cache and maintain its coherence at application level.
      The address and the size of cacheable buffers (shared between CPU and other masters)  must be properly updated to be aligned to cache line size (32 bytes).

@Note It is recommended to enable the cache and maintain its coherence, but depending on the use case
      It is also possible to configure the MPU as "Write through", to guarantee the write access coherence.
      In that case, the MPU must be configured as Cacheable/Bufferable/Not Shareable.
      Even though the user must manage the cache coherence for read accesses.
      Please refer to the AN4838 “Managing memory protection unit (MPU) in STM32 MCUs”
      Please refer to the AN4839 “Level 1 cache on STM32F7 Series”

@par Directory contents

  F767_DualCDC\Core\Src\main.c                  Main program
  F767_DualCDC\Core\Src\stm32f7xx_hal_msp.c     MSP Initialization file
  F767_DualCDC\Core_\Src\system_stm32f7xx.c     STM32F7xx system clock configuration file
  F767_DualCDC\Core\Src\stm32f7xx_it.c          Interrupt handlers
  F767_DualCDC\USB_DEVICE\App\usbd_desc.c       USB device CDC descriptor
  F767_DualCDC\USB_DEVICE\App\usbd_cdc_if.c     USB device CDC Interface for VCP
  F767_DualCDC\USB_DEVICE\App\usb_device.c      USB device CDC Intialization
  F767_DualCDC\USB_DEVICE\Target\usbd_conf.c    General low level driver configuration
  F767_DualCDC\Core\Inc\main.h                  Main program header file
  F767_DualCDC\Core\Inc\stm32f7xx_it.h          Interrupt handlers header file
  F767_DualCDC\Core\Inc\stm32f7xx_hal_conf.h    HAL configuration file
  F767_DualCDC\Core\Inc\usbd_conf.h             USB device driver Configuration file
  F767_DualCDC\USB_DEVICE\App\usbd_desc.c       USB device MSC descriptor header file
  F767_DualCDC\USB_DEVICE\App\usbd_cdc_if.c     USB device CDC Interface for VCP header file 
  F767_DualCDC\USB_DEVICE\App\usb_device.c      USB device CDC Intialization header file
  F767_DualCDC\USB_DEVICE\Target\usbd_conf.c    General low level driver configuration header file

  
@par Hardware and Software environment

  - This application runs on STM32F767xx devices.
  - This application has been tested with STMicroelectronics STM32F767-Nucleo board and can be easily tailored to any other supported device 
    and development board.
  - STM32F767-Nucleo set up
      - Connect the STM32746G-Discovery board to the PC through 'USB micro A-Male 
      to A-Male' cable to the connector:
            - CN3: to use USB Full Speed (FS)

@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - In the workspace toolbar select the project configuration:
 - Run the application
 - Install the USB virtual COM port driver
 - Find out the number of the COM ports assigned to the STM32 CDC device using device manager

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */