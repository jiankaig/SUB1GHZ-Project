//https://software-dl.ti.com/simplelink/esd/simplelink_msp432e4_sdk/2.30.00.14/docs/driverlib/msp432e4/html/group__uart__api.html
//http://software-dl.ti.com/lprf/simplelink_cc2640r2_sdk/1.30.00.25/exports/docs/driverlib_cc13xx_cc26xx/cc26x0/driverlib/group__uart__api.html
#include "uart.h" //SerialCCXX uses this api

//https://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/06_01_01_12/exports/docs/pdk/docs/user_guide/html/group__DRV__UART__API__MODULE.html
//http://software-dl.ti.com/simplelink/esd/simplelink_cc13x0_sdk/4.10.01.01/exports/docs/tidrivers/doxygen/html/_u_a_r_t_8h.html
//https://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/07_00_00_11/exports/docs/pdk_jacinto_07_00_00/docs/userguide/modules/uart.html
//https://software-dl.ti.com/dsps/dsps_public_sw/sdo_sb/targetcontent/tirtos/2_20_00_06/exports/tirtos_full_2_20_00_06/products/tidrivers_full_2_20_00_08/docs/doxygen/html/_u_a_r_t_8h.html
#include <UART.h> //ccs examples use this api
//#include <UART_stdio.h>
//#include "Board.h" //for Board_UART0
#define Board_UART0 0 //CC1310_LAUNCHXL_UART0
#define BUFSIZE 128

void setup() {
  // put your setup code here, to run once:
  UARTEnable(UART0_BASE);
  UARTCharGetNonBlocking(UART0_BASE);

 
  // One-time initialization of UART driver
  UART_init();
  // Initialize UART parameters
  UART_Params params;
  UART_Params_init(&params);
  params.baudRate = 9600;
  params.readMode = UART_MODE_BLOCKING;
  params.writeMode = UART_MODE_BLOCKING;
  params.readTimeout = UART_WAIT_FOREVER;
  params.writeTimeout = UART_WAIT_FOREVER;
  // Open the UART
  UART_Handle uart;
  uart = UART_open(Board_UART0, &params);
  // Read from the UART
  int32_t readCount;
  uint8_t buffer[BUFSIZE];
  readCount = UART_read(uart, buffer, BUFSIZE);
  // Write to the UART
  UART_write(uart, buffer, BUFSIZE);
  // Close the UART
  UART_close(uart);
}

void loop() {
  // put your main code here, to run repeatedly: 
  if(UARTBusy(UART0_BASE))
    Serial.print("busy");
}
