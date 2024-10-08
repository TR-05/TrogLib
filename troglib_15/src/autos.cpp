#include "drive_movement/auto_funcs.h"
#include "motor_controller.h"
#include "sensor_data.h"
#include "vex.h"
#include <iostream>

float ykp = .7, yki = 0.0, ykd = 6;
float hkp = .28, hki = .01, hkd = 3;

void test_auto()
{
    start_auto(0, 0, 0);

    straight(24, ykp, yki, ykd, 12, .125, 1);
    delay(300);
    straight_with_heading(-24, 0, ykp, yki, ykd, hkp, hkd, 12, 12, .125, 1);
    classic_move_to(-20, 30, 9, 12, ykp, hkp * .6, .125, 2, false);
    delay(300);
    // turn_to_xy(0,0, hkp, hki, hkd, 6, 1, false);
    // delay(300);
    classic_move_to(0, 0, 9, 12, ykp, hkp, .125, 2, true);
    delay(500);
    turn_to(0, hkp, hki, hkd, 9, 1);

    // straight(-24, ykp, yki, ykd, 12, .15, 1);
    // straight_with_heading(-24, -90, ykp, yki, ykd, hkp, hkd, 12, 12, .125, 1);

    /*
        turn_to(90, hkp, hki, hkd, 12, 1);
        turn_to(0, hkp, hki, hkd, 12, 1);
        turn_to_xy(-45, 45, hkp, hki, hkd, 12, 1, false);
        turn_to_xy(-45, 45, hkp, hki, hkd, 12, 1, true);
        turn_to(0, hkp, hki, hkd, 12, 1);
    */
    stop_auto();
}

void prog_skills_15()
{
    start_auto(0, 0, 0);
    ykp = .7, yki = 0.0, ykd = 6;
    hkp = .28, hki = .01, hkd = 3;
    straight_with_heading(-50, -2, ykp, yki, ykd, hkp, hkd, 10, 12, .125, 3);
    swing_on_right(-115, hkp * 1.2, hki, hkd, 12, 8);
    classic_move_to(85, -34, 8, 12, ykp, hkp * 1.5, .125, 4, true);
    turn_to_xy(72, -51, hkp, hki, hkd, 12, 3, false);
    delay(500);
    classic_move_to(72, -51, 4, 12, ykp, hkp * 1.5, .125, 4, false);
    delay(500);
    turn_to(-151, hkp, hki, hkd, 5, 3);
    straight_with_heading(6, -151, ykp, yki, ykd, hkp, hkd, 2.5, 12, .125, 0);
    delay(1000);
    intake_at(-12, 0, 1);
    turn_to(-151, hkp, hki, hkd, 5, 3);
    delay(10000);

    // classic_move_to(0, -50, 9, 12, ykp, hkp * .6, .125, 2, true);
    stop_auto();
}