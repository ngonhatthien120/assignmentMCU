/*
 * button.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Nhat Thien
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"
//#include "global.h"

#define NORMAL_STATE GPIO_PIN_SET
#define PRESSED_STATE GPIO_PIN_RESET

#define MAX_BUTTONS 4

extern int TimerForKeyPress[MAX_BUTTONS];
extern int isButtonNPressed(int index);

void getKeyInput();

#endif /* INC_BUTTON_H_ */
