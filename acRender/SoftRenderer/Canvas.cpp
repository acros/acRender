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
    assert(y>=0 && y < mHeight);
    int index =  (int)(mWidth * (mHeight - y - 1) + x);
    assert(index >=0 && index < mWidth*mHeight);
    mPixels[index] = c.bit32();
}

void Canvas::drawPixel(const Point& p, const Color& c)
{
    drawPixel(int(p.x),int(p.y),int(p.z),c);
}

void Canvas::drawLine(const Point& lVec,const Point& rVec)
{
    //TODO - Ignore z-axis here
    float y1 = rVec.y;
    float y0 = lVec.y;
    float x1 = rVec.x;
    float x0 = lVec.x;
    
    Color c(0.5f,0,0.5f);
    drawLine(x0,y0, x1,y1,c);
 }


void Canvas::drawLine(int x0, int y0, int x1, int y1, const Color& c)
{
    float dy = y1 - y0;
    float dx = x1 - x0;
    if(std::fabs(dx) > std::fabs(dy)) {
        int sign = x1 - x0 > 0 ? 1 : -1;
        float ratio = 0;
        if (dx != 0) {
            ratio = (float)dy / dx;
        }
        
        for (int x = x0; x != x1; x += sign) {
            int y = y0 + (x - x0) * ratio;
            drawPixel(x, y,0, c);
        }
    } else {
        int sign = y1 - y0 > 0 ? 1 : -1;
        float ratio = 0;
        if (dy != 0) {
            ratio = (float)dx / dy;
        }
        
        for (int y = y0; y != y1; y += sign) {
            int x = x0 + (y - y0) * ratio;
            drawPixel(x, y,0, c);
        }
    }

}

// The point is anti-clockwise
void Canvas::drawTriangle(const Point& p1,const Point& p2,const Point& v3)
{
    assert(false);
    
    
    
    
}

//Draw from bottom to top and anti-clockwise
void Canvas::drawBottomTriangle(const Point& p1, const Point& p2,const Point& p3, const Color& c)
{
    for (int y = p1.y; y <= p3.y; ++y ) {
        int xEnd,xStart;
        xStart = (y - p1.y) * (p3.x - p1.x) / (p3.y - p1.y) + p1.x +0.5f;   //Why 0.5?
        xEnd = (y - p2.y) * (p3.x - p2.x) / (p3.y - p2.y) + p2.x + 0.5f;
        
        drawLine(xStart, y,xEnd,y,c);
    }
}

//Draw from bottom to top and anti-clockwise
void Canvas::drawTopTriangle(const Point& p1,const Point& p2,const Point& p3, const Color& c)
{
    for (int y = p1.y; y <= p3.y; ++y) {
        int xStart,xEnd;
        xStart = (y - p1.y) * (p3.x - p1.x) / (p3.y - p1.y) + p1.x +0.5f;   //Why 0.5?
        xEnd = (y - p1.y) * (p2.x - p1.x) / (p2.y - p1.y) + p1.x + 0.5f;
        
        drawLine(xStart, y,xEnd,y,c);
    }
}


void Canvas::update()
{
    //Random fulfill color
    for (int i=0; i<mWidth; ++i) {
        for (int j=0; j<mHeight; ++j) {
            
            if(j < mHeight/2)
                //drawPixel(i, j, 0, Color::randomColor());
                drawPixel(i, j, 0, Color(0.5f,0.5f,0,0));
            else
                drawPixel(i, j, 0, Color(0,0,0,0));
        }
    }
    
    drawLine(Vector(500,50,0), Vector(200,200,0));
    drawLine(Vector(mWidth -1,mHeight-1), Vector(100,30));
    
    
    drawBottomTriangle(Point(200,200), Point(300,200), Point(100,400), Color(0.8f,0.2f,0.2f));
    drawTopTriangle(  Point(300,200),Point(600,400), Point(400,400),Color(0.8f,0.2f,0.2f));
}