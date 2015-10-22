//
//  Canvas.h
//  acRender
//
//  Created by ZhaoZhihui on 15/9/30.
//  Copyright © 2015年 ZhaoZhihui. All rights reserved.
//

#ifndef Canvas_h
#define Canvas_h

#include "Vector.h"
#include "Color.hpp"
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
        
        void drawPixel(int x,int y,float z, const Color& c);
        void drawPixel(const Vector& p, const Color& c);
        
        void drawLine(const Vector& lVec,const Vector& rVec);
        
    protected:
        int     mWidth,mHeight;
        
        Uint32*   mPixels;
        
    };
 
}

#endif /* Canvas_h */
