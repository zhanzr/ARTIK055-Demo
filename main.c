/****************************************************************************
 *
 * Demo for ARTIK 055 board.
 *
 * Author: zhanzr@foxmail.com
 * Date:	11:50 PM 9/26/2018
 * Description:
 *
 ****************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include <apps/shell/tash.h>

#include <system/sysinfo.h>
#include <tinyara/board.h>
#include <tinyara/endian.h>
#include <tinyara/progmem.h>
#include <tinyara/gpio.h>

#include "examples/wifi-auto.h"

extern int http_main(int argc, char *argv[]);


/**
 * Write the value of gpio
 *
 *   Write the value of given gpio port.
 *
 */
void gpio_write(int port, int value)
{
	char str[4];
	static char devpath[16];
	snprintf(devpath, 16, "/dev/gpio%d", port);
	int fd = open(devpath, O_RDWR);

	ioctl(fd, GPIOIOC_SET_DIRECTION, GPIO_DIRECTION_OUT);
	write(fd, str, snprintf(str, 4, "%d", value != 0) + 1);

	close(fd);
}

/**
 * Blinks the LED for the given file descriptor handle
 *
 *   For the given file handle, the value is enabled and disabled at one second
 *   period.
 */
void blink_led(int i)
{
	gpio_write(i, 1);
	sleep(1);

	gpio_write(i, 0);
	sleep(1);
}

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int demo_main(int argc, FAR char *argv[])
#endif
{
	int ret = 0;

	sysinfo();

	printf("%s %s FlashList:%s\n",
			CONFIG_ARCH_FAMILY,
			CONFIG_ARCH_CHIP,
			CONFIG_ARTIK05X_FLASH_PART_NAME);

	printf("Ram:[%08X-%08X]\n",
			CONFIG_RAM_START, CONFIG_RAM_END);

	printf("L%d\n", __BYTE_ORDER);

	printf("ProgMem: PageSize:%u, MaxPage:%u, BlockSize:%u\n",
			FLASH_PAGE_SIZE,
			FLASH_MAX_PAGE,
			FLASH_BLOCK_SIZE);

	adctest(1);

	blink_led(49);
	StartWifiConnection();
	blink_led(49);

	http_main(argc, argv);
	blink_led(49);

	return ret;
}

