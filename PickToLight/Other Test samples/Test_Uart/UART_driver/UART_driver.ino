char        input;
UART_Handle uart;
UART_Params uartParams;


void setup() {
  // Initialize the UART driver.
  UART_init();
  // Create a UART with data processing off.
  UART_Params_init(&uartParams);
  uartParams.writeDataMode = UART_DATA_BINARY;
  uartParams.readDataMode = UART_DATA_BINARY;
  uartParams.readReturnMode = UART_RETURN_FULL;
  uartParams.readEcho = UART_ECHO_OFF;
  uartParams.baudRate = 9600;
  // Open an instance of the UART drivers
  uart = UART_open(Board_UART0, &uartParams);
  if (uart == NULL) {
      // UART_open() failed
      while (1);
  }
}

void loop() {
  // Loop forever echoing 
  UART_read(uart, &input, 1);
  UART_write(uart, &input, 1);
  
}
