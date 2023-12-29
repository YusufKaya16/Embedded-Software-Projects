/*
 * MPU6050.c
 *
 *  Created on: 12 Tem 2023
 *      Author: Yusuf KAYA
 */

#include "MPU6050.h"


extern I2C_HandleTypeDef hi2c1;

void MPU6050_Init(SensorData_t *pSensor, FS_SEL gyro, AFS_SEL accel){

	uint8_t pwr_data = 0x00;
	HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS << 1, PWR_MGMT_1, 1, &pwr_data,1, HAL_MAX_DELAY);
	Gyro_Config(pSensor, gyro);
	Accel_Config(pSensor, accel);

}

SensorStatus_t Gyro_Config(SensorData_t *pSensor, FS_SEL gyro){

	HAL_StatusTypeDef check;

	uint8_t data = gyro<<3;
	check = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS<<1, GYRO_CONFIG, 1, &data, 1, 1000);

	if(HAL_OK != check) return SENSOR_ERROR;

	switch(gyro){
	case FS_250:
		pSensor->gyro_const = 131.0; break;
	case FS_500:
		pSensor->gyro_const = 65.5; break;
	case FS_1000:
		pSensor->gyro_const = 32.8; break;
	case FS_2000:
		pSensor->gyro_const = 16.4; break;
	default:
		return SENSOR_ERROR;
	}

	return SENSOR_OK;

}

SensorStatus_t Accel_Config(SensorData_t *pSensor, AFS_SEL accel){

	HAL_StatusTypeDef check;
	uint8_t data = accel<<3;

	check = HAL_I2C_Mem_Write(&hi2c1, MPU6050_ADDRESS<<1, ACCEL_CONFIG, 1, &data, 1, 1000);
	if(HAL_OK != check) return SENSOR_ERROR;

	switch(accel){
	case AFS_2G:
		pSensor->accel_const = 16.384; break;
	case AFS_4G:
		pSensor->accel_const = 8.192; break;
	case AFS_8G:
		pSensor->accel_const = 4.096; break;
	case AFS_16G:
		pSensor->accel_const = 2.048; break;
	default:
		return SENSOR_ERROR;
	}

	return SENSOR_OK;

}

void MPU6050_READ_DATA(SensorData_t *pSensor){

	uint8_t Buffer[14];
	uint8_t RegAdd = ACCEL_XOUT_H;

	HAL_I2C_Master_Transmit(&hi2c1, MPU6050_ADDRESS<<1, &RegAdd, 1, 1000);
	HAL_I2C_Master_Receive(&hi2c1, MPU6050_ADDRESS<<1, Buffer, 14, 1000);

	/* Accelerometer raw values */
	pSensor->accel_raw.raw_x = (int16_t)(Buffer[0]<<8 | Buffer[1]);
	pSensor->accel_raw.raw_y = (int16_t)(Buffer[2]<<8 | Buffer[3]);
	pSensor->accel_raw.raw_z = (int16_t)(Buffer[4]<<8 | Buffer[5]);

	/* Gyroscope raw values */
	pSensor->gyros_raw.raw_x = (int16_t)(Buffer[8]<<8 | Buffer[9]);
	pSensor->gyros_raw.raw_y = (int16_t)(Buffer[10]<<8 | Buffer[11]);
	pSensor->gyros_raw.raw_z = (int16_t)(Buffer[12]<<8 | Buffer[13]);

	pSensor->accel.x = (float)(pSensor->accel_raw.raw_x / pSensor->accel_const);
	pSensor->accel.y = (float)(pSensor->accel_raw.raw_y / pSensor->accel_const);
	pSensor->accel.z = (float)(pSensor->accel_raw.raw_z / pSensor->accel_const);

	pSensor->gyros.x = (float)(pSensor->gyros_raw.raw_x / pSensor->gyro_const);
	pSensor->gyros.y = (float)(pSensor->gyros_raw.raw_y / pSensor->gyro_const);
	pSensor->gyros.z = (float)(pSensor->gyros_raw.raw_z / pSensor->gyro_const);


}









