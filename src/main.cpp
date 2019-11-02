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

void red_on(void)
{
    red = on;
}

void red_off(void)
{
    red = off;
}

int flashes;                    /* flashes left in sequence */

void green_grp_on(void)
{
    if (flashes > 0) {
        green = on;
    }
}

void green_grp_off(void)
{
    if (flashes > 0) {
        green = off;
        flashes -= 1;
    }
}

void green_grp_reset(void)
{
    flashes = 3;
}


int main()
{
    red = 1;
    green = 1;
    led_app_red = 1;
    led_app_green = 1;

    schInit();

    /* tasks for red flashing led */
    schAddTask(red_on, 0, 9);
    schAddTask(red_off, 2, 9);

    /* tasks for green group flashing */
    schAddTask(green_grp_on, 0, 9);
    schAddTask(green_grp_off, 2, 9);
    schAddTask(green_grp_reset, 0, 32);

    schStart();

    while (true) {
        schDispatch();
    }
}
