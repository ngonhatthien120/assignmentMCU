/*
 * software_timer.c
 *
 *  Created on: Nov 1, 2022
 *      Author: Nhat Thien
 */

#include "software_timer.h"
#include "global.h"

int timer_tLight1_counter = 0;
int timer_tLight1_flag = 0;

int timer_tLight2_counter = 0;
int timer_tLight2_flag = 0;

int timer_pes_counter = 0;
int timer_pes_flag = 0;

int timer_buzzer_counter = 0;
int timer_buzzer_flag = 0;

void setTimer_tLight1(int duration) {
	timer_tLight1_counter = duration/TIMER_CYCLE;
	timer_tLight1_flag = 0;
}
void setTimer_tLight2(int duration) {
	timer_tLight2_counter = duration/TIMER_CYCLE;
	timer_tLight2_flag = 0;
}
void setTimer_PES(int duration) {
	timer_pes_counter = duration/TIMER_CYCLE;
	ADD = timer_pes_counter/100;
	timer_pes_flag = 0;
}
void setTimer_buzzer(int duration) {
	timer_buzzer_counter = duration/TIMER_CYCLE;
	timer_buzzer_flag = 0;
}

void timerRun() {
	if (timer_tLight1_counter > 0) {
		TIME = timer_tLight1_counter;
		timer_tLight1_counter--;
		if (timer_tLight1_counter <= 0) {
			timer_tLight1_flag = 1;
		}
	}
	if (timer_tLight2_counter > 0) {
		timer_tLight2_counter--;
		if (timer_tLight2_counter <= 0) {
			timer_tLight2_flag = 1;
		}
	}
	if (timer_pes_counter > 0) {
			timer_pes_counter--;
			if (timer_pes_counter <= 0) {
				timer_pes_flag = 1;
			}
	}
	if (timer_buzzer_counter > 0) {
		timer_buzzer_counter--;
		if (timer_buzzer_counter <= 0) {
			timer_buzzer_flag = 1;
		}
}
}

