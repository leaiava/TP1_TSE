#include "leds.h"

#define LEDS_ALL_OFF 0x0000
#define LEDS_OFFSET 1
#define LED_ON_STATE 1

static uint16_t *puerto;
static logger_t RegistrarError;

static uint16_t LedToMask(int led)
{
    return (LED_ON_STATE << (led -LEDS_OFFSET));
}

void LedsCreate(uint16_t *direccion, logger_t logger)
{
    puerto = direccion;
    RegistrarError = logger;
    *puerto = LEDS_ALL_OFF;
}

void LedsOn(int led)
{
    if ((led>= 1 ) && (led<= 16))
    {
        *puerto |= LedToMask(led);
    }
    else
    {
        RegistrarError(0, __FUNCTION__, __LINE__ , "Numero de led invalido");
    }
}

void LedsOff(int led)
{
    if ((led>= 1 ) && (led<= 16))
    {
        *puerto &= ~LedToMask(led);
    }
    else
    {
        RegistrarError(0, __FUNCTION__, __LINE__ , "Numero de led invalido");
    }
}

void LedsOnAll(void)
{
    *puerto = 0xFFFF;
}

void LedsOffAll(void)
{
    *puerto = 0x0000;
}

int LedsIsOff(int led)
{
    if ((led>= 1 ) && (led<= 16))
    {
        if (*puerto && LedToMask(led))
            return 0;
        else    
            return 1;
    }
    else
    {
        RegistrarError(0, __FUNCTION__, __LINE__ , "Numero de led invalido");
    }
    return -1;
}

int LedsIsOn(int led)
{
    if ((led>= 1 ) && (led<= 16))
    {
        if (*puerto && LedToMask(led))
            return 1;
        else    
            return 0;
    }
    else
    {
        RegistrarError(0, __FUNCTION__, __LINE__ , "Numero de led invalido");
    }
    return -1;
}
