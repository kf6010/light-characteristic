/* Light Characteristics
 * Demonstrating the use of TTA
 */


#include <stdbool.h>
#include <stdint.h>
#include <scheduler.h>
#include <string.h>
#include <mbed.h>



static DigitalOut red(LED_RED);
static DigitalOut green(LED_GREEN);
static DigitalOut blue(LED_BLUE);

static DigitalOut led_app_red(D5);
static DigitalOut led_app_green(D9);
static DigitalOut led_app_blue(D8);

enum { on, off };

int main()
{
    red = 1;
    green = 1;
    led_app_red = 1;
    led_app_green = 1;

    schInit();


    schStart();

    while (true) {
        schDispatch();
    }
}
