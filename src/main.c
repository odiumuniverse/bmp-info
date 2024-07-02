#include <stdint.h>
#include <stdio.h>

#define u16_t uint16_t
#define u32_t uint32_t
#define i32_t int32_t

#pragma pack(1)

typedef struct {
  u16_t bfType;
  u32_t bfSize;
  u16_t bfReserved1;
  u16_t bfReserved2;
  u32_t bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
  u32_t biSize;
  i32_t biWidth;
  i32_t biHeight;
  u16_t biPlanes;
  u16_t biBitCount;
  u32_t biCompression;
  u32_t biSizeImage;
  i32_t biXPelsPerMeter;
  i32_t biYPelsPerMeter;
  u32_t biClrUsed;
  u32_t biClrImportant;
} BITMAPINFOHEADER;

char *getCompressionMethod(u32_t compression) {
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

  if (first_header.bfType != 0x4D42 && first_header.bfType != 0x424D) {
    fprintf(stderr, "It's not a BMP file\n");
    fclose(file);
    return;
  }

  BITMAPINFOHEADER info_header;
  fread(&info_header, sizeof(BITMAPINFOHEADER), 1, file);

  printf("Width         : %dpx\n", info_header.biWidth);
  printf("Height        : %dpx\n", info_header.biHeight);
  printf("Bits/pixel    : %d\n", info_header.biBitCount);
  printf("Compression   : %s\n",
         getCompressionMethod(info_header.biCompression));
  printf("Image Size    : %u byte\n", info_header.biSizeImage);
  printf("Pixels/meter  : %dx%d\n", info_header.biXPelsPerMeter,
         info_header.biYPelsPerMeter);
  printf("Colors Used   : %u\n", info_header.biClrUsed);
  printf("Important Colors : %u\n",
         info_header.biClrImportant); // Always zero, idk

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
