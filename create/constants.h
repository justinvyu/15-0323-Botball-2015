// Created on Tue February 17 2015

#define ARM_MOTOR 0

#pragma mark - Servos

#define GATE_SERVO 2
#define GATE_CLOSED 0
#define GATE_HALFOPEN 1024
#define GATE_OPEN 2047

#pragma mark - Sensors

#define ARM_STOP_TOUCH_SENSOR 15

#pragma mark - Shortcuts

#define ssp(serv, pos) set_servo_position(serv, pos)
