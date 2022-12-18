/*
 * display_trafficLed.h
 *
 *  Created on: Dec 8, 2022
 *      Author: Phạm Đình Văn
 */
#include "button.h"
#ifndef INC_DISPLAY_TRAFFICLED_H_
#define INC_DISPLAY_TRAFFICLED_H_

#define RED_IDX 0
#define GRE_IDX 1
#define YEL_IDX 2

extern int LED_TIME[3];

void automatic_LED();
void switchLED();
void turningLED();

void pesLED_NORMAL();
void pesLED_ACTION();

#endif /* INC_DISPLAY_TRAFFICLED_H_ */
