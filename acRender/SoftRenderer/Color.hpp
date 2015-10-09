//
//  Color.hpp
//  acRender
//
//  Created by ZhaoZhihui on 15/9/30.
//  Copyright © 2015年 ZhaoZhihui. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

#include <stdio.h>
#include <cstdlib>
#include <SDL2/SDL.h>

namespace acRender {
    
    class Color
    {
    public:
        Color(float tr = 1.f, float tg = 1.f, float tb = 1.f, float ta = 1.f):r(tr),g(tg),b(tb),a(ta)
        {}
        
        static Color randomColor() {
            float r = (rand() % 255) / 255.0f;
            float g = (rand() % 255) / 255.0f;
            float b = (rand() % 255) / 255.0f;
            return  Color(r, g, b, 1);
        };
        
        Uint32 bit32() const;
        
        
    protected:
        
        float r,g,b,a;
    };
    
}


#endif /* Color_hpp */
