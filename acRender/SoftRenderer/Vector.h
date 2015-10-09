//
//  Vector.h
//  acRender
//
//  Created by ZhaoZhihui on 15/9/30.
//  Copyright © 2015年 ZhaoZhihui. All rights reserved.
//

#ifndef Vector_h
#define Vector_h

#include <cassert>
#include <cmath>

namespace acRender {
    
    class Vector
    {
    public:
        float x,y,z;
        
        Vector(float tx = 0.f, float ty = 0.f,float tz = 0.f): x(tx),y(ty),z(tz)
        {}
        
        Vector operator+(const Vector& vec)const
        {
            return Vector(x+vec.x, y+vec.y, z+vec.z);
        }
        
        float dot(const Vector& vec)const
        {
            return x*vec.x + y*vec.y + z*vec.z;
        }
        
        Vector cross(const Vector& vec)const
        {
            assert(false);
            return Vector();
        }
        
        float lenSquare()const
        {
            return x*x + y*y + z*z;
        }
        
        float length()const
        {
            return sqrt(lenSquare());
        }
        
    };
    
}
#endif /* Vector_h */
