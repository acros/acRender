//
//  Canvas.cpp
//  acRender
//
//  Created by ZhaoZhihui on 15/9/30.
//  Copyright © 2015年 ZhaoZhihui. All rights reserved.
//

#include "Canvas.h"

using namespace acRender;

void Canvas::clear()
{
    memset(mPixels, 0, sizeof(Uint32)*mWidth*mHeight);
}


void Canvas::drawPixel(int x,int y,float z, const Color& c)
{
    //TODO: Concern the z order
    int index =  (int)(mWidth * y + x);
    mPixels[index] = c.bit32();
}

void Canvas::update()
{
    //Random fulfill color
    for (int i=0; i<mWidth; ++i) {
        for (int j=0; j<mHeight; ++j) {
            
            drawPixel(i, j, 0, Color::randomColor());
        }
    }
}