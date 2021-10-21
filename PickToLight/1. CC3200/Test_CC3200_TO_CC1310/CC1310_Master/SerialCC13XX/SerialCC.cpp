#include "SerialCC.h"
#include "uart.h"
#include "ioc.h"
#include "prcm.h"

void SerialCC::Begin(long baud) {

  PRCMPowerDomainOn(PRCM_DOMAIN_SERIAL);
  while (PRCMPowerDomainStatus(PRCM_DOMAIN_SERIAL) != PRCM_DOMAIN_POWER_ON) ;
  PRCMPowerDomainOn(PRCM_DOMAIN_PERIPH);
  while (PRCMPowerDomainStatus(PRCM_DOMAIN_PERIPH) != PRCM_DOMAIN_POWER_ON) ;

  PRCMPeripheralRunEnable(PRCM_PERIPH_UART0);
  PRCMLoadSet();
  // configure UART0
  IOCPortConfigureSet(IOID_3, IOC_PORT_MCU_UART0_TX, 0);
  IOCPortConfigureSet(IOID_2, IOC_PORT_MCU_UART0_RX, IOC_INPUT_ENABLE);

  UARTConfigSetExpClk(UART0_BASE, 48000000, baud, (UART_CONFIG_WLEN_8 |
                      UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
  UARTEnable(UART0_BASE);

}

int SerialCC::Print(String str) {

  char buffer[1000];
  long strLength = str.length() + 1;

  if (str.length() > 999)return -1;

  str.toCharArray(buffer, strLength, 0);

  for (long index = 0; index < strLength; index++)UARTCharPut(UART0_BASE, buffer[index]);

  return 0;

}



int SerialCC::Println(String str) {


  char buffer[1000];
  long strLength = str.length() + 1;

  if (str.length() > 999)return -1;

  str.toCharArray(buffer, strLength, 0);

  for (long index = 0; index < strLength; index++)UARTCharPut(UART0_BASE, buffer[index]);
  UARTCharPut(UART0_BASE, '\r');
  UARTCharPut(UART0_BASE, '\n');
  return 0;

}



int SerialCC::Read() {


  if (UARTCharsAvail(UART0_BASE)) {

    return (int)UARTCharGet(UART0_BASE);

  } else return 0;



}

