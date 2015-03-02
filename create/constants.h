// Created on Tue February 17 2015

// Replace FILE with your file's name
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#pragma mark - Motors

#define ARM_MOTOR 0

#pragma mark - Servos

#define GATE_SERVO 2
#define GATE_CLOSED 1120
#define GATE_OPEN 2047

#pragma mark - Sensors

#define ARM_STOP_TOUCH_SENSOR 15

#pragma mark - Shortcuts

#define ssp(serv, pos) set_servo_position(serv, pos)

#endif
