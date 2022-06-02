#include <xmc_gpio.h>
#define TICKS_WAIT 1

#define LED1 P1_1
#define LED2 P1_0


// NOTES: I took the main systick timer code from https://www.keil.com/pack/doc/cmsis/Core/html/group__SysTick__gr.html


uint32_t counterTMS = 40;                                                        /* Variable to store millisecond ticks */
int letterCounter=0;

//Interrupt handler

void SysTick_Handler(void)  {     
  //XMC_GPIO_ToggleOutput(LED1);                           
  counterTMS++;                       
  if (counterTMS>=50){
    
    letterCounter++;
  }                         
}
  
int main (void)  {
  uint32_t returnCode;
  //7 0,0,0,0,0,0,0,
  //3 0,0,0,
  uint8_t signalArray[95]={ 0,
                            1,0,1, // I
                            0,0,0,0,0,0,0,
                            1,1,1,0,1,0,1,1,1,0,1,
                            0,0,0,
                            1,0,1,1,1,
                            0,0,0,
                            1,1,1,0,1,
                            0,0,0,0,0,0,0,
                            1,1,1,0,1,1,1,
                            0,0,0,
                            1,1,1,0,1,1,1,0,1,1,1,
                            0,0,0,
                            1,0,1,1,1,0,1,
                            0,0,0,
                            1,0,1,0,1,
                            0,0,0,
                            1,
                            3};
// GPIO CONFIG
  XMC_GPIO_CONFIG_t config;
  config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
  config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;
  XMC_GPIO_Init(LED1, &config);
  config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
  XMC_GPIO_Init(LED2, &config);
  

  returnCode = SysTick_Config(SystemCoreClock / 10);      /* Configure SysTick to generate an interrupt every 100 milliseconds */
  
  if (returnCode != 0)  {                                   /* Check return code for errors */
    // Error Handling 
  }
  
  for(;;){
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
      break;
    }

  }
}
