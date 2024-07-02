#include <stdint.h>
#include <stdio.h>

#define u16_t uint16_t
#define u32_t uint32_t
#define i32_t int32_t

#pragma pack(1)

typedef struct {
  u16_t bf_type;
  u32_t bf_size;
  u16_t bf_reserved1;
  u16_t bf_reserved2;
  u32_t bf_offbits;
} BITMAPFILEHEADER;

typedef struct {
  u32_t bi_size;
  i32_t bi_width;
  i32_t bi_height;
  u16_t bi_planes;
  u16_t bi_bit_count;
  u32_t bi_compression;
  u32_t bi_size_image;
  i32_t bi_Xpels_permeter;
  i32_t bi_Ypels_permeter;
  u32_t bi_clr_used;
  u32_t bi_clr_important;
} BITMAPINFOHEADER;

char *get_compression_method(u32_t compression) {
  switch (compression) {
  case 0:
    return "none";
  case 1:
    return "RLE8";
  case 2:
    return "RLE4";
  case 3:
    return "Bitfields";
  case 4:
    return "JPEG";
  case 5:
    return "PNG";
  case 6:
    return "Alpha Bitfields";
  default:
    return "unknown";
  }
}

void print_info_bmpfile(char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Unable to open file or opening error: \n");
    return;
  }

  BITMAPFILEHEADER first_header;
  fread(&first_header, sizeof(BITMAPFILEHEADER), 1, file);

  if (first_header.bf_type != 0x4D42 && first_header.bf_type != 0x424D) {
    fprintf(stderr, "It's not a BMP file\n");
    fclose(file);
    return;
  }

  BITMAPINFOHEADER info_header;
  fread(&info_header, sizeof(BITMAPINFOHEADER), 1, file);

  printf("Width         : %dpx\n", info_header.bi_width);
  printf("Height        : %dpx\n", info_header.bi_height);
  printf("Bits/pixel    : %d\n", info_header.bi_bit_count);
  printf("Compression   : %s\n",
         get_compression_method(info_header.bi_compression));
  printf("Image Size    : %u byte\n", info_header.bi_size_image);
  printf("Pixels/meter  : %dx%d\n", info_header.bi_Xpels_permeter,
         info_header.bi_Ypels_permeter);
  printf("Colors Used   : %u\n", info_header.bi_clr_used);
  printf("Important Colors : %u\n",
         info_header.bi_clr_important); // Always zero, idk

  fclose(file);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr,
            "Only one command line argument can be used. Take away all the "
            "arguments %s",
            argv[1]);
    return 1;
  }

  print_info_bmpfile(argv[1]);
  return 0;
}
