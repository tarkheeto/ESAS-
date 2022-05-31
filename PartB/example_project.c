#include <xmc_gpio.h>
#include <stdio.h>
#include <xmc_uart.h>
#define UART_TX P1_5
#define UART_RX P1_4
XMC_UART_CH_CONFIG_t uart_config =
{
  .data_bits = 8U,
  .stop_bits = 1U,
  .baudrate = 115200U
};


#define TICKS_WAIT 1

#define LED1 P1_1
#define LED2 P1_0
#define GPIO_BUTTON1  XMC_GPIO_PORT1, 14
#define GPIO_BUTTON2  XMC_GPIO_PORT1, 15

// NOTES: I took the main systick timer code from https://www.keil.com/pack/doc/cmsis/Core/html/group__SysTick__gr.html


uint32_t counterTMS = 0;                                                        /* Variable to store millisecond ticks */
int letterCounter=0;
bool btnPressedFlag=false;
bool firstRunFlag=false;
uint32_t timeBuffer=0;
uint32_t timeBtn1Buffer=0;
//Interrupt handler

void SysTick_Handler(void)  {     
  //XMC_GPIO_ToggleOutput(LED1);                           
  counterTMS++;   
  if (counterTMS%100==0){
        if (btnPressedFlag){
            if (letterCounter==0){
                letterCounter=1;}
            else {    
            letterCounter++;}
        }          
    }
}
  
void XMC_AssertHandler(const char *const msg, const char *const file, uint32_t line)
{
  printf("%s at line %u of %s\n", msg, (unsigned int)line, file);
  while(1);
}


int main (void)  {
    
  uint32_t returnCode;
  //7 0,0,0,0,0,0,0,
  //3 0,0,0,
  
  uint8_t signalArray[95]={ 0, //INITIAL CONDITION
                            1,0,1, // I
                            0,0,0,0,0,0,0, //space
                            1,1,1,0,1,0,1,1,1,0,1, //C
                            0,0,0,// 
                            1,0,1,1,1, //A
                            0,0,0,//
                            1,1,1,0,1,//N
                            0,0,0,0,0,0,0,//space
                            1,1,1,0,1,1,1,// M
                            0,0,0,// 
                            1,1,1,0,1,1,1,0,1,1,1,// O
                            0,0,0,// 
                            1,0,1,1,1,0,1,//R
                            0,0,0,// 
                            1,0,1,0,1,// S
                            0,0,0,// 
                            1,//E
                            3 //End signal
                            };
                            
                            
  XMC_UART_CH_Init(XMC_UART0_CH0, &uart_config);

  XMC_GPIO_SetMode(UART_RX, XMC_GPIO_MODE_INPUT_TRISTATE);
  XMC_UART_CH_SetInputSource(XMC_UART0_CH0, XMC_UART_CH_INPUT_RXD, USIC0_C0_DX0_P1_4);

  XMC_UART_CH_Start(XMC_UART0_CH0);
  
  
// GPIO CONFIG
  XMC_GPIO_CONFIG_t config;
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
  XMC_GPIO_Init(LED1, &config);
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  XMC_GPIO_Init(LED2, &config);
  
  const XMC_GPIO_CONFIG_t in_config = \
      {.mode=XMC_GPIO_MODE_INPUT_TRISTATE,\
       .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
       .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};
  XMC_GPIO_Init(GPIO_BUTTON1,  &in_config);
  XMC_GPIO_Init(GPIO_BUTTON2,  &in_config);

  returnCode = SysTick_Config(SystemCoreClock / 1000);      /* Configure SysTick to generate an interrupt every 1 milliseconds */
  
  if (returnCode != 0)  {                                   /* Check return code for errors */
    // Error Handling 
  }
  
  for(;;){
    if(XMC_GPIO_GetInput(GPIO_BUTTON1) == 0) { btnPressedFlag=true;}
    if(XMC_GPIO_GetInput(GPIO_BUTTON2) == 0) { 
                                               printf("Manga"); 
                                            }
        
        
        
        
    if (btnPressedFlag){
   
    timeBtn1Buffer=counterTMS;
    counterTMS=0;
    
    switch (signalArray[letterCounter])
    {
    case 1:
      XMC_GPIO_SetOutputHigh(LED1);
      break;
    case 0:
      XMC_GPIO_SetOutputLow(LED1);
      break;
    case 3:
//         
      letterCounter=0;
      counterTMS=0;
      btnPressedFlag=false;
      break;
    }
  }else{XMC_GPIO_SetOutputLow(LED1);}
  }
}
