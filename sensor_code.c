#include "sensor_code.h"

//Initializing global variable
int g_i2cFid;

//Close LED Function
void closeLEDs(int* rgy) {
    if (rgy != NULL) {
        for (int i = 0; i < 3; i++) {
            close(rgy[i]);
        }
        free(rgy);
    }
}

//Set LED Direction Function
int setDirectionLeds() {
    int fd;
    int gpios[3] = {60, 44, 68};  //GPIO numbers
    for (int i = 0; i < 3; i++) {
        char path[256];
        snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", gpios[i]);
        fd = open(path, O_WRONLY);
        if (fd == -1) {
            perror("Failed to open GPIO direction file");
            return -1;
        }
        if (write(fd, "out", 3) == -1) {
            perror("Failed to set direction to out");
            close(fd);
            return -1;
        }
        close(fd);
    }
    return 0;
}

//Turn on LED Function
int* getLEDs(){
    int* rgy = malloc(3 * sizeof(int));
    if (rgy == NULL) {
        perror("Failed to allocate memory");
        return NULL;
    }
    
    int gpios[3] = {60, 44, 68};  //GPIO numbers
    for (int i = 0; i < 3; i++) {
        char path[256];
        snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", gpios[i]);
        rgy[i] = open(path, O_WRONLY);
        if (rgy[i] == -1) {
            perror("Failed to open GPIO value file");
            for (int j = 0; j < i; j++) {
                close(rgy[j]);
            }
            free(rgy);
            return NULL;
        }
    }
    return rgy;
}

//Open the Linux device
void i2cOpen()
{
	g_i2cFid = open("/dev/i2c-2", O_RDWR);
	if (g_i2cFid < 0) {
		perror("i2cOpen");
		exit(1);
	}
}

//Close the Linux device
void i2cClose()
{
	close(g_i2cFid);
}

//Set the I2C slave address for all subsequent I2C device transfers
void i2cSetAddress(int address)
{
	if (ioctl(g_i2cFid, I2C_SLAVE, address) < 0) {
		perror("i2cSetAddress");
		exit(1);
	}
}

int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    uint8_t reg[1];
	reg[0]=reg_addr;

 	if (write(g_i2cFid, reg, 1) != 1) {
		perror("user_i2c_read_reg");
		rslt = 1;
	}
	if (read(g_i2cFid, reg_data, len) != len) {
		perror("user_i2c_read_data");
		rslt = 1;
	}

    return rslt;
}

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
	uint8_t reg[16];
    reg[0]=reg_addr;
	
    for (int i=1; i<len+1; i++)
       reg[i] = reg_data[i-1];

    if (write(g_i2cFid, reg, len+1) != len+1) {
		perror("user_i2c_write");
		rslt = 1;
        exit(1);
	}

    return rslt;
}

void user_delay_ms(uint32_t period)
{
    sleep(period/1000);
}

//Exponent function
double my_exp(double x) {
    double sum = 1.0;
    double term = 1.0;
    int n = 1;

    for (n = 1; n <= 20; n++) {
        term *= x / n;
        sum += term;
    }

    return sum;
}

//Power function
double my_pow(double x, int y) {
    if (y == 0)
        return 1; 
    else if (y < 0)
        return 1 / my_pow(x, -y);
    double result = 1;
    double base = x;

    while (y > 0) {
        if (y % 2 == 1) { 
            result *= base;
        }
        base *= base;
        y /= 2;
    }

    return result;
}

//Find min function
double my_fmin(double x, double y) {
    return x < y ? x : y;
}

