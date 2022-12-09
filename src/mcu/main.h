// main.h
// Miles Cook & Penny Hernandez
// mdcook@g.hmc.edu
// 12/8/2022

#ifndef MAIN_H
#define MAIN_H

#include "STM32L432KC.h"
#include <stm32l432xx.h>

///////////////////////////////////////////////////////////////////////////////
// Custom defines
///////////////////////////////////////////////////////////////////////////////
// Motor Pins 
#define XA PA2
#define XB PA7
#define XC PA6
#define XD PA5

#define YA PA4
#define YB PA3
#define YC PA1
#define YD PA0 

#define ZA PA12
#define ZB PB3
#define ZC PB5
#define ZD PB0

// Joystick control
#define JN PB1
#define JW PA8
#define JS PB4
#define JE PA9

// Button Control
#define start_button PB7
#define end_button PA10

// Done Control
#define done_control PA11 //High is going, low is done 

// Delay 
#define DELAY_TIM TIM2

void move_E() {
    digitalWrite(XA, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(XA, 0);
    digitalWrite(XC, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(XC, 0);
    digitalWrite(XB, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(XB, 0);
    digitalWrite(XD, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(XD, 0);
}

void move_W() {
    digitalWrite(XD, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(XD, 1);
    digitalWrite(XB, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(XB, 1);
    digitalWrite(XC, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(XC, 1);
    digitalWrite(XA, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(XA, 1);
}

void move_S() {
    digitalWrite(YA, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(YA, 0);
    digitalWrite(YC, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(YC, 0);
    digitalWrite(YB, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(YB, 0);
    digitalWrite(YD, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(YD, 0);
}

void move_N() {
    digitalWrite(YD, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(YD, 1);
    digitalWrite(YB, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(YB, 1);
    digitalWrite(YC, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(YC, 1);
    digitalWrite(YA, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(YA, 1);
}

void move_Z_Down() {
    digitalWrite(ZD, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(ZD, 1);
    digitalWrite(ZB, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(ZB, 1);
    digitalWrite(ZC, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(ZC, 1);
    digitalWrite(ZA, 0);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(ZA, 1);
}

void move_Z_Up() {
    digitalWrite(ZA, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(ZA, 0);
    digitalWrite(ZC, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(ZC, 0);
    digitalWrite(ZB, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(ZB, 0);
    digitalWrite(ZD, 1);
    delay_millis(DELAY_TIM, 2);
    digitalWrite(ZD, 0);
}


#endif // MAIN_H