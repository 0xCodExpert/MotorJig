#ifndef _MODBUS_H_
#define _MODBUS_H_

#include <stdbool.h>

typedef enum {
	MODBUS_STATE_ADDRESS,
	MODBUS_STATE_FUNCTION,
	MODBUS_STATE_STARTING_REGISTER_HI,
	MODBUS_STATE_STARTING_REGISTER_LO,
	MODBUS_STATE_NUMBER_REGISTER_HI,
	MODBUS_STATE_NUMBER_REGISTER_LO,
	MODBUS_STATE_CRC16_LO,
	MODBUS_STATE_CRC16_HI
} MODBUS_STATE;

#define MODBUS_DATA_BUF_SIZE		128

typedef struct {
	uint8_t buf[MODBUS_DATA_BUF_SIZE];
	uint8_t index;
} MODBUS_DATA;

typedef struct {
	MODBUS_STATE state;
	uint8_t address;
	uint8_t function;
	uint16_t reg;
	uint16_t number;
	uint16_t crc16;
	MODBUS_DATA data;
	bool done;
} MODBUS;

extern MODBUS Modbus;

void ModbusInit(MODBUS *pModbusm, uint8_t address);
uint16_t ModbusCrc16 (const uint8_t *nData, uint16_t wLength);
void ModbusProcessData(MODBUS *pModbus, uint8_t data);

#endif
