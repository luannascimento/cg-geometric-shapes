#include "libs/headers.h"

GLuint *textures = NULL;
GLsizei n;
size_t texture_num = -1;

struct tagBITMAPFILEHEADER 
{
  uint16_t bfType;
  uint32_t bfSize;
  uint16_t bfReserved1;
  uint16_t bfReserved2;
  uint32_t bfOffBits;
};

struct tagBITMAPINFOHEADER
{
  uint32_t biSize;
  int32_t biwidth;
  int32_t biHeight;
  uint16_t biPlanes;
  uint16_t biBitCount;
  uint32_t biCompression;
  uint32_t biSizeImage;
  int32_t biXPelsPerMeter;
  int32_t biYPelsPerMeter;
  uint32_t biClrUsed;
  uint32_t biClrImportant;
};

static void freeTextures();

void textureInit(const size_t quantity)
{
  if(n != 0)
  {
    logging("O uso de textura já esta iniciado, arquivo %s","texture.c");
    return;
  }
  textures = (GLuint*) calloc(quantity,sizeof(GLuint));
  if(!textures)
  {
    logging("Erro memoria insuficiente, arquivo %s","texture.c");
    free(textures);
    exit(EXIT_FAILURE);
  }
  atexit(freeTextures);
  n = quantity;
  glGenTextures(n,textures);
}

GLuint loadBitmap( char* fileName )
{
  BITMAPFILEHEADER bitmapFileHeader;
  BITMAPINFOHEADER bitmapInfoHeader;
  char* data = NULL;

  FILE* fp = NULL;

  if(!(fp = fopen(fileName,"rb")))
  {
    logging("Erro ao tenta ler o arquivo %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapFileHeader.bfType, sizeof(uint16_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o tipo do arquivo %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(bitmapFileHeader.bfType != 19778)
  {
    logging("O arquivo %s não e um arquivo BM", fileName);
    exit(EXIT_FAILURE);
  }
  
  if(fread(&bitmapFileHeader.bfSize, sizeof(uint32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o tamanho do arquivo %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapFileHeader.bfReserved1, sizeof(uint16_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o campo reservado do arquivo %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(bitmapFileHeader.bfReserved1 != 0)
  {
    logging("Campo reservado do arquivo %s não e zero", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapFileHeader.bfReserved2, sizeof(uint16_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o campo reservado do arquivo %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(bitmapFileHeader.bfReserved2 != 0)
  {
    logging("Campo reservado do arquivo %s não e zero", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapFileHeader.bfOffBits, sizeof(uint32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o deslocamento, em bytes, para o início da área de dados da imagem do arquivo %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biSize, sizeof(uint32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o tamanho do cabeçalho da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biwidth, sizeof(int32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler a largura da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biHeight, sizeof(int32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler a altura da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biPlanes, sizeof(uint16_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o número de planos da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biBitCount, sizeof(uint16_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o número de bits por px da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biCompression, sizeof(uint32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o tipo de compressão da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biSizeImage, sizeof(uint32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o tamanho da áreas de dados da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biXPelsPerMeter, sizeof(int32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler a resolução horizontal em pixels por metro da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biYPelsPerMeter, sizeof(int32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler a resolução vertical em pixels por metro da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biClrUsed, sizeof(uint32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o número de cores usadas na imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  if(fread(&bitmapInfoHeader.biClrImportant, sizeof(uint32_t), 1, fp) != 1)
  {
    logging("Erro ao tenta ler o número de cores importantes da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  size_t size_data = bitmapInfoHeader.biwidth * bitmapInfoHeader.biHeight * 3;

  data = (char*) malloc(size_data);
  if(!data)
  {
    logging("Erro memoria insuficiente, arquivo %s","texture.c");
    exit(EXIT_FAILURE);
  }

  if(fread(data, size_data, 1, fp) != 1)
  {
    logging("Erro ao tenta ler os dados da imagem %s", fileName);
    exit(EXIT_FAILURE);
  }

  long int i;
  char aux;
  for(i = 0; i < size_data; i+=3)
  {
    aux = data[i];
    data[i] = data[i+2];
    data[i+2] = aux;
  }

  fclose(fp);

  printf("\nCABEÇALHO FILE BITMAP\n");
  printf("Nome do arquivo: %s\n", fileName);
  printf("Tipo do arquivo: %X\n", bitmapFileHeader.bfType);
  printf("Tamanho do arquivo: %d bytes\n", bitmapFileHeader.bfSize);
  printf("Campo reservado 1: %d\n",bitmapFileHeader.bfReserved1);
  printf("Campo reservado 2: %d\n",bitmapFileHeader.bfReserved2);
  printf("Deslocamento para área de dados: %d bytes\n",bitmapFileHeader.bfOffBits);
  printf("Image true color: %s\n",(bitmapFileHeader.bfOffBits == 54) ? "true" : "false");
  printf("\nCABEÇALHO BITMAP\n");
  printf("Tamanho do cabeçalho: %d\n",bitmapInfoHeader.biSize);
  printf("Largura da imagem: %d px\n",bitmapInfoHeader.biwidth);
  printf("Altura da imagem: %d px\n",bitmapInfoHeader.biHeight);
  printf("Número de planos da imagem: %d\n",bitmapInfoHeader.biPlanes);
  printf("Número de bits por pixel: %d\n",bitmapInfoHeader.biBitCount);
  printf("Tipo de compressão: %d\n",bitmapInfoHeader.biCompression);
  printf("Tamanho da imagem (dados): %d bytes\n",bitmapInfoHeader.biSizeImage);
  printf("Resolução horizontal em pixels por metro: %d\n",bitmapInfoHeader.biXPelsPerMeter);
  printf("Resolução vertical em pixels por metro: %d\n",bitmapInfoHeader.biYPelsPerMeter);
  printf("Número de cores usadas na imagem: %d\n",bitmapInfoHeader.biClrUsed);
  printf("Número de cores importantes: %d\n\n",bitmapInfoHeader.biClrImportant);
  
  texture_num++;
  glBindTexture(GL_TEXTURE_2D, texture_num);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmapInfoHeader.biwidth, bitmapInfoHeader.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bitmapInfoHeader.biwidth, bitmapInfoHeader.biHeight, GL_RGB, GL_UNSIGNED_BYTE, data);
  
  free(data);
  textures[texture_num] = texture_num;
  return texture_num;
}

GLuint getTexture(size_t texture)
{
  if(n < texture)
    return -1;

  return textures[texture - 1];
}

static void freeTextures()
{
  free(textures);
}