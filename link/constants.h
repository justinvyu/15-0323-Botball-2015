// Created on Tue February 17 2015

// Replace FILE with your file's name
#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#pragma mark - Servos

#define PROP_SERVO 1
#define PROP_UP 1000
#define PROP_DOWN 1900

#define ARM_SERVO 2
#define ARM_UP 2047
#define ARM_DOWN 0

#pragma mark - Shortcuts

#define ssp(serv, pos) set_servo_position(serv, pos)
#define forward_with_speed(m1, m2, time, speed) motor(m1,speed);motor(m2,speed);msleep(time)
#define back_with_speed(m1, m2, time, speed) motor(m1,-speed);motor(m2,-speed);msleep(time)
#define fd_with_time(m1, m2, time) fd(m1);fd(m2);msleep(time)
#define bk_with_time(m1, m2, time) bk(m1);bk(m2);msleep(time)

#define f_with_speed(time, speed) motor(MOT_LEFT, speed);motor(MOT_RIGHT, speed);msleep(time)

#pragma mark - Sensors

#define TOUCH_SENSOR_LEFT 14
#define TOUCH_SENSOR_RIGHT 13

#define ET 0
#define ET_TURN 1

#define ET_THRESHOLD_RIGHT 280 
#define ET_THRESHOLD_FRONT 370

#define TOP_HAT_LEFT 2
#define TOP_HAT_RIGHT 3
#define DARKNESS_THRESHOLD 600
#endif
