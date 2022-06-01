#include <xmc_gpio.h>
#define TICKS_WAIT 1

#define LED1 P1_1
#define LED2 P1_0

#define GPIO_BUTTON1  XMC_GPIO_PORT1, 14
#define GPIO_BUTTON2  XMC_GPIO_PORT1, 15

// NOTES: I took the main systick timer code from https://www.keil.com/pack/doc/cmsis/Core/html/group__SysTick__gr.html


uint32_t counterTMS = 0;                                                        /* Variable to store millisecond ticks */
int letterCounter=0;
bool btnOPressedFlag=false;
bool btnTPressedFlag=false;
bool timeBufferFlag=true; //originally set to true
uint32_t timeBuffer=0; //Initialised to 0 so that if Button 1 is not yet pressed 0 is transmitted per Morse

//Interrupt handler

void SysTick_Handler(void)  {     
  //XMC_GPIO_ToggleOutput(LED1);                           
  counterTMS++;       
    if(counterTMS%100==0){
        if (btnOPressedFlag){
            if (letterCounter==0){
                letterCounter=1;}
            else {    
            letterCounter++;}
        } 
    }
}
  
int main (void)  {
  uint32_t returnCode;
  //7 0,0,0,0,0,0,0,
  //3 0,0,0,
  uint8_t signalArray[95]={ 0, //INITIAL CONDITION
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
  
    const XMC_GPIO_CONFIG_t in_config = \
      {.mode=XMC_GPIO_MODE_INPUT_TRISTATE,\
       .output_level=XMC_GPIO_OUTPUT_LEVEL_LOW,\
       .output_strength=XMC_GPIO_OUTPUT_STRENGTH_STRONG_SHARP_EDGE};
  XMC_GPIO_Init(GPIO_BUTTON1,  &in_config);
  XMC_GPIO_Init(GPIO_BUTTON2,  &in_config);


  returnCode = SysTick_Config(SystemCoreClock / 1000);      /* Configure SysTick to generate an interrupt every 100 milliseconds */
  
  if (returnCode != 0)  {                                   /* Check return code for errors */
    // Error Handling 
  }
  
  
  for(;;){
      
   // The mechanism for the button locking is utilized through the flags btnTPressedFlag and btnOPressedFlag   
      
    if(XMC_GPIO_GetInput(GPIO_BUTTON1) == 0) { 
            if (!btnTPressedFlag){
                    btnOPressedFlag=true;
                                }
                                                }
    if(XMC_GPIO_GetInput(GPIO_BUTTON2) == 0) { 
                                             if(!btnOPressedFlag){
                                                 btnTPressedFlag=true;
                                                                }
                                            }  
   
   // Btn 1 Functionality
   //
   if (btnOPressedFlag){
       if (timeBufferFlag){
       timeBuffer = counterTMS;
       counterTMS=0;
       timeBufferFlag=false;    
                            }
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
            btnOPressedFlag=false;
            timeBufferFlag=true;
            break;
        }
   }else {XMC_GPIO_SetOutputLow(LED1);}
  }
}
