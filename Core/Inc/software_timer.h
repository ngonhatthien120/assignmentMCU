/*
 * software_timer.h
 *
 *  Created on: Nov 1, 2022
 *      Author: Nhat Thien
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#define TIMER_CYCLE  10

extern int timer_tLight1_flag;
extern int timer_tLight2_flag;
extern int timer_pes_flag;
extern int timer_buzzer_flag;


void setTimer_tLight1(int duration);
void setTimer_tLight2(int duration);
void setTimer_PES(int duration);
void setTimer_buzzer(int duration);

void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
