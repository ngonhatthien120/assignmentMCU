/*
 * button.c
 *
 *  Created on: Dec 8, 2022
 *      Author: Nhat Thien
 */

#include "button.h"
#include "main.h"
int buttonN_flag[MAX_BUTTONS] = { 0 };

//signal button pressed
int buttonN_PIN[MAX_BUTTONS] = { BTN_1_Pin, BTN_2_Pin, BTN_3_Pin, BTN_PES_Pin };

int KeyReg0[MAX_BUTTONS] = { NORMAL_STATE };
int KeyReg1[MAX_BUTTONS] = { NORMAL_STATE };
int KeyReg2[MAX_BUTTONS] = { NORMAL_STATE };
int KeyReg3[MAX_BUTTONS] = { NORMAL_STATE };

int TimerForKeyPress[MAX_BUTTONS] = { 100 };

int isButtonNPressed(int index) {
	if (buttonN_flag[index] == 1) {
		buttonN_flag[index] = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index) {
	buttonN_flag[index] = 1;
}
int readPin(int index) {
	switch (index) {
	case 0:
		return HAL_GPIO_ReadPin(BTN_1_GPIO_Port, BTN_1_Pin);
		break;
	case 1:
		return HAL_GPIO_ReadPin(BTN_2_GPIO_Port, BTN_2_Pin);
		break;
	case 2:
		return HAL_GPIO_ReadPin(BTN_3_GPIO_Port, BTN_3_Pin);
		break;
	case 3:
		return HAL_GPIO_ReadPin(BTN_PES_GPIO_Port, BTN_PES_Pin);
	default:
		break;
	}
	return 0;
}
void getKeyInput() {
	for (int i = 0; i < MAX_BUTTONS; i++) {
		KeyReg0[i] = KeyReg1[i];
		KeyReg1[i] = KeyReg2[i];
		KeyReg2[i] = readPin(i);
		if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
			if (KeyReg3[i] != KeyReg2[i]) {
				KeyReg3[i] = KeyReg2[i];
				if (KeyReg2[i] == PRESSED_STATE) {
					//TODO
					subKeyProcess(i);
					TimerForKeyPress[i] = 100;
				}
			} else {
				TimerForKeyPress[i]--;
				if (TimerForKeyPress[i] == 0) {
					//TODO
					KeyReg3[i] = NORMAL_STATE;
				}
			}
		}
	}
}
