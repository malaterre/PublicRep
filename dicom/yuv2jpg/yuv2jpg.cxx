#include <stdio.h> // before jpeglib.h
#include <jpeglib.h>

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <iostream>

class File {
  typedef FILE *ptr;
  ptr stream;

 public:
  File(std::string const &filename, std::string const &mode)
      : stream(fopen(filename.c_str(), mode.c_str())) {}
  ~File() {
    if (stream) {
      fclose(stream);
    }
  };
  operator ptr() const { return stream; }
  File(File const &) = delete;
  File &operator=(File const &) = delete;
};

class Compress {
  typedef jpeg_compress_struct *ptr;
  jpeg_compress_struct dstinfo{};

 public:
  Compress() { jpeg_create_compress(&dstinfo); }
  ~Compress() { jpeg_destroy_compress(&dstinfo); }
  operator ptr() { return &dstinfo; }
  jpeg_compress_struct *operator->() { return &dstinfo; }
};

int main(int argc, char *argv[])
{
  if( argc < 3 ) return 1;
  const char *input = argv[1];
  const char *output = argv[2];
  int image_width = 800;
  int image_height = 555;
  int quality = 100;

  std::ifstream ifs(input, std::ios::binary | std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();

  // packed representation:
  if( pos != image_width * image_height * 2 ) {
    std::cerr << "invalid size: " << pos << std::endl;
    return 1;
  }

  std::vector<uint8_t> result(pos);
  ifs.seekg(0, std::ios::beg);
  ifs.read(reinterpret_cast<char *>(result.data()), pos);

  /* This struct contains the JPEG compression parameters and pointers to
   * working space (which is allocated as needed by the JPEG library).
   * It is possible to have several such structures, representing multiple
   * compression/decompression processes, in existence at once.  We refer
   * to any one struct (and its associated working data) as a "JPEG object".
   */
  Compress cinfo;
  /* This struct represents a JPEG error handler.  It is declared separately
   * because applications often want to supply a specialized error handler
   * (see the second half of this file for an example).  But here we just
   * take the easy way out and use the standard error handler, which will
   * print a message on stderr and call exit() if compression fails.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  struct jpeg_error_mgr jerr;
  JSAMPROW row_pointer[1];	/* pointer to JSAMPLE row[s] */
//  int row_stride;		/* physical row width in image buffer */

  /* We have to set up the error handler first, in case the initialization
   * step fails.  (Unlikely, but it could happen if you are out of memory.)
   * This routine fills in the contents of struct jerr, and returns jerr's
   * address which we place into the link field in cinfo.
   */
  cinfo->err = jpeg_std_error(&jerr);

  /* Now we can initialize the JPEG compression object. */

  /* Step 2: specify data destination (eg, a file) */
  /* Note: steps 2 and 3 can be done in either order. */

  /* Here we use the library-supplied code to send compressed data to a
   * stdio stream.  You can also write your own code to do something else.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to write binary files.
   */
  File outfile(output, "wb");
  if (!outfile) {
    throw std::invalid_argument("failure to open output.");
  }
  jpeg_stdio_dest(cinfo, outfile);

  /* Step 3: set parameters for compression */

  /* First we supply a description of the input image.
   * Four fields of the cinfo struct must be filled in:
   */
  cinfo->image_width = image_width; 	/* image width and height, in pixels */
  cinfo->image_height = image_height;
  cinfo->input_components = 3;		/* # of color components per pixel */
  cinfo->in_color_space = JCS_YCbCr; 	/* colorspace of input image, 24bits */
  /* Now use the library's routine to set default compression parameters.
   * (You must set at least cinfo.in_color_space before calling this,
   * since the defaults depend on the source color space.)
   */
  jpeg_set_defaults(cinfo);

  /* Now you can set any non-default parameters you wish to.
   * Here we just illustrate the use of quality (quantization table) scaling:
   */
  jpeg_set_quality(cinfo, quality, TRUE /* limit to baseline-JPEG values */);

  cinfo->optimize_coding = TRUE;
  cinfo->jpeg_color_space = JCS_YCbCr;

  // https://zpl.fi/chroma-subsampling-and-jpeg-sampling-factors/
  cinfo->comp_info[0].h_samp_factor = 2;
  cinfo->comp_info[0].v_samp_factor = 1;
  cinfo->comp_info[1].h_samp_factor = 1;
  cinfo->comp_info[1].v_samp_factor = 1;
  cinfo->comp_info[2].h_samp_factor = 1;
  cinfo->comp_info[2].v_samp_factor = 1;

  /* Step 4: Start compressor */

  /* TRUE ensures that we will write a complete interchange-JPEG file.
   * Pass TRUE unless you are very sure of what you're doing.
   */
  jpeg_start_compress(cinfo, TRUE);

  /* Step 5: while (scan lines remain to be written) */
  /*           jpeg_write_scanlines(...); */

  /* Here we use the library's state variable cinfo.next_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   * To keep things simple, we pass one scanline per call; you can pass
   * more if you wish, though.
   */
//  row_stride = image_width * 3;	/* JSAMPLEs per row in image_buffer */

  // https://gist.github.com/royshil/fa98604b01787172b270
  std::vector<uint8_t> tmprowbuf(image_width * 3);
  row_pointer[0] = &tmprowbuf[0];
  while (cinfo->next_scanline < cinfo->image_height) {
    /* jpeg_write_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could pass
     * more than one scanline at a time if that's more convenient.
     */
    //row_pointer[0] = & image_buffer[cinfo->next_scanline * row_stride];
    unsigned i, j;
    unsigned offset = cinfo->next_scanline * cinfo->image_width * 2; //offset to the correct row
    for (i = 0, j = 0; i < cinfo->image_width * 2; i += 4, j += 6) { //input strides by 4 bytes, output strides by 6 (2 pixels)
        tmprowbuf[j + 0] = result[offset + i + 0]; // Y (unique to this pixel)
        tmprowbuf[j + 1] = result[offset + i + 2]; // U (shared between pixels)
        tmprowbuf[j + 2] = result[offset + i + 3]; // V (shared between pixels)
        tmprowbuf[j + 3] = result[offset + i + 1]; // Y (unique to this pixel)
        tmprowbuf[j + 4] = result[offset + i + 2]; // U (shared between pixels)
        tmprowbuf[j + 5] = result[offset + i + 3]; // V (shared between pixels)
    }
    (void) jpeg_write_scanlines(cinfo, row_pointer, 1);
  }

  /* Step 6: Finish compression */

  jpeg_finish_compress(cinfo);
  /* After finish_compress, we can close the output file. */

  /* Step 7: release JPEG compression object */

  /* This is an important step since it will release a good deal of memory. */

  /* And we're done! */
  std::cout << "success" << std::endl;
  return 0;
}
