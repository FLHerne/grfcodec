#ifndef _SPRITES_H
#define _SPRITES_H

/*****************************************\
*                                         *
* SPRITES.H - A couple of routines to     *
*             decode and encode TTD .GRF  *
*             sprites                     *
*                                         *
*                                         *
* Copyright (C) 2000 by Josef Drexler     *
*               <jdrexler@julian.uwo.ca>  *
*                                         *
* Permission granted to copy and redist-  *
* ribute under the terms of the GNU GPL.  *
* For more info please read the file      *
* COPYING which should have come with     *
* this file.                              *
*                                         *
\*****************************************/

#include <stdio.h>
#include <stdarg.h>

#include "pcxfile.h"
#include "typesize.h"

#ifdef _SPRITES_C
#	define SPRITES_EXTERN
#	define SPRITES_INIT = 0
#else
#	define SPRITES_EXTERN extern
#	define SPRITES_INIT
#endif


// Define some of the bits in info[0]
#define DONOTCROP(info) (info[0] & 64)
#define HASTRANSPARENCY(info) (info[0] & 8)
#define SIZEISCOMPRESSED(info) (info[0] & 2)


// minimum and maximum overlap to search for in the compression routines
#define MINOVERLAP 3
#define MAXOVERLAP 15	// must be <= 15 b/o how it's encoded



class spriteinfowriter : public bandnotify {
	public:
	virtual void addsprite(int /*x*/, U8 /*info*/[8]) { };
	virtual void adddata(U16 /*size*/, U8 * /*data*/) { };
};

class spritestorage {
	public:
	virtual ~spritestorage(){}
	virtual void newsprite() {};
	virtual void setsize(int /*sx*/, int /*sy*/) {};
	virtual int  curspritex() {return 0;};
	virtual void newrow() {};
	virtual void nextpixel(U8 /*colour*/) {};
	virtual void spritedone(int /*sx*/, int /*sy*/) {};
	virtual void spritedone() {};
};


SPRITES_EXTERN int maxx SPRITES_INIT, maxy SPRITES_INIT, maxs SPRITES_INIT;

int decodesprite(FILE *grf, spritestorage *store, spriteinfowriter *writer);

U16 getlasttilesize();
U16 encodetile(FILE *grf, const U8 *image, long imgsize, U8 background, int sx, int sy, const U8 inf[8], int docompress, int spriteno);
U16 encoderegular(FILE *grf, const U8 *image, long imgsize, const U8 inf[8], int docompress);

#endif /* _SPRITES_H */