/* -------------------------------------------------------------------------- *
 *                        BSOD - Blue Screen of Death                         *
 *   Implements the "blue screen" functionality (as seen on Windows) for      *
 * Linux kernel. Displays a messsage, a weird sound (courtesy of BSOD) and    *
 * reboots the system.                                                        *
 *                                                                            *
 * -------------------------------------------------------------------------- */

#include "bsod.h"

#include <linux/vt.h>
#include <linux/notifier.h>

/* 
 * Set screen to a blue background + white text 
 */
unsigned attr = 0x100f;

/*
 * Our display text
 */
unsigned short *textmemptr;

/* 
 * cls - clears the screen
 */
// void cls() {
//     unsigned bl;
//     int i;

//     /* Set default char */
//     bl = ' ' | (attr << 8);

//      Clean up the screen 
//     for (i = 0; i < 25; i++) {
//         memset (textmemptr + i * 80, blank, 80);
//     }
// }

/*
 * display_error - display the rror message to the screen
 *
 * Let the user know that something bad has happenned (but of course that
 * we should just dump him with a lot of debug information so he doesn't
 * really knows what to do with it).
 */
void display_error(void) {
    int i, t_r;

    vc_set_color(&t_r);

    for (i = 0; i < t_r; i++) {
        printk("\n");
    }

    printk(BSOD_ERROR_MESSAGE);
}