#include "vex.h"
#include "motor_controller.h"
#include "drive_movement/user_control.h"
#include "data_output/brain_screen.h"
#include "data_output/wireless_terminal.h"
#include "sensor_data.h"
#include "drive_movement/pid.h"
#include "drive_movement/auto_movement_loop.h"
#include "autos.h"
#include "drive_movement/sweeper.h"
#include "drive_movement/motion_profile.h"
#include "drive_movement/velo_controller.h"
#include "drive_movement/pathing/bezier_curves.h"
#include "drive_movement/pathing/pps.h"

using namespace vex;
brain Brain;
controller Controller;
competition Competition;

motor ls_front = motor(PORT8, ratio6_1, true);
motor ls_back = motor(PORT10, ratio6_1, true);
motor rs_front = motor(PORT18, ratio6_1, false);
motor rs_back = motor(PORT19, ratio6_1, false);

motor_group left_drive_motors = motor_group(ls_front, ls_back);
motor_group right_drive_motors = motor_group(rs_front, rs_back);
inertial IMU1 = inertial(PORT1);
encoder TY = encoder(Brain.ThreeWirePort.E);
encoder TX = encoder(Brain.ThreeWirePort.G);

extern task motor_control;

data bot(
    // horizontal tracking wheel offset (positive for back of robot)
    0.0586285,

    // vertical tracking wheel offset (positive for right side of robot)
    -0.0164235,

    // IMU multiplier
    1.011868,

    // Toggle using tracking wheels
    true

);

PID sweeper_pid(.1, 0, 0);
sweeper_class sweep;
PID drive_pid(0, 0, 0);
PID turn_pid(0, 0, 0);
MP_move mp_calc;
line_intersection get_line;
velo_controller left_side_drive(0.17, 0.025, 0.025, 0); // 0.02 ka 0.03 kd
velo_controller right_side_drive(0.17, 0.025, 0.025, 0);
int odometry_thread_wrapper()
{
  bot.odom_thread();
  return 0;
}
void pre_auton(void)
{
  IMU1.calibrate();
  task motor_control(motor_thread);
  task brain_screen(brain_readout_thread);
  task terminal(wireless_readout_thread);
  task odometry(odometry_thread_wrapper);
  bot.reset_sensors();
  bot.setPos(0, 0, 0);
}

void autonomous(void)
{
  enable_user_control = false;
  test_auto();
  // prog_skills_15();
}

void usercontrol(void)
{
  enable_auto_movement = false;
  drive_controllers(1, 1);
  if (bot.use_tracking_wheels)
    intake_controller(1);
  sweeper_controller(0);

  //wireless_terminal_on = false;
  //print_cubic(0,0, 0,20, 40,20, 40, 40, 20);
  //get_line.searchForIntersect(30);
  //printf("(%.2f,%.2f),", get_line.goal_x, get_line.goal_y);

  if (Controller.ButtonLeft.pressing())
    wait(2400, vex::msec), autonomous();
  while (1)
  {
    enable_user_control = true;
    user_drive_control();
    wait(10, msec);
  }
}

int main()
{
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true)
  {
    wait(100, msec);
  }
}
