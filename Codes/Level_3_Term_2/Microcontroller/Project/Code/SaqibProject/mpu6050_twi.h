/*
 * ATmega32_Gyrometer.c
 * http://www.electronicwings.com
 *
 */
#ifndef MPU6050_H_
#define MPU6050_H_

//#define F_CPU 8000000UL		/* Define CPU clock Frequency 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include delay header file */
#include <inttypes.h>		/* Include integer type header file */
#include <stdlib.h>		/* Include standard library file */
#include <stdio.h>		/* Include standard I/O library file */
#include "MPU6050_res_define.h"	/* Include MPU6050 register define file */
#include "I2C_Master_H_file.h"	/* Include I2C Master header file */


 

void Gyro_Init()		/* Gyro initialization function */
{
	_delay_ms(150);		/* Power up time >100ms */
	I2C_Start_Wait(0xD0);	/* Start with device write address */
	I2C_Write(SMPLRT_DIV);	/* Write to sample rate register */
	I2C_Write(0x07);	/* 1KHz sample rate */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(PWR_MGMT_1);	/* Write to power management register */
	I2C_Write(0x01);	/* X axis gyroscope reference frequency */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(CONFIG);	/* Write to Configuration register */
	I2C_Write(0x00);	/* Fs = 8KHz */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(GYRO_CONFIG);	/* Write to Gyro configuration register */
	I2C_Write(0x18);	/* Full scale range +/- 2000 degree/C */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(ACCEL_CONFIG);/* Write to Accelo configuration register */
	I2C_Write(0x00);	/* Full scale range +/- 2g */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(MOT_THR);	/* Write to motion threshold register */
	I2C_Write(0x00);	/* Motion detection threshold value */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(FIFO_EN);	/* Write to FIFO enable register */
	I2C_Write(0x00);	/* FIFO disabled */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(FF_THR);	/* Write to free fall threshold register */
	I2C_Write(0x00);	/* Free fall threshold value */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(FF_DUR);	/* Write to free fall duration register */
	I2C_Write(0x00);	/* Free fall duration counter */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(MOT_DUR);	/* Write to motion duration register */
	I2C_Write(0x00);	/* Motion detection duration counter */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(ZRMOT_DUR);	/* Write to zero motion duration register */
	I2C_Write(0x00);	/* Zero motion detection duration counter */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(ZRMOT_THR);	/* Write to zero motion threshold register */
	I2C_Write(0x00);	/* Zero motion detection threshold value */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_MST_CTRL);/* Write to I2C Master control register */
	I2C_Write(0x00);	/* Disable multi-master */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV0_REG);/* Write to I2C Slave0 data register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV0_ADDR);/* Write to I2C Slave0 address register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV0_CTRL);/* Write to I2C Slave0 Control register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV1_REG);/* Write to I2C Slave1 data register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV1_ADDR);/* Write to I2C Slave1 address register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV1_CTRL);/* Write to I2C Slave1 control register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV2_REG);/* Write to I2C Slave2 data register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV2_ADDR);/* Write to I2C Slave2 address register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV2_CTRL);/* Write to I2C Slave2 control register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV3_REG);/* Write to I2C Slave3 data register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV3_ADDR);/* Write to I2C Slave3 address register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV3_CTRL);/* Write to I2C Slave3 control register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV4_REG);/* Write to I2C Slave4 data register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV4_ADDR);/* Write to I2C Slave4 address register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV4_CTRL);/* Write to I2C Slave4 control register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV4_DO);	/* Write to I2C Slave4 data out register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV4_DI);	/* Write to I2C Slave4 data in register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_PIN_CFG);	/* Write to interrupt pin configuration register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_ENABLE);	/* Write to interrupt enable register */
	I2C_Write(0x01);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV0_DO);	/* Write to I2C Slave0 data out register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV1_DO);	/* Write to I2C Slave1 data out register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV2_DO);	/* Write to I2C Slave2 data out register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_SLV3_DO);	/* Write to I2C Slave3 data out register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(I2C_MST_DELAY_CTRL);/* Write to I2C Master delay control register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(SIGNAL_PATH_RESET);/* Write to Signal Path Reset register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(MOT_DETECT_CTRL);/* Write to Motion detection control register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(USER_CTRL);	/* Write to User control register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(PWR_MGMT_2);	/* Write to power management register */
	I2C_Write(0x00);
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(FIFO_R_W);	/* Write to FIFO R/W register */
	I2C_Write(0x00);
	I2C_Stop();
}

void MPU_Start_Loc()
{
	I2C_Start_Wait(0xD0);	/* I2C start with device write address */
	I2C_Write(ACCEL_XOUT_H);/* Write start location address from where to read */ 
	I2C_Repeated_Start(0xD1);/* I2C start with device read address */
}

/*
Function : reads raw data from MPU6050. Reads all data from X axis acceleration to Z axis Gyro rotation serially.
	all except for the temperature are in 2's complement form in the registers. So we're getting the true value of them here.
*/


//void Read_RawValue(float* Acc_x, float* Acc_y, float* Acc_z, float* Temperature, float* Gyro_x, float* Gyro_y, float* Gyro_z)
//{
//	MPU_Start_Loc();									/* Read Gyro values */
//	*Acc_x = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack())-1);
//	*Acc_y = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack())-1);
//	*Acc_z = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack())-1);
//	*Temperature = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
//	*Gyro_x = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack())-1);
//	*Gyro_y = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack())-1);
//	*Gyro_z = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack())-1);
//	I2C_Stop();
//}

void Read_RawValue(float* Acc_x, float* Acc_y, float* Acc_z)
{
	MPU_Start_Loc();									/* Read Gyro values */
	*Acc_x = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack())-1);
	*Acc_y = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack())-1);
	*Acc_z = ~((((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack())-1);

	I2C_Stop();
}



#endif