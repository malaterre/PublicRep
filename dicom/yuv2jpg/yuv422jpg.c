#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "jpeglib.h"

int yuv422_to_jpeg(unsigned char *data, int image_width, int image_height, FILE *fp, int quality)
{
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];  /* pointer to JSAMPLE row[s] */
    int row_stride;    /* physical row width in image buffer */
    JSAMPIMAGE  buffer;
    int band,i,buf_width[3],buf_height[3], mem_size, max_line, counter;
    unsigned char *yuv[3];
    uint8_t *pSrc, *pDst;

    yuv[0] = data;
    yuv[1] = yuv[0] + (image_width * image_height);
    yuv[2] = yuv[1] + (image_width * image_height) /2;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, fp);

    cinfo.image_width = image_width;  /* image width and height, in pixels */
    cinfo.image_height = image_height;
    cinfo.input_components = 3;    /* # of color components per pixel */
    //cinfo.in_color_space = JCS_RGB;  /* colorspace of input image */
    cinfo.jpeg_color_space = JCS_YCbCr;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, quality, TRUE );

    cinfo.optimize_coding = TRUE;

    cinfo.raw_data_in = TRUE;
    cinfo.comp_info[0].h_samp_factor = 2;
    cinfo.comp_info[0].v_samp_factor = 1;

    jpeg_start_compress(&cinfo, TRUE);

    buffer = (JSAMPIMAGE) (*cinfo.mem->alloc_small) ((j_common_ptr) &cinfo, JPOOL_IMAGE, 3 * sizeof(JSAMPARRAY));
    for(band=0; band <3; band++)
    {
        buf_width[band] = cinfo.comp_info[band].width_in_blocks * DCTSIZE;
        buf_height[band] = cinfo.comp_info[band].v_samp_factor * DCTSIZE;
        buffer[band] = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, buf_width[band], buf_height[band]);
    }
    max_line = cinfo.max_v_samp_factor*DCTSIZE;
    for(counter=0; cinfo.next_scanline < cinfo.image_height; counter++)
    {
        //buffer image copy.
        for(band=0; band <3; band++)
        {
            mem_size = buf_width[band];
            pDst = (uint8_t *) buffer[band][0];
            pSrc = (uint8_t *) yuv[band] + counter*buf_height[band] * buf_width[band];

            for(i=0; i <buf_height[band]; i++)
            {
                memcpy(pDst, pSrc, mem_size);
                pSrc += buf_width[band];
                pDst += buf_width[band];
            }
        }
        jpeg_write_raw_data(&cinfo, buffer, max_line);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    return 0;
}

int main(int argc, char *argv[])
{
  if(argc < 3 ) return 1;
  const char * input = argv[1];
  const char * output = argv[2];
  int image_width = 800;
  int image_height = 555;

  FILE *f = fopen(input, "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  if( fsize != image_height * image_width * 2 )
  {
    fprintf(stderr, "wrong size %d", fsize);
   }
unsigned char *data = malloc(fsize);
fread(data, sizeof *data, fsize, f);
fclose(f);

  f = fopen(output, "wb");

  yuv422_to_jpeg(data, image_width, image_height, f, 100);
fclose(f);

  return 0;
}
