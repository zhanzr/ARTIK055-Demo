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

	printf("%s %s\n", __DATE__, __TIME__);

	sysinfo();

	printf("%s %s FlashList:%s\n",
			CONFIG_ARCH_FAMILY,
			CONFIG_ARCH_CHIP,
			CONFIG_ARTIK05X_FLASH_PART_NAME);

	printf("Ram:[%08X-%08X]\n",
			CONFIG_RAM_START, CONFIG_RAM_END);

	printf("Random:\n");
	for(size_t i=0; i < 10; ++i)
	{
		printf("%08X ", rand());
	}
	printf("\n");

	printf("Endian Test:\n");
#if __BYTE_ORDER == __LITTLE_ENDIAN
	printf("L%d\n", __BYTE_ORDER);
#else
	printf("B%d\n", __BYTE_ORDER);
#endif
	uint32_t t_endian = 0x12345678;
	uint8_t* tp = (uint8_t*)&t_endian;
	for(size_t i=0; i < sizeof(t_endian); ++i)
	{
		printf("%02X ", *(tp+i));
	}
	printf("\n");

	printf("ProgMem: PageSize:%u, MaxPage:%u, BlockSize:%u\n",
			FLASH_PAGE_SIZE,
			FLASH_MAX_PAGE,
			FLASH_BLOCK_SIZE);

	adctest(1);

	return ret;
}

