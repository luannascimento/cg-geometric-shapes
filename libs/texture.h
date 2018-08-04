#ifndef _TEXTURE_
#define _TEXTURE_
typedef struct tagBITMAPFILEHEADER BITMAPFILEHEADER;
typedef struct tagBITMAPINFOHEADER BITMAPINFOHEADER;
extern void textureInit( size_t );
extern GLuint loadBitmap( char* );
extern GLuint getTexture( size_t );
#endif