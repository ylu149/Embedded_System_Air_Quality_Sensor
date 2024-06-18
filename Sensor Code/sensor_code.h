#ifndef SENSOR_CODE_H
#define SENSOR_CODE_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bme680.h"

//Function prototypes for LED management
void closeLEDs(int* rgy);
int setDirectionLeds();
int* getLEDs();

//Function prototypes for I2C device handling
void i2cOpen();
void i2cClose();
void i2cSetAddress(int address);
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
void user_delay_ms(uint32_t period);

//Math prototypes
double my_exp(double x);
double my_pow(double x, int y);
double my_fmin(double x, double y);

#endif 