/*
 * display_led.c
 *
 *  Created on: Nov 2, 2022
 *      Author: Phạm Đình Văn
 */

#include "main.h"
#include "display_trafficLed.h"
#include "software_timer.h"
#include "global.h"
#include "buzzer.h"

uint16_t RED[2] = { tLight1_RED_Pin, tLight2_RED_Pin };
uint16_t GRE[2] = { tLight1_GRE_Pin, tLight2_GRE_Pin };

//time that one led can run
int LED_TIME[3] = { 5000, 3000, 2000 };

int currentState[2] = { 0, 1 };
int currentTimer[2] = { 0, 0 };

int currentPesState = 0;

void clear_tLight1() {
	HAL_GPIO_WritePin(tLight1_RED_GPIO_Port, tLight1_RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(tLight1_GRE_GPIO_Port, tLight1_GRE_Pin, GPIO_PIN_SET);
}
void clear_tLight2() {
	HAL_GPIO_WritePin(tLight2_RED_GPIO_Port, tLight2_RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(tLight2_GRE_GPIO_Port, tLight2_GRE_Pin, GPIO_PIN_SET);
}
void clear_pLight() {
	HAL_GPIO_WritePin(pLight_RED_GPIO_Port, pLight_RED_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(pLight_GRE_GPIO_Port, pLight_GRE_Pin, GPIO_PIN_SET);
}

void currentState_update(int index) {
	//0 for tLight1, 1 for tLight2
	currentTimer[index] = LED_TIME[currentState[index]];
	currentState[index] = currentState[index] + 1;
	if (currentState[index] >= 3)
		currentState[index] = 0;
}

void tLight1_processing() {
	clear_tLight1();
	switch (currentState[0]) {
	case RED_IDX:
		HAL_GPIO_WritePin( tLight1_RED_GPIO_Port, RED[0], GPIO_PIN_RESET);
//		HAL_GPIO_WritePin( tLight1_RED_GPIO_Port, GRE[0], GPIO_PIN_RESET);
		break;
	case GRE_IDX:
		HAL_GPIO_WritePin( tLight1_GRE_GPIO_Port, GRE[0], GPIO_PIN_RESET);
		break;
	case YEL_IDX:
//		HAL_GPIO_WritePin( tLight1_RED_GPIO_Port, RED[0], GPIO_PIN_SET);
//		HAL_GPIO_WritePin( tLight1_GREEN_GPIO_Port, GRE[0], GPIO_PIN_SET);
		break;
	}
}
void tLight2_processing() {
	clear_tLight2();
	switch (currentState[1]) {
	case GRE_IDX:
		HAL_GPIO_WritePin( tLight2_GRE_GPIO_Port, GRE[1], GPIO_PIN_RESET);
		break;
	case YEL_IDX:
//		HAL_GPIO_WritePin( tLight1_RED_GPIO_Port, RED[1], GPIO_PIN_SET);
//		HAL_GPIO_WritePin( tLight1_GREEN_GPIO_Port, GRE[1], GPIO_PIN_SET);
		break;
	case RED_IDX:
		HAL_GPIO_WritePin( tLight2_RED_GPIO_Port, RED[1], GPIO_PIN_RESET);
		break;
	}
}

void pLight_processing() {
	switch (currentPesState) {
	case GRE_IDX:
		HAL_GPIO_WritePin(pLight_GRE_GPIO_Port, pLight_GRE_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(pLight_RED_GPIO_Port, pLight_RED_Pin, GPIO_PIN_SET);
		break;
	case RED_IDX:  case YEL_IDX:
		HAL_GPIO_WritePin(pLight_RED_GPIO_Port, pLight_RED_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(pLight_GRE_GPIO_Port, pLight_GRE_Pin, GPIO_PIN_SET);
		break;

	}

}

void automatic_LED() {
	if (timer_tLight1_flag == 1) {
		tLight1_processing();
		currentState_update(0);
		setTimer_tLight1(currentTimer[0]); //setTimer for run
	}
	if (timer_tLight2_flag == 1) {
		tLight2_processing();
		currentState_update(1);
		setTimer_tLight2(currentTimer[1]);
	}
}

void switchLED() {
	if (currentState[0] - 1 == RED_IDX) {
		tLight2_processing();
		currentState_update(1);
		setTimer_tLight2(currentTimer[1]);

		if (currentState[1] - 1 == RED_IDX) {
			tLight1_processing();
			currentState_update(0);
			setTimer_tLight1(currentTimer[0]);
			return;
		}
		setTimer_tLight1(currentTimer[1]);
	} else if (currentState[1] - 1 == RED_IDX) {

		tLight1_processing();
		currentState_update(0);
		setTimer_tLight1(currentTimer[0]);
		if (currentState[0] - 1 == RED_IDX) {
			tLight2_processing();
			currentState_update(1);
			setTimer_tLight2(currentTimer[1]);
			return;
		}
		setTimer_tLight2(currentTimer[0]);
	}
}

void turningLED() {

	switch (currentState[0]) {
	case RED_IDX:
	case YEL_IDX: //RED
		LED_TIME[RED_IDX] = LED_TIME[RED_IDX] + (1 * 1000);
		break;
	case GRE_IDX:
		LED_TIME[GRE_IDX] = LED_TIME[GRE_IDX] + (1 * 1000);
		break;
	default:
		break;
	}
	switch (currentState[1]) {
	case RED_IDX:
	case YEL_IDX: //RED
		LED_TIME[RED_IDX] = LED_TIME[RED_IDX] + (1 * 1000);
		break;
	case GRE_IDX:
		LED_TIME[GRE_IDX] = LED_TIME[GRE_IDX] + (1 * 1000);
		break;
	default:
		break;
	}
	timer_tLight1_flag = 1;
	timer_tLight2_flag = 1;
	currentState[0]--;
	currentState[1]--;
}

void pesLED_NORMAL() {
	clear_pLight();
}
void pesLED_ACTION() {
	if (currentState[0] == GRE_IDX) {
		currentPesState = GRE_IDX;
		buzzer(buz);
		if(timer_buzzer_flag == 1) {
			buz/= 2;
		}
	} else if (currentState[0] == YEL_IDX) {
		currentPesState = RED_IDX;
	} else {
		currentPesState = YEL_IDX;
	}
	pLight_processing();
}
