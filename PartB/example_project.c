#include <xmc_gpio.h>
#define TICKS_WAIT 1

#define LED1 P1_1
#define LED2 P1_0

#define GPIO_BUTTON1  XMC_GPIO_PORT1, 14
#define GPIO_BUTTON2  XMC_GPIO_PORT1, 15

// NOTES: I took the main systick timer code from https://www.keil.com/pack/doc/cmsis/Core/html/group__SysTick__gr.html

int recordedTimeArray[10]={0,12,12,12,12,12,12,12,12,12};
int morseNumber[800] ={3};
uint32_t counterTMS = 0;                                                        /* Variable to store millisecond ticks */
int letterCounter=0;
bool btnOPressedFlag=false;
bool btnTPressedFlag=false;
bool timeBufferFlag=true; //originally set to true
uint32_t timeBuffer=0; //Initialised to 0 so that if Button 1 is not yet pressed 0 is transmitted per Morse

//Interrupt handler


// DECIMAL TO ARRAY CODE TAKEN FROM STACK OVERFLOW https://stackoverflow.com/questions/515612/convert-an-integer-number-into-an-array
void DecimalToArrayFunction(int recordedTimeArray[], uint32_t timeBuffer)
{  
        int c = 0; /* digit position */
        int n = timeBuffer;
        //recordedTimeArray[]={999,999,999,999,999,999,999,999,999,999};              
        while (n != 0)
        {
            n /= 10;
            c++;
        }
       
        int numberArray[c];
       
        c = 0;    
        n = timeBuffer;
       
        /* extract each digit */
        while (n != 0)
        {
            numberArray[c] = n % 10;
            n /= 10;
            c++;
        }
        int intracounter=0;
        for (int i=c-1;i>=0;i--){            
            //printf("%d \n",numberArray[i]);
                recordedTimeArray[intracounter]=numberArray[i];
                intracounter++;
        }
        intracounter=0;

}
void ArrayToMorse(int ArrayInput[], int ArrayOutput[]){
    bool encodingFlag = false;
    int counterIndex=0;
    int outputCounterIndex=0;
    while (!encodingFlag){
       
        switch (ArrayInput[counterIndex])
        {
            case 0:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 counterIndex++;
                break;
            case 1:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 counterIndex++;
                break;
            case 2:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 counterIndex++;
                break;
            case 3:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 
                counterIndex++;
                break;
            case 4:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                counterIndex++;
                break;
            case 5:
                ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 counterIndex++;
                break;
            case 6:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                counterIndex++;
                break;
            case 7:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
               
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
               
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                counterIndex++;
                break;
            case 8:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
               
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
               
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                counterIndex++;
                break;
            case 9:
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
               
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
               
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=1;
                 outputCounterIndex++;
                 
                 ArrayOutput[outputCounterIndex]=0;
                 outputCounterIndex++;
                counterIndex++;
                break;
               
            case 12:
                ArrayOutput[outputCounterIndex]=3;
                //ArrayInput[1,2,3,4,5,6,7,8,9,10]=999,999,999,999,999,999,999,999,999,999;
                encodingFlag=true;
                break;
        }
       
       
    }
   
}
void SysTick_Handler(void)  {    
  //XMC_GPIO_ToggleOutput(LED1);                          
  counterTMS++;      
    if(counterTMS%100==0){
        if (btnOPressedFlag || btnTPressedFlag){
            if (letterCounter==0){
                letterCounter=1;}
            else {    
            letterCounter++;}
        }
    }
}

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
                           
                           
int main (void)  {
  uint32_t returnCode;
  //7 0,0,0,0,0,0,0,
  //3 0,0,0,

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
  XMC_GPIO_SetOutputLow(LED1);
 
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
                                                 DecimalToArrayFunction(recordedTimeArray,timeBuffer);
                                                 ArrayToMorse(recordedTimeArray,morseNumber);
                                                                }
                                            }  
   
   // Btn 1 Functionality
   //
   if (btnTPressedFlag){

    switch (morseNumber[letterCounter])
        {
            case 1:
            XMC_GPIO_SetOutputHigh(LED1);
            break;
            case 0:
            XMC_GPIO_SetOutputLow(LED1);
            break;
            case 3:  
            letterCounter=0;            
            counterTMS=0;
            btnTPressedFlag=false;
            timeBufferFlag=true;
            for (int i=0;i<=9;i++){
                if(i==0){recordedTimeArray[i]=0;}else{
            recordedTimeArray[i]=12;}
                
            }
            XMC_GPIO_SetOutputLow(LED1);
            break;
        }
   }
   
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
            XMC_GPIO_SetOutputLow(LED1);
            break;
        }
   }//else {XMC_GPIO_SetOutputLow(LED1);}
  }
}
