// stepper_control.c
// Miles Cook
// mdcook@g.hmc.edu
// 11/17/2022
// Controls stepper motors given input 

#include "main.h"

int main(void) {
    //****** Enable Motor as Output ******// 
    // GPIO Enable
    gpioEnable(GPIO_PORT_A);
    gpioEnable(GPIO_PORT_B);

    // X direction
    pinMode(XA, GPIO_OUTPUT);
    pinMode(XB, GPIO_OUTPUT);
    pinMode(XC, GPIO_OUTPUT);
    pinMode(XD, GPIO_OUTPUT);
   
    // Y direction
    pinMode(YA, GPIO_OUTPUT);
    pinMode(YB, GPIO_OUTPUT);
    pinMode(YC, GPIO_OUTPUT);
    pinMode(YD, GPIO_OUTPUT);

    // Z direction
    pinMode(ZA, GPIO_OUTPUT);
    pinMode(ZB, GPIO_OUTPUT);
    pinMode(ZC, GPIO_OUTPUT);
    pinMode(ZD, GPIO_OUTPUT);

    //****** Enable Joystick as Input ******// 
    pinMode(JN, GPIO_INPUT);
    pinMode(JW, GPIO_INPUT);
    pinMode(JS, GPIO_INPUT);
    pinMode(JE, GPIO_INPUT);

    GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD9, 0b01);  // Set PA9 as pull up
    GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD8, 0b01);  
    GPIOB->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD4, 0b01);  // Set PA9 as pull up
    GPIOB->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD1, 0b01);  
    
    ////****** Enable Buttons as Input ******// 
    pinMode(start_button, GPIO_INPUT);  
    pinMode(end_button, GPIO_INPUT);  

    GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD11, 0b01);  
    GPIOA->PUPDR |= _VAL2FLD(GPIO_PUPDR_PUPD10, 0b01);  // Pull both high

    // Control Pin
    pinMode(done_control, GPIO_OUTPUT);
    
    // Initialize timer
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    initTIM(DELAY_TIM);

    // Set parameters for input 
    int x_location = 0;
    int y_location = 0;
    int z_threshold = 1000;
    int z_current = 500;
    int time = 80000;

    // Starting State
    while(digitalRead(end_button)) {
      delay_millis(DELAY_TIM, 10);
    };

    // Tell FPGA to start counting 
    digitalWrite(done_control, 1);
    
    // Wait before entering 
    while(!digitalRead(end_button)){
        delay_millis(DELAY_TIM, 10);
    };

    // Delay for increment 
    delay_millis(DELAY_TIM, 6000);

    // Playing the game 
    while(digitalRead(end_button) && time > 0) { // Finishes when either time runs out or button is pressed
      if(!digitalRead(JE)) {  // Read the joystick input
        move_S();
        y_location--;
      }

      else if(!digitalRead(JW)) {
        move_N();
        y_location++;
        y_location++;
      }
      
      else if(!digitalRead(JS)) {
        move_W();
        x_location--;      
      }

      else if(!digitalRead(JN)) {
        move_E();
        x_location++;      
      }
      
      time--;
    }

    // Deassert game pin 
    digitalWrite(done_control, 0);
    
    // Drop the claw + Bring Back up
    for (int i = 0; i < 500; ++i) {
      move_Z_Up();
      delay_millis(DELAY_TIM, 10);
    }

    delay_millis(DELAY_TIM, 1);
    
    for (int i = 0; i < 500; ++i) {
      move_Z_Down();
      delay_millis(DELAY_TIM, 10);
    }
    // Returning the claw - This did not consistently work, but the methodology for its 
    // functionality is described here
    while(x_location > 0) {
        move_W();
        x_location--;
    }

    while(y_location > 0) {
        move_S();
        y_location--;
    }

}            


