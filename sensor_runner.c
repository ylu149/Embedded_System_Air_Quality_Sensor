#include "sensor_code.h"
#include <signal.h>

//Shutdown flag
volatile sig_atomic_t shutdown_flag = 0;
void handle_sigint(int sig) {
    shutdown_flag = 1;
}

int main(int argc, char *argv[] )
{
	signal(SIGINT, handle_sigint);
	int RED = 0;
	int GREEN = 1;
	int YELLOW = 2;
	int delay = 3;
	int nMeas = 3;

	printf("**** BME680 start measurements  ****\n");
    //Open Linux I2C device
	i2cOpen();
	//Set address of the BME680
	i2cSetAddress(BME680_I2C_ADDR_SECONDARY);

    //init device
	struct bme680_dev gas_sensor;
	gas_sensor.dev_id = BME680_I2C_ADDR_SECONDARY;
	gas_sensor.intf = BME680_I2C_INTF;
	gas_sensor.read = user_i2c_read;
	gas_sensor.write = user_i2c_write;
	gas_sensor.delay_ms = user_delay_ms;
	int8_t rslt = BME680_OK;
	rslt = bme680_init(&gas_sensor);
    uint8_t set_required_settings;

	//Set the temperature, pressure and humidity settings
	gas_sensor.tph_sett.os_hum = BME680_OS_2X;
	gas_sensor.tph_sett.os_pres = BME680_OS_4X;
	gas_sensor.tph_sett.os_temp = BME680_OS_8X;
	gas_sensor.tph_sett.filter = BME680_FILTER_SIZE_3;

	//Set the remaining gas sensor settings and link the heating profile 
	gas_sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;

	//Create a ramp heat waveform in 3 steps
	gas_sensor.gas_sett.heatr_temp = 320; //degree Celsius
	gas_sensor.gas_sett.heatr_dur = 150; //milliseconds

	//Select the power mode, must be set before writing the sensor configuration
	gas_sensor.power_mode = BME680_FORCED_MODE; 

	//Set the required sensor settings needed 
	set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL 
		| BME680_GAS_SENSOR_SEL;

	//Set the desired sensor configuration
	rslt = bme680_set_sensor_settings(set_required_settings,&gas_sensor);

	//Set the power mode 
	rslt = bme680_set_sensor_mode(&gas_sensor);

	//Get the total measurement duration so as to sleep or wait till the measurement is complete
	uint16_t meas_period;
	bme680_get_profile_dur(&meas_period, &gas_sensor);
	user_delay_ms(meas_period + delay*1000); /* Delay till the measurement is ready */
    struct bme680_field_data data;

	//Setting up gpio LEDs
	if (setDirectionLeds() == -1) {
		fprintf(stderr, "Failed to set direction of LEDs\n");
        return -1;
    }
    int* LEDs = getLEDs();
    if (LEDs == NULL) {
		fprintf(stderr, "Failed to open LEDs\n");
        return -1;
    }

	write(LEDs[RED], "1", 1);
	write(LEDs[GREEN], "1", 1);
	write(LEDs[YELLOW], "1", 1);
	user_delay_ms(4000);
	write(LEDs[RED], "0", 1);
	write(LEDs[GREEN], "0", 1);
	write(LEDs[YELLOW], "0", 1);
	user_delay_ms(1000);

	while (!shutdown_flag) {
		//Get sensor data
		rslt = bme680_get_sensor_data(&data, &gas_sensor);
		//Avoid using measurements from an unstable heating setup 
		if(data.status & BME680_HEAT_STAB_MSK)
		{
			int R_gas = data.gas_resistance;
			float temp = data.temperature / 100.0f;
			float hum = data.humidity / 1000.0f;
			float R_base = 55000;
			int IAQ = (1-(R_gas/R_base)) * 100;
			if (IAQ < 0) {
				IAQ = 0;
			}
			if (IAQ <=50) {
				write(LEDs[RED], "0", 1);
				write(LEDs[GREEN], "1", 1);
				write(LEDs[YELLOW], "0", 1);
			}
			else if (IAQ > 50 && IAQ <= 150) {
				write(LEDs[RED], "0", 1);
				write(LEDs[GREEN], "0", 1);
				write(LEDs[YELLOW], "1", 1);
			}
			else {
				write(LEDs[RED], "1", 1);
				write(LEDs[GREEN], "0", 1);
				write(LEDs[YELLOW], "0", 1);
			}

			printf("Temperature: %.2f deg C, Pressure: %.2f hPa, Humidity: %.2f %%rH, Gas Resistance: %d ohm, ", temp, data.pressure / 100.0f, hum, R_gas);
			printf("IAQ: %d", IAQ);
			printf("\r\n");
		}
		//Trigger a meausurement
		rslt = bme680_set_sensor_mode(&gas_sensor); /* Trigger a measurement */
		//Wait for a measurement to complete
		user_delay_ms(meas_period + delay*1000); /* Wait for the measurement to complete */			
	}
	//Turn off everything once shutdown flag is tripped
    write(LEDs[RED], "0", 1);
    write(LEDs[GREEN], "0", 1);
    write(LEDs[YELLOW], "0", 1);
	i2cClose();
    closeLEDs(LEDs);
    printf("Clean up done. Exited safely.\n");
	return 0;
}