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

static DigitalOut app_red(D5);
static DigitalOut app_green(D9);
static DigitalOut app_blue(D8);

enum { on, off };

/* Flashing Red -------------- */
void red_on(void)
{
    red = on;
}

void red_off(void)
{
    red = off;
}

/* Group flashing green ------ */
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

/* Quick flashing blue ------- */
void blue_on(void)
{
    blue = on;
}

void blue_off(void)
{
    blue = off;
}

/* South Cardinal mark - app shield red -- */
int south_flashes;

void app_red_on(void)
{
    if (south_flashes > 0) {
        app_red = on;
    }
}

void app_red_off(void)
{
    if (south_flashes > 0) {
        app_red = off;
        south_flashes -= 1;
    }
}

void app_red_reset(void)
{
	south_flashes = 6;
}

void app_red_long_on(void)
{
	app_red = on;
}

void app_red_long_off(void)
{
	app_red = off;
}

int main()
{
    red = 1;
    green = 1;
    app_red = 1;
    app_green = 1;
    schInit();
 
 	/* tasks for red flashing led */
    schAddTask(red_on, 0, 225);
    schAddTask(red_off, 50, 225);
 
 	/* tasks for green group flashing */
    schAddTask(green_grp_on, 0, 225);
    schAddTask(green_grp_off, 50, 225);
    schAddTask(green_grp_reset, 0, 800);
 
 	/* tasks for blue flashing led */
    schAddTask(blue_on, 0, 100);
    schAddTask(blue_off, 25, 100);
 
	/* tasks for south cardinal mark */
   schAddTask(app_red_on,   0, 100);
   schAddTask(app_red_off, 25, 100);
   schAddTask(app_red_reset, 0, 1200);
   schAddTask(app_red_long_on,  600, 1200);
   schAddTask(app_red_long_off, 800, 1200);

	/* start schedule... */
    schStart();
    while (true) {
        schDispatch();
    }
}
