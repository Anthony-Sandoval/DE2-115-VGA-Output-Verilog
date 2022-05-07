#include "sys/alt_stdio.h"
#include <altera_up_sd_card_avalon_interface.h>
#include "stdio.h"
#include "io.h"
#include "system.h"
#include <altera_up_avalon_video_pixel_buffer_dma.h>

/*
void VGA_box(int, int, int, int, int);
*/
volatile int i,j;
short int att;/*
void VGA_box(int x1, int y1, int x2, int y2, int pixel_color)
{
	int offset, row, col;

	volatile short *pixel_buffer = (short *) 0x00000000;

	for (row = y1; row <= y2; row++)
	{
		col = x1;
		while (col <= x2)
		{
			offset = (row << 9) + col;
			*(pixel_buffer + offset) = pixel_color;
			++col;
		}
	}
}
*/
int main()
{
	alt_up_sd_card_dev *device_reference = NULL;
	int connected = 0;
	alt_up_pixel_buffer_dma_dev* pb_dev;
	pb_dev = alt_up_pixel_buffer_dma_open_dev("/dev/pixel_buffer_dma");

	short int handler;
	short int att1=0,att2=0,att3=0;
	int pixel;


	///*
	device_reference = alt_up_sd_card_open_dev(SD_CARD_AVALON_INTERFACE_NAME);
	if(device_reference != NULL){
		if((connected == 0) && (alt_up_sd_card_is_Present())){  // check SDcard connection
			printf("\ncard connected\n");
			if(alt_up_sd_card_is_FAT16()) {

				handler = alt_up_sd_card_fopen("mario.BMP", false);

					printf("%d/n",handler);


				att = alt_up_sd_card_get_attributes(handler);
				printf("FAT16 file system detected.\n");
				alt_up_pixel_buffer_dma_clear_screen(pb_dev,0);
				for (j=0;j<54;j++)
				{
					att1 = alt_up_sd_card_read(handler);
				}

				i=0;
				j=0;
				for(int k =0 ; k< 256;k++){
					for(int l =0 ; l<256; l++){
						att1 =(unsigned char) alt_up_sd_card_read(handler);
						att2 =(unsigned char) alt_up_sd_card_read(handler);
						att3 =(unsigned char) alt_up_sd_card_read(handler);
						alt_up_sd_card_read(handler);
						pixel = (att3<<16) | (att2<<8) | att1;
						alt_up_pixel_buffer_dma_draw(pb_dev,pixel,256-l,256-k);
					}
				}
				alt_up_sd_card_fclose(handler);
				alt_up_pixel_buffer_dma_swap_buffers(pb_dev);
			}
			else {
				printf("Unknown File System.\n");
			}
			connected = 1;
		}else if ((connected == 1) && (alt_up_sd_card_is_Present() == false)){
			printf("Card Disconnected");
			connected = 0;
		}
	}
//*/
	return 0;
}

