/* -------------------------------------------------------------------------- *
 *                        BSOD - Blue Screen of Death                         *
 *   Implements the "blue screen" functionality (as seen on Windows) for      *
 * Linux kernel. Displays a messsage, a weird sound (courtesy of BSOD) and    *
 * reboots the system.                                                        *
 *                                                                            *
 * -------------------------------------------------------------------------- */

#ifndef _KERNEL_BSOD_H
#define _KERNEL_BSOD_H

/*
 * Default error message (slightly inspired by windows)
 */
#define BSOD_ERROR_MESSAGE "A problem has been detected and Linux has been shut down to protect your computer. If this is the first time you've seen this stop error screen, restart your computer. If this screen appears again, follow these steps:\n\nCheck for viruses on your computer. Remove any newly installed hard drives or hard drive ccontrollers. Check your hard drive to make sure it is properly configured and terminated.\nRun e2fsck -c to check for hard drive corruption, and then restart your computer.\n\nTechnical information:\n\n*** STOP: 0x0000007B (0xF78D663C, 0xC0000034, 0x00000000, 0x00000000)\n\n\n\n\n\n\n\n\n\n\n"

void display_error(void);

#endif