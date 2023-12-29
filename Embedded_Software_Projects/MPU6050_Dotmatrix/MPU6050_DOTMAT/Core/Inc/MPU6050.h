/*
 * MPU6050.h
 *
 *  Created on: 12 Tem 2023
 *      Author: Yusuf KAYA
 */

#ifndef INC_MPU6050_H_
#define INC_MPU6050_H_

#include "main.h"

#define MPU6050_ADDRESS		0x68
#define WHO_AM_I	0x75
#define PWR_MGMT_1	0x6B
#define SMPRT_DIV	0x19
#define GYRO_CONFIG	0x1B
#define ACCEL_CONFIG	0x1C

#define ACCEL_XOUT_H	0x3B
#define GYRO_XOUT_H		0x43


// Accelerometers and Gyroscope datas
typedef struct{
	float x;
	float y;
	float z;
}Direction_t;

typedef struct{
	int16_t raw_x;
	int16_t raw_y;
	int16_t raw_z;
}Raw_t;

// Gyroscope Full - Scale Range
typedef enum{
	FS_250 = 0,
	FS_500 = 1,
	FS_1000 = 2,
	FS_2000 = 3,
}FS_SEL;

// Accelerometer Full - Scale Range
typedef enum{
	AFS_2G = 0,
	AFS_4G = 1,
	AFS_8G = 2,
	AFS_16G = 3,
}AFS_SEL;

//Sensor Status
typedef enum{
	SENSOR_OK = 1,
	SENSOR_ERROR = 0,
}SensorStatus_t;

// All datas
typedef struct{

	Direction_t accel;				//Accelerometer result
	Direction_t gyros;				//Gyroscope result
	Raw_t accel_raw;				//Accelerometer raw values
	Raw_t gyros_raw;				//Gyroscope raw values
	float gyro_const;
	float accel_const;

}SensorData_t;


SensorStatus_t MPU6050_Response(uint8_t DevAdd);
void MPU6050_Init(SensorData_t *pSensor, FS_SEL gyro, AFS_SEL accel);
SensorStatus_t Gyro_Config(SensorData_t *pSensor, FS_SEL gyro);
SensorStatus_t Accel_Config(SensorData_t *pSensor, AFS_SEL accel);
void MPU6050_READ_DATA(SensorData_t *pSensor);





















#endif /* INC_MPU6050_H_ */
