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

#include <apps/shell/tash.h>

#include <system/sysinfo.h>
#include <tinyara/board.h>
#include <tinyara/endian.h>
#include <tinyara/progmem.h>

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

	printf("Endian Test:\n");
	printf("%d\n", __BYTE_ORDER);

	printf("ProgMem: PageSize:%u, MaxPage:%u, BlockSize:%u\n",
			FLASH_PAGE_SIZE,
			FLASH_MAX_PAGE,
			FLASH_BLOCK_SIZE);

	adctest(4);

	return ret;
}

