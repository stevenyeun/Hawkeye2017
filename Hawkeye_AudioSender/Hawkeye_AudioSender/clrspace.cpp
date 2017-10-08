
/*
 *						DISPLAY MODULE
 *
 * Provides displaying of multiple streams using 
 * VGA card capabilities onto different monitors.
 *
 * Supports Mpeg-2, Mpeg-4, H.264 as well as universal decoding.
 * 
 * Written by SWTEAM	 <bleikher@mail.ru>
 *
 * Color Space convertor
 *
 */
#include "StdAfx.h"
#include <stdlib.h>
#include <windows.h>
//#include "dmmlib.h"

#ifndef SAFE_FREE
#define SAFE_FREE(x) {if(x) free(x); x=NULL;}
#endif //SAFE_FREE

// Masks for BGR16 and RGB16 formats

#define RGB16_LOWER_MASK  0x001f
#define RGB16_MIDDLE_MASK 0x07e0
#define RGB16_UPPER_MASK  0xf800

// Extract unsigned char RGB values from 15 bit pixels

#define RGB16_TO_R(pixel) ((pixel & RGB16_UPPER_MASK)>>8)
#define RGB16_TO_G(pixel) ((pixel & RGB16_MIDDLE_MASK)>>3)
#define RGB16_TO_B(pixel) ((pixel & RGB16_LOWER_MASK)<<3)

#define RGB15_LOWER_MASK  0x001f
#define RGB15_MIDDLE_MASK 0x3e0
#define RGB15_UPPER_MASK  0x7C00

#define RGB15_TO_R(pixel) ((pixel & RGB15_UPPER_MASK)>>7)
#define RGB15_TO_G(pixel) ((pixel & RGB15_MIDDLE_MASK)>>2)
#define RGB15_TO_B(pixel) ((pixel & RGB15_LOWER_MASK)<<3)

// ((((((src[2]<<5)&0xff00)|src[1])<<6)&0xfff00)|src[0])>>3;

#define PACK_RGB16(_r,_g,_b,_pixel) \
_pixel=((((((_r<<5)&0xff00)|_g)<<6)&0xfff00)|_b)>>3

// ((((((src[2]<<5)&0xff00)|src[1])<<5)&0xfff00)|src[0])>>3;

#define PACK_RGB15(_r,_g,_b,_pixel) \
_pixel=((((((_r<<5)&0xff00)|_g)<<5)&0xfff00)|_b)>>3

#define TEST_PICTURE_WIDTH  768
#define TEST_PICTURE_HEIGHT 576

/*
 *   Some braindead YUV conversion (but works at least :-)
 */

long _yuv_ref = 0;

int * r_to_y = (int*)0;
int * g_to_y = (int*)0;
int * b_to_y = (int*)0;

int * r_to_u = (int*)0;
int * g_to_u = (int*)0;
int * b_to_u = (int*)0;

int * r_to_v = (int*)0;
int * g_to_v = (int*)0;
int * b_to_v = (int*)0;

int * y_to_rgb = (int*)0;
int * v_to_r = (int*)0;
int * u_to_g = (int*)0;
int * v_to_g = (int*)0;
int * u_to_b = (int*)0;

/* JPEG Quantization */

int * r_to_yj = (int*)0;
int * g_to_yj = (int*)0;
int * b_to_yj = (int*)0;

int * r_to_uj = (int*)0;
int * g_to_uj = (int*)0;
int * b_to_uj = (int*)0;

int * r_to_vj = (int*)0;
int * g_to_vj = (int*)0;
int * b_to_vj = (int*)0;

int * yj_to_rgb = (int*)0;
int * vj_to_r = (int*)0;
int * uj_to_g = (int*)0;
int * vj_to_g = (int*)0;
int * uj_to_b = (int*)0;

void term_yuv()
{
	long ref = InterlockedDecrement(&_yuv_ref);
	if(ref != 0){
		return ;
	}

  SAFE_FREE(r_to_y);
  SAFE_FREE(g_to_y);
  SAFE_FREE(b_to_y);

  SAFE_FREE(r_to_u);
  SAFE_FREE(g_to_u);
  SAFE_FREE(b_to_u);

  SAFE_FREE(r_to_v);
  SAFE_FREE(g_to_v);
  SAFE_FREE(b_to_v);

  SAFE_FREE(y_to_rgb);
  SAFE_FREE(v_to_r);
  SAFE_FREE(u_to_g);
  SAFE_FREE(v_to_g);
  SAFE_FREE(u_to_b);

  /* JPEG Quantization */

  SAFE_FREE(r_to_yj);
  SAFE_FREE(g_to_yj);
  SAFE_FREE(b_to_yj);

  SAFE_FREE(r_to_uj);
  SAFE_FREE(g_to_uj);
  SAFE_FREE(b_to_uj);

  SAFE_FREE(r_to_vj);
  SAFE_FREE(g_to_vj);
  SAFE_FREE(b_to_vj);

  SAFE_FREE(yj_to_rgb);
  SAFE_FREE(vj_to_r);
  SAFE_FREE(uj_to_g);
  SAFE_FREE(vj_to_g);
  SAFE_FREE(uj_to_b);
}

void init_yuv()
{
	long ref = InterlockedIncrement(&_yuv_ref);
	if(ref != 1){
		return ;
	}
  int i;

  r_to_y = (int*)malloc(0x100 * sizeof(int));
  g_to_y = (int*)malloc(0x100 * sizeof(int));
  b_to_y = (int*)malloc(0x100 * sizeof(int));

  r_to_u = (int*)malloc(0x100 * sizeof(int));
  g_to_u = (int*)malloc(0x100 * sizeof(int));
  b_to_u = (int*)malloc(0x100 * sizeof(int));

  r_to_v = (int*)malloc(0x100 * sizeof(int));
  g_to_v = (int*)malloc(0x100 * sizeof(int));
  b_to_v = (int*)malloc(0x100 * sizeof(int));

  y_to_rgb = (int*)malloc(0x100 * sizeof(int));
  v_to_r   = (int*)malloc(0x100 * sizeof(int));
  u_to_g   = (int*)malloc(0x100 * sizeof(int));
  v_to_g   = (int*)malloc(0x100 * sizeof(int));
  u_to_b   = (int*)malloc(0x100 * sizeof(int));

  /* JPEG Quantization */

  r_to_yj = (int*)malloc(0x100 * sizeof(int));
  g_to_yj = (int*)malloc(0x100 * sizeof(int));
  b_to_yj = (int*)malloc(0x100 * sizeof(int));

  r_to_uj = (int*)malloc(0x100 * sizeof(int));
  g_to_uj = (int*)malloc(0x100 * sizeof(int));
  b_to_uj = (int*)malloc(0x100 * sizeof(int));

  r_to_vj = (int*)malloc(0x100 * sizeof(int));
  g_to_vj = (int*)malloc(0x100 * sizeof(int));
  b_to_vj = (int*)malloc(0x100 * sizeof(int));

  yj_to_rgb = (int*)malloc(0x100 * sizeof(int));
  vj_to_r   = (int*)malloc(0x100 * sizeof(int));
  uj_to_g   = (int*)malloc(0x100 * sizeof(int));
  vj_to_g   = (int*)malloc(0x100 * sizeof(int));
  uj_to_b   = (int*)malloc(0x100 * sizeof(int));


  for(i = 0; i < 0x100; i++)
    {
    // RGB to YUV conversion

    r_to_y[i] = (int)(0.257*0x10000 * i + 16 * 0x10000);
    g_to_y[i] = (int)(0.504*0x10000 * i);
    b_to_y[i] = (int)(0.098*0x10000 * i);

    r_to_u[i] = (int)(-0.148*0x10000 * i);
    g_to_u[i] = (int)(-0.291*0x10000 * i);
    b_to_u[i] = (int)( 0.439*0x10000 * i + 0x800000);

    r_to_v[i] = (int)( 0.439*0x10000 * i);
    g_to_v[i] = (int)(-0.368*0x10000 * i);
    b_to_v[i] = (int)(-0.071*0x10000 * i + 0x800000);

    r_to_yj[i] = (int)((0.29900)*0x10000 * i);
    g_to_yj[i] = (int)((0.58700)*0x10000 * i);
    b_to_yj[i] = (int)((0.11400)*0x10000 * i);

    r_to_uj[i] = (int)(-(0.16874)*0x10000 * i);
    g_to_uj[i] = (int)(-(0.33126)*0x10000 * i);
    b_to_uj[i] = (int)( (0.50000)*0x10000 * i + 0x800000);

    r_to_vj[i] = (int)( (0.50000)*0x10000 * i);
    g_to_vj[i] = (int)(-(0.41869)*0x10000 * i);
    b_to_vj[i] = (int)(-(0.08131)*0x10000 * i + 0x800000);


    // YUV to RGB conversion

    y_to_rgb[i] = (int)(1.164*(i-16)) * 0x10000;

    v_to_r[i]   = (int)( 1.596  * (i - 0x80) * 0x10000);
    u_to_g[i]   = (int)(-0.392  * (i - 0x80) * 0x10000);
    v_to_g[i]   = (int)(-0.813  * (i - 0x80) * 0x10000);
    u_to_b[i]   = (int)( 2.017 * (i - 0x80) * 0x10000);

    /* JPEG Quantization */

    yj_to_rgb[i] = (int)(i * 0x10000);

    vj_to_r[i]   = (int)( 1.40200 * (i - 0x80) * 0x10000);
    uj_to_g[i]   = (int)(-0.34414 * (i - 0x80) * 0x10000);
    vj_to_g[i]   = (int)(-0.71414 * (i - 0x80) * 0x10000);
    uj_to_b[i]   = (int)( 1.77200 * (i - 0x80) * 0x10000);

    }
}

#define RECLIP(color) (unsigned char)((color>0xFF)?0xff:((color<0)?0:color))

#define YUV_2_RGB(y,u,v,r,g,b) i_tmp=(y_to_rgb[y]+v_to_r[v])>>16;\
                                r=RECLIP(i_tmp);\
                                i_tmp=(y_to_rgb[y]+u_to_g[u]+v_to_g[v])>>16;\
                                g=RECLIP(i_tmp);\
                                i_tmp=(y_to_rgb[y]+u_to_b[u])>>16;\
                                b=RECLIP(i_tmp);

#define YUVJ_2_RGB(y,u,v,r,g,b) i_tmp=(yj_to_rgb[y]+vj_to_r[v])>>16;\
                                r=RECLIP(i_tmp);\
                                i_tmp=(yj_to_rgb[y]+uj_to_g[u]+vj_to_g[v])>>16;\
                                g=RECLIP(i_tmp);\
                                i_tmp=(yj_to_rgb[y]+uj_to_b[u])>>16;\
                                b=RECLIP(i_tmp);

#define RGB_TO_YUV(r,g,b,y,u,v) y=(r_to_y[r]+g_to_y[g]+b_to_y[b])>>16;\
                               u=(r_to_u[r]+g_to_u[g]+b_to_u[b])>>16;\
                               v=(r_to_v[r]+g_to_v[g]+b_to_v[b])>>16

#define RGB_TO_YUVJ(r,g,b,y,u,v) y=(r_to_yj[r]+g_to_yj[g]+b_to_yj[b])>>16;\
                                 u=(r_to_uj[r]+g_to_uj[g]+b_to_uj[b])>>16;\
                                 v=(r_to_vj[r]+g_to_vj[g]+b_to_vj[b])>>16

#define RGB_TO_Y(r,g,b,y) y=(r_to_y[r]+g_to_y[g]+b_to_y[b])>>16

#define RGB_TO_YJ(r,g,b,y) y=(r_to_yj[r]+g_to_yj[g]+b_to_yj[b])>>16


void convert_32_to_24(unsigned char * in_frame,
                      unsigned char * out_frame,
                      int width, int height)
{
  int i, j;
  unsigned char * in_pixel;
  unsigned char * out_pixel;

  unsigned char  * out_pixel_save = out_frame;
  unsigned char * in_pixel_save = in_frame;

  for(i = 0; i < height; i++)
    {
    in_pixel = (unsigned char*)in_pixel_save;
    out_pixel = out_pixel_save;
    for(j = 0; j < width; j++)
      {
      out_pixel[0] = in_pixel[0];
      out_pixel[1] = in_pixel[1];
      out_pixel[2] = in_pixel[2];
      in_pixel+=4;
      out_pixel+=3;
      }
    in_pixel_save += width*4;
    out_pixel_save +=  width*3;
    }
}

//balm. not tested
void convert_24_to_32(unsigned char * in_frame,
                      unsigned char * out_frame,
                      int width, int height)
{
  int i, j;
  unsigned char * in_pixel;
  unsigned char * out_pixel;

  unsigned char  * out_pixel_save = out_frame;
  unsigned char * in_pixel_save = in_frame;

  for(i = 0; i < height; i++)
    {
    in_pixel = (unsigned char*)in_pixel_save;
    out_pixel = out_pixel_save;
    for(j = 0; j < width; j++)
      {
      out_pixel[0] = in_pixel[0];
      out_pixel[1] = in_pixel[1];
      out_pixel[2] = in_pixel[2];
	  out_pixel[3] = 0xFF; //opaque black
      in_pixel+=3;
      out_pixel+=4;
      }
    in_pixel_save += width*3;
    out_pixel_save +=  width*4;
    }
}


void convert_YUY2_to_RGB24(unsigned char * in_frame,
                           unsigned char * out_frame,
                           int width, int height)
{
  int i, j, i_tmp;

  unsigned char * in_pixel;
  unsigned char * out_pixel;

  unsigned char * out_pixel_save = out_frame;
  unsigned char * in_pixel_save = in_frame;

  for(i = 0; i < height; i++)
    {
    in_pixel = in_pixel_save;
    out_pixel = out_pixel_save;
    for(j = 0; j < width/2; j++)
      {
      YUV_2_RGB(in_pixel[0], in_pixel[3], in_pixel[1],
                out_pixel[0], out_pixel[1], out_pixel[2]);
      out_pixel+=3;
      YUV_2_RGB(in_pixel[2], in_pixel[3], in_pixel[1],
                out_pixel[0], out_pixel[1], out_pixel[2]);
      out_pixel+=3;
      in_pixel += 4;
      }
    in_pixel_save += width*2;//in_frame->strides[0];
    out_pixel_save +=  width*3;//out_frame->strides[0];
    }
}

//balm. not tested
void convert_RGB24_to_YUY2(unsigned char * in_frame,
                           unsigned char * out_frame,
                           int width, int height)
{
  int i, j;//, i_tmp;

  unsigned char * in_pixel;
  unsigned char * out_pixel;

  unsigned char * out_pixel_save = out_frame;
  unsigned char * in_pixel_save = in_frame;

  for(i = 0; i < height; i++)
    {
    in_pixel = in_pixel_save;
    out_pixel = out_pixel_save;

	for(j = 0; j < width/2; j++){
		RGB_TO_YUV(in_pixel[0], in_pixel[1], in_pixel[2],
			out_pixel[0], out_pixel[1], out_pixel[3]);
	    in_pixel += 3;
        RGB_TO_Y(in_pixel[0], in_pixel[1], in_pixel[2], out_pixel[2]);
	    in_pixel += 3;
        out_pixel += 4;
	}

    in_pixel_save += width*3;//in_frame->strides[0];
    out_pixel_save +=  width*2;//out_frame->strides[0];
    }
}

//balm. not tested
void convert_YUY2_to_RGB32(unsigned char * in_frame,
                           unsigned char * out_frame,
                           int width, int height)
{
  int i, j, i_tmp;

  unsigned char * in_pixel;
  unsigned char * out_pixel;

  unsigned char * out_pixel_save = out_frame;
  unsigned char * in_pixel_save = in_frame;

  for(i = 0; i < height; i++)
    {
    in_pixel = in_pixel_save;
    out_pixel = out_pixel_save;
    for(j = 0; j < width/2; j++)
      {
      YUV_2_RGB(in_pixel[0], in_pixel[3], in_pixel[1],
                out_pixel[0], out_pixel[1], out_pixel[2]);
	  out_pixel[3] = 0xFF;
      out_pixel+=4;
      YUV_2_RGB(in_pixel[2], in_pixel[3], in_pixel[1],
                out_pixel[0], out_pixel[1], out_pixel[2]);
	  out_pixel[3] = 0xFF;
      out_pixel+=4;
      in_pixel += 4;
      }
    in_pixel_save += width*2;//in_frame->strides[0];
    out_pixel_save +=  width*4;//out_frame->strides[0];
    }
}

//balm. not tested
void convert_RGB32_to_YUY2(unsigned char * in_frame,
                           unsigned char * out_frame,
                           int width, int height)
{
  int i, j;//, i_tmp;

  unsigned char * in_pixel;
  unsigned char * out_pixel;

  unsigned char * out_pixel_save = out_frame;
  unsigned char * in_pixel_save = in_frame;

  for(i = 0; i < height; i++)
    {
    in_pixel = in_pixel_save;
    out_pixel = out_pixel_save;

	for(j = 0; j < width/2; j++){
		RGB_TO_YUV(in_pixel[0], in_pixel[1], in_pixel[2],
			out_pixel[0], out_pixel[1], out_pixel[3]);
	    in_pixel += 4;
        RGB_TO_Y(in_pixel[0], in_pixel[1], in_pixel[2], out_pixel[2]);
	    in_pixel += 4;
        out_pixel += 4;
	}

    in_pixel_save += width*4;//in_frame->strides[0];
    out_pixel_save +=  width*2;//out_frame->strides[0];
    }
}

