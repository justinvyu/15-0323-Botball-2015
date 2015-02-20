// Created on Tue February 17 2015

// Replace FILE with your file's name
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#pragma mark - Motors

#define MOT_LEFT 3//Rek'sai edition!
#define MOT_RIGHT 1

#pragma mark - Servos

#define PROP_SERVO 0
#define PROP_FLAT 1024
#define PROP_UP 0
#define PROP_DOWN 2047

#define ARM_SERVO 1 
#define ARM_UP 2047
#define ARM_DOWN 0

#pragma mark - Shortcuts

#define ssp(serv, pos) set_servo_position(serv, pos)
#define forward_with_speed(m1, m2, time, speed) motor(m1,speed);motor(m2,speed);msleep(time)
#define back_with_speed(m1, m2, time, speed) motor(m1,-speed);motor(m2,-speed);msleep(time)
#define fd_with_time(m1, m2, time) fd(m1);fd(m2);msleep(time)
#define bk_with_time(m1, m2, time) bk(m1);bk(m2);msleep(time)

#pragma mark - Sensors

#define TOUCH_SENSOR_LEFT 15
#define TOUCH_SENSOR_RIGHT 16
#define ET 0

#endif