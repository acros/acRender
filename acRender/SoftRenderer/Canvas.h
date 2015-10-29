//
//  Canvas.h
//  acRender
//
//  Created by ZhaoZhihui on 15/9/30.
//  Copyright © 2015年 ZhaoZhihui. All rights reserved.
//

#ifndef Canvas_h
#define Canvas_h

//#include "Vector.h"
#include "Color.hpp"
#include "acMath.hpp"
#include <SDL2/SDL.h>

namespace acRender {
    class Canvas
    {
    public:
        Canvas(Uint32*  pixels,int width,int height)
        : mPixels(pixels)
        , mWidth(width)
        , mHeight(height)
        {
            assert(mPixels != nullptr);
        }
        
        void clear();
        
        void update();
        
        void drawPixel(const Point& p, const Color& c);
        void drawLine(const Point& lVec,const Point& rVec);
        void drawTriangle(const Point& p1,const Point& p2,const Point& v3);
        
    protected:
        void drawPixel(int x,int y,float z, const Color& c);
        void drawLine(int x1, int y1, int x2, int y2, const Color& c);
        void drawBottomTriangle(const Point& p1, const Point& p2,const Point& p3, const Color& c);
        void drawTopTriangle(const Point& p1,const Point& p2,const Point& p3, const Color& c);
        
        int     mWidth,mHeight;
        Uint32*   mPixels;
        
    };
 
}

#endif /* Canvas_h */
