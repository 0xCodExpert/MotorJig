#include "main.h"
#include "uart_drv.h"
#include "VL53L1X_API.h"
#include "VL53l1X_calibration.h"

uint16_t	dev=0x52;
int status=0;

void VL53L1XInit(void)
{
	 uint8_t byteData, sensorState=0;
	  uint16_t wordData;
	  //	int16_t offset;
	  //	uint16_t xtalk;

	/* Those basic I2C read functions can be used to check your own I2C functions */
	  status = VL53L1_RdByte(dev, 0x010F, &byteData);
	  Uart_Printf("VL53L1X Model_ID: %X\r\n", byteData);
	  status = VL53L1_RdByte(dev, 0x0110, &byteData);
	  Uart_Printf("VL53L1X Module_Type: %X\r\n", byteData);
	  status = VL53L1_RdWord(dev, 0x010F, &wordData);
	  Uart_Printf("VL53L1X: %X\r\n", wordData);
	  while(sensorState==0){
			status = VL53L1X_BootState(dev, &sensorState);
		HAL_Delay(2);
	  }
	  Uart_Printf("Chip booted\r\n");


	    /* This function must to be called to initialize the sensor with the default setting  */
	    status = VL53L1X_SensorInit(dev);
	    /* Optional functions to be used to change the main ranging parameters according the application requirements to get the best ranging performances */
	    status = VL53L1X_SetDistanceMode(dev, 1); /* 1=short, 2=long */
	    status = VL53L1X_SetTimingBudgetInMs(dev, 100); /* in ms possible values [20, 50, 100, 200, 500] */
	    status = VL53L1X_SetInterMeasurementInMs(dev, 100); /* in ms, IM must be > = TB */
	    status = VL53L1X_SetROI(dev, 16, 16);
	  //  status = VL53L1X_SetOffset(dev,20); /* offset compensation in mm */
	  //  status = VL53L1X_SetROI(dev, 16, 16); /* minimum ROI 4,4 */
	  //	status = VL53L1X_CalibrateOffset(dev, 140, &offset); /* may take few second to perform the offset cal*/
	  //	status = VL53L1X_CalibrateXtalk(dev, 1000, &xtalk); /* may take few second to perform the xtalk cal */

	    Uart_Printf("VL53L1X Ultra Lite Driver Example running ...\r\n");
	    status = VL53L1X_StartRanging(dev);   /* This function has to be called to enable the ranging */
}

void VL53L1XProcessData(void)
{
  uint16_t Distance;
  uint16_t SignalRate;
  uint16_t AmbientRate;
  uint16_t SpadNum;
  uint8_t RangeStatus;
  uint8_t dataReady;

 /* read and display data */
	  while (dataReady == 0){
		  status = VL53L1X_CheckForDataReady(dev, &dataReady);
		  HAL_Delay(2);
	  }
	  dataReady = 0;
	  status = VL53L1X_GetRangeStatus(dev, &RangeStatus);
	  status = VL53L1X_GetDistance(dev, &Distance);
	  status = VL53L1X_GetSignalRate(dev, &SignalRate);
	  status = VL53L1X_GetAmbientRate(dev, &AmbientRate);
	  status = VL53L1X_GetSpadNb(dev, &SpadNum);
	  status = VL53L1X_ClearInterrupt(dev); /* clear interrupt has to be called to enable next interrupt*/
	  Uart_Printf("%u, %u, %u, %u, %u\r\n", RangeStatus, Distance, SignalRate, AmbientRate,SpadNum);
}

