/*
 * Despues de la configuración todos los leds deben quedar apagados
 * Prender un led cualquiera
 * Apagar un led cualquiera
 * Prender y apagar algunos leds
 * Prender todos los leds juntos
 * Consultar el estado de un led apagado
 * Consultar el estado de un led encendido
 * Revisar los límites de los parámetros
 * Probar valores inválidos para los parámetros
 */
#include "unity.h"
#include "leds.h"
#include <string.h>

#define LED 3
#define LED_LIMITE_SUPERIOR 16
#define LED_LIMITE_INFERIOR 1
#define LED_BIT(x) (1<< (x - 1))

static uint16_t puertoVirtual;

static struct
{
    int gravedad;
    char funcion[64];
}error;

void RegistrarMensaje(int gravedad, const char * funcion, int linea, const char * mensaje)
{
    error.gravedad = gravedad;
    strcpy(error.funcion, funcion);
}

void setUp(void)
{
    error.gravedad = -1;
    memset(error.funcion, 0, sizeof(error.funcion));
    LedsCreate(&puertoVirtual, RegistrarMensaje);
}
//tearDown  se ejecuta al final de las pruebas
//suiteSetUp  se ejecuta una sola vez al inicio de las pruebas
/* Despues de la configuración todos los leds deben quedar apagados */
void test_todos_los_leds_inician_apagados(void)
{
    uint16_t puertoVirtual = 0xFFFF;
    LedsCreate(&puertoVirtual, RegistrarMensaje);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

/* Prender un led cualquiera */
void test_prender_un_led_cualquiera(void)
{
    LedsOn(LED);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED), puertoVirtual);
}

/* Apagar un led cualquiera */
void test_apagar_un_led(void)
{
    LedsOn(LED);
    LedsOff(LED);
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

/* Prender y apagar algunos leds */
void test_prender_y_apagar_varios_leds(void)
{
    LedsOn(LED);
    LedsOn(LED + 3);
    LedsOff(LED);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED + 3), puertoVirtual);
}

/* Probar valores inválidos para los parámetros de LedsOn*/
void test_error_en_parametro_LedsOn_max(void)
{
    LedsOn(17);
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsOn", error.funcion);
}

/* Probar valores inválidos para los parámetros de LedsOn*/
void test_error_en_parametro_LedsOn_min(void)
{
    LedsOn(0);
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsOn", error.funcion);
}

/* Probar valores inválidos para los parámetros de LedsOff*/
void test_error_en_parametro_LedsOff_max(void)
{
    LedsOff(17);
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsOff", error.funcion);
}

/* Probar valores inválidos para los parámetros de LedsOff*/
void test_error_en_parametro_LedsOff_min(void)
{
    LedsOff(0);
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsOff", error.funcion);
}
/* Prender todos los led juntos */ 
void test_prender_todos_los_led_juntos(void)
{
    LedsOnAll();
    TEST_ASSERT_EQUAL_HEX16(0xFFFF, puertoVirtual);
}

/* Apagar todos los led juntos */ 
void test_apagar_todos_los_led_juntos(void)
{
    LedsOffAll();
    TEST_ASSERT_EQUAL_HEX16(0x0000, puertoVirtual);
}

/* Consultar el estado de un led apagado */
void test_consultar_el_estado_de_un_led_apagado(void)
{
    LedsOn(LED);
    TEST_ASSERT_EQUAL( 0 , LedsIsOff(LED) );
    LedsOff(LED);
    TEST_ASSERT_EQUAL( 1 , LedsIsOff(LED) );
    
}

/* Consultar el estado de un led encendido */
void test_consultar_el_estado_de_un_led_encendido(void)
{
    LedsOn(LED);
    TEST_ASSERT_EQUAL( 1 , LedsIsOn(LED) );
    LedsOff(LED);
    TEST_ASSERT_EQUAL( 0 , LedsIsOn(LED) );
}

/* Probar valores inválidos para los parámetros de LedsIsOff*/
void test_error_en_parametro_LedsIsOff_max(void)
{
    TEST_ASSERT_EQUAL(-1, LedsIsOff(17));
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsIsOff", error.funcion);
}

/* Probar valores inválidos para los parámetros de LedsIsOff*/
void test_error_en_parametro_LedsIsOff_min(void)
{
    TEST_ASSERT_EQUAL(-1, LedsIsOff(0));
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsIsOff", error.funcion);
}

/* Probar valores inválidos para los parámetros de LedsIsOn*/
void test_error_en_parametro_LedsIsOn_max(void)
{
    TEST_ASSERT_EQUAL(-1, LedsIsOn(17));
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsIsOn", error.funcion);
}

/* Probar valores inválidos para los parámetros de LedsIsOn*/
void test_error_en_parametro_LedsIsOn_min(void)
{
    TEST_ASSERT_EQUAL(-1, LedsIsOn(0));
    TEST_ASSERT_EQUAL(0, error.gravedad);
    TEST_ASSERT_EQUAL_STRING("LedsIsOn", error.funcion);
}

/* Probar limite superior LedOn*/
void test_parametro_limite_superior_LedsOn(void)
{
    LedsOn(LED_LIMITE_SUPERIOR);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED_LIMITE_SUPERIOR), puertoVirtual);
}

/* Probar limite inferior LedOn*/
void test_parametro_limite_inferior_LedsOn(void)
{
    LedsOn(LED_LIMITE_INFERIOR);
    TEST_ASSERT_EQUAL_HEX16(LED_BIT(LED_LIMITE_INFERIOR), puertoVirtual);
}

/* Probar limite superior LedOff*/
void test_parametro_limite_superior_LedsOff(void)
{
    LedsOff(LED_LIMITE_SUPERIOR);
    TEST_ASSERT_EQUAL_HEX16(!LED_BIT(LED_LIMITE_SUPERIOR), puertoVirtual);
}

/* Probar limite inferior LedOff*/
void test_parametro_limite_inferior_LedsOff(void)
{
    LedsOff(LED_LIMITE_INFERIOR);
    TEST_ASSERT_EQUAL_HEX16(!LED_BIT(LED_LIMITE_INFERIOR), puertoVirtual);
}

/* Probar limite superior LedsIsOff LedsIsOn*/
void test_parametro_limite_superior_LedsIsOff_LedsIsOn(void)
{
    LedsOn(LED_LIMITE_SUPERIOR);
    TEST_ASSERT_EQUAL(0, LedsIsOff(LED_LIMITE_SUPERIOR));
    TEST_ASSERT_EQUAL(1, LedsIsOn(LED_LIMITE_SUPERIOR));
}

/* Probar limite inferior LedsIsOn LedsIsOff*/
void test_parametro_limite_inferior_LedsIsOff(void)
{
    LedsOn(LED_LIMITE_INFERIOR);
    TEST_ASSERT_EQUAL(0, LedsIsOff(LED_LIMITE_INFERIOR));
    TEST_ASSERT_EQUAL(1, LedsIsOn(LED_LIMITE_INFERIOR));
}

/*
  Las 4 son mandatorias
 * Prender todos los led juntos
 * Apagar todos los leds juntos
 * Consultar el estado de un led apagado
 * Consultar el estado de un led encendido
 
 Estas son optativas
 * Revisar los valores limites de los parametros
 * Probar valores invalidos para los parametros
*/