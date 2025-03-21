
#include <Arduino.h>
#ifndef ENCODER_H
#define ENCODER_H

#define ENCODER_DT 20
#define ENCODER_CLK 21
#define ENCODER_SW 19

/* 
 * Initialize pins for encoder
 */
void encoder_setup();

/*
 * Check encoder direction and return it
 */
int encoder_update(int * ret_val, int * click);

#endif