#include "leds.h"

#define LEDS_ALL_OFF 0x0000
#define LEDS_OFFSET 1
#define LED_ON_STATE 1
#define LED_OFF_STATE   0
#define LED_MIN         1
#define LED_MAX         16
#define NO_LED          0
#define LED_NUM_ERROR   -1

static uint16_t *puerto;
static logger_t RegistrarError;

static uint16_t LedToMask(int led)
{
    if ((led>= LED_MIN ) && (led<= LED_MAX))
        {
        return (LED_ON_STATE << (led -LEDS_OFFSET));
        }
    
    RegistrarError(0, __FUNCTION__, __LINE__ , "Numero de led invalido");
    return NO_LED;
}

void LedsCreate(uint16_t *direccion, logger_t logger)
{
    puerto = direccion;
    RegistrarError = logger;
    *puerto = LEDS_ALL_OFF;
}

void LedsOn(int led)
{
    *puerto |= LedToMask(led);
}

void LedsOff(int led)
{
    *puerto &= ~LedToMask(led);
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
    int LedMask = LedToMask(led);
    
    if (LedMask == 0)
        return LED_NUM_ERROR;
    
    if (*puerto && LedMask)
        return LED_OFF_STATE;
    else    
        return LED_ON_STATE;
}

int LedsIsOn(int led)
{
    int LedState = LedsIsOff(led);
    
    if (LedState == LED_NUM_ERROR)
        return LED_NUM_ERROR;
    else
        return !LedState;
}
