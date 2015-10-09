//
//  main.h
//  acRender
//
//  Created by ZhaoZhihui on 15/9/28.
//  Copyright © 2015年 ZhaoZhihui. All rights reserved.
//
#ifndef main_h
#define main_h

#include <SDL2/SDL.h>
#include "Canvas.h"

class SdlApplication
{
public:
    SdlApplication();
    ~SdlApplication();
    
    int run(int width, int height);
    
protected:
    enum APP_STATE{
        APP_OK = 0,
        APP_FAILED = 1
    };
    
    int init(int width, int height);
    void destroy();
    
    void onEvent(SDL_Event* ev);
    void update(float dt);
    void render();
    
    bool _running;

    int mWinHeight,mWinWidth;
    
    SDL_Window*     mWindow;
    SDL_Renderer*   mRenderer;
    
    SDL_Texture*    mTargetTex;
    Uint32*         mPixelArray;
    
    acRender::Canvas*   mAcCanvas;
};


#endif /* main_h */
