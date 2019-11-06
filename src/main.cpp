#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	int mtrPort = 1;
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::lcd::initialize();
	pros::Motor mtr(mtrPort);
	mtr.set_gearing(pros::E_MOTOR_GEARSET_36);
	mtr.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	mtr.set_encoder_units(pros::E_MOTOR_ENCODER_INVALID);

	while (true) {
		pros::lcd::print(0, "Velocity(RPM): %lf RPM", mtr.get_actual_velocity());
		pros::lcd::print(1, "Current(mA): %d mA", mtr.get_current_draw());
		pros::lcd::print(2, "Efficiency(): %ld",(long) mtr.get_efficiency());
		pros::lcd::print(3, "Power(W): %lf W", mtr.get_power());
		pros::lcd::print(4, "Temperature(C): %lf C", mtr.get_temperature());
		pros::lcd::print(5, "Torque(Nm): %lf Nm", mtr.get_torque());
		pros::lcd::print(6, "Voltage(mV): %ld mV", mtr.get_voltage());

		if (master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y))
			mtr.move(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
		else
			mtr.move_velocity((master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) - master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) * 100);

		pros::delay(250);
	}
}
