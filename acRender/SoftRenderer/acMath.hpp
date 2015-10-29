//
//  acMath.hpp
//  acRender
//
//  Created by ZhaoZhihui on 15/10/28.
//  Copyright © 2015年 ZhaoZhihui. All rights reserved.
//

#ifndef acMath_hpp
#define acMath_hpp

#include <stdio.h>
#include "Vector.h"
namespace acRender {
    
#define PI      3.141592654f
#define PI_INV  0.318309886f
    
    typedef Vector Point;
    
    struct ParamLine{
        Point   mP0;
        Point   mP1;
        Vector  mDir;
    };
    
    struct Plane{
        Point mP0;
        Vector mNormal;
    };
    
    struct Matrix4{
        void reset();
        void setIdentity();
        
        float m[16];
    };
    

}

#endif /* acMath_hpp */
