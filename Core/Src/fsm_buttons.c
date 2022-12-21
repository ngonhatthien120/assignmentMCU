/*
 * fms_buttons.c
 *
 *  Created on: Dec 8, 2022
 *      Author: Dattt
 */

#include "fsm_buttons.h"
#include "button.h"
#include"software_timer.h"
#include "global.h"
#include "display_trafficLed.h"

void fsm_simple_buttons_run (){
	//AUTOMATIC
	if (isButtonNPressed(0) == 1) {
		status = AUTOMATIC;
	}
	//MANUAL
	if (isButtonNPressed(1) == 1) {
		status = MANUAL;
	}
	//TURNING
	if (isButtonNPressed(2) == 1) {
		status = TURNING;

	}
	if (isButtonNPressed(3) == 1) {
		setTimer_PES(5000);
		status_1 = ACTION;
	}

}
