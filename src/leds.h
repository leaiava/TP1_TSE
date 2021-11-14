#include "stdint.h"
#include "errores.h"

void LedsCreate(uint16_t *direccion, logger_t logger);

void LedsOn(int led);

void LedsOff(int led);

void LedsOnAll(void);

void LedsOffAll(void);

int LedsIsOff(int led);

int LedsIsOn(int led);