/*
 * fsm.c
 *
 *  Created on: Dec 8, 2022
 *      Author: Phạm Đình Văn
 */

#include "fsm.h"
#include "software_timer.h"
#include "fsm_buttons.h"
#include "global.h"
#include "display_trafficLed.h"

void fsm_run() {
	switch (status) {
	case AUTOMATIC:
		automatic_LED();
		break;
	case MANUAL:
		switchLED();
		status = AUTOMATIC;
		break;
	case TURNING:
		turningLED();
		status = AUTOMATIC;
	default:
		break;
	}
}

void fsm_pesRUN(){
	switch (status_1) {
	case NORMAL:
		pesLED_NORMAL();
		break;
	case ACTION:
		pesLED_ACTION();
		buz = 999;
		setTimer_buzzer(250);
		if(timer_pes_flag == 1) {
			status_1 = NORMAL;
		}
		break;
	default:
		break;
	}
}
