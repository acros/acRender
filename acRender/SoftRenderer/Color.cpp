//
//  Color.cpp
//  acRender
//
//  Created by ZhaoZhihui on 15/9/30.
//  Copyright © 2015年 ZhaoZhihui. All rights reserved.
//

#include "Color.hpp"

using namespace acRender;

Uint32 Color::bit32()const
{
    Uint32 A = (Uint32)(a * 255.0f);
    Uint32 R = (Uint32)(r * 255.0f);
    Uint32 G = (Uint32)(g * 255.0f);
    Uint32 B = (Uint32)(b * 255.0f);
    
   return  (A << 24) | (R<< 16) | (G << 8) | B;
}