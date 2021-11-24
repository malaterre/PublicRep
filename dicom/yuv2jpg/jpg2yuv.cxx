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

class Decompress {
  typedef jpeg_decompress_struct *ptr;
  jpeg_decompress_struct srcinfo{};

 public:
  Decompress() { jpeg_create_decompress(&srcinfo); }
  ~Decompress() { jpeg_destroy_decompress(&srcinfo); }
  operator ptr() { return &srcinfo; }
  jpeg_decompress_struct *operator->() { return &srcinfo; }
};

void put_scanline_someplace(File &stream, JSAMPROW buffer, int row_stride)
{
  fwrite(buffer, 1, row_stride, stream);
}

int main(int argc, char * argv[])
{
  if( argc < 3 ) return 1;
  const char *input = argv[1];
  const char *output = argv[2];

  Decompress cinfo;
  /* We use our private extension JPEG error handler.
   * Note that this struct must live as long as the main JPEG parameter
   * struct, to avoid dangling-pointer problems.
   */
  //struct my_error_mgr jerr;
  struct jpeg_error_mgr jerr;
  /* More stuff */
  //FILE *infile;                 /* source file */
  JSAMPARRAY buffer;            /* Output row buffer */
  int row_stride;               /* physical row width in output buffer */

  /* In this example we want to open the input file before doing anything else,
   * so that the setjmp() error recovery below can assume the file is open.
   * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
   * requires it in order to read binary files.
   */

  File infile(input, "rb");
  if (!infile) {
    throw std::invalid_argument("failure to open input.");
  }
 
  //if ((infile = fopen(filename, "rb")) == NULL) {
  //  fprintf(stderr, "can't open %s\n", filename);
  //  return 0;
  //}

  /* Step 1: allocate and initialize JPEG decompression object */

  /* We set up the normal JPEG error routines, then override error_exit. */
  cinfo->err = jpeg_std_error(&jerr);
#if 0
  jerr.pub.error_exit = my_error_exit;
  /* Establish the setjmp return context for my_error_exit to use. */
  if (setjmp(jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object, close the input file, and return.
     */
    jpeg_destroy_decompress(cinfo);
    fclose(infile);
    return 0;
  }
#endif
  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(cinfo);

  /* Step 2: specify data source (eg, a file) */

  jpeg_stdio_src(cinfo, infile);

  /* Step 3: read file parameters with jpeg_read_header() */

  (void)jpeg_read_header(cinfo, TRUE);
  /* We can ignore the return value from jpeg_read_header since
   *   (a) suspension is not possible with the stdio data source, and
   *   (b) we passed TRUE to reject a tables-only JPEG file as an error.
   * See libjpeg.txt for more info.
   */

  /* Step 4: set parameters for decompression */

  /* In this example, we don't need to change any of the defaults set by
   * jpeg_read_header(), so we do nothing here.
   */

  /* Step 5: Start decompressor */

  (void)jpeg_start_decompress(cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */

  File outfile(output, "wb");
  if (!outfile) {
    throw std::invalid_argument("failure to open output.");
  }

  /* We may need to do some setup of our own at this point before reading
   * the data.  After jpeg_start_decompress() we have the correct scaled
   * output image dimensions available, as well as the output colormap
   * if we asked for color quantization.
   * In this example, we need to make an output work buffer of the right size.
   */
  /* JSAMPLEs per row in output buffer */
  row_stride = cinfo->output_width * cinfo->output_components;
  /* Make a one-row-high sample array that will go away when done with image */
#if 0
  buffer = (*cinfo->mem->alloc_sarray)
                ((j_common_ptr)cinfo, JPOOL_IMAGE, row_stride, 1);
#endif
  jpeg_decompress_struct *tmp = cinfo;
  buffer = (*cinfo->mem->alloc_sarray)
                ((j_common_ptr)tmp, JPOOL_IMAGE, row_stride, 1);
#if 0
  std::vector<uint8_t> tmp(row_stride*3);
  buffer[0] = tmp.data();
#endif

  /* Step 6: while (scan lines remain to be read) */
  /*           jpeg_read_scanlines(...); */

  /* Here we use the library's state variable cinfo->output_scanline as the
   * loop counter, so that we don't have to keep track ourselves.
   */
  while (cinfo->output_scanline < cinfo->output_height) {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    (void)jpeg_read_scanlines(cinfo, buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
    put_scanline_someplace(outfile, buffer[0], row_stride);
  }

  /* Step 7: Finish decompression */

  (void)jpeg_finish_decompress(cinfo);
  /* We can ignore the return value since suspension is not possible
   * with the stdio data source.
   */

  /* Step 8: Release JPEG decompression object */

  /* This is an important step since it will release a good deal of memory. */
  jpeg_destroy_decompress(cinfo);

  /* After finish_decompress, we can close the input file.
   * Here we postpone it until after no more JPEG errors are possible,
   * so as to simplify the setjmp error logic above.  (Actually, I don't
   * think that jpeg_destroy can do an error exit, but why assume anything...)
   */
  fclose(infile);

  /* At this point you may want to check to see whether any corrupt-data
   * warnings occurred (test whether jerr.pub.num_warnings is nonzero).
   */

  /* And we're done! */
  return 0;
}
