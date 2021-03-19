#ifndef _COMMON_H_
#define _COMMON_H_

#define TRUE			1
#define FALSE 			0

#define RECV            1
#define SEND            0

#define OFF             1
#define ON              0

typedef enum {
    LED_ON = ON,
    LED_OFF = OFF,
    LED_COUNT,
} LED_STATE;

#endif
