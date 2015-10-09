#include "main.h"

SdlApplication::SdlApplication()
    : _running(false)
    , mWinHeight(0)
    , mWinWidth(0)
    , mRenderer(nullptr)
    , mWindow(nullptr)
    , mTargetTex(nullptr)
    , mPixelArray(nullptr)
    , mAcCanvas(nullptr)
{
}

SdlApplication::~SdlApplication()
{
	destroy();
}

int SdlApplication::init(int width, int height)
{
    mWinHeight = height;
    mWinWidth = width;
    
	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return APP_FAILED;
	}
	
	mWindow = SDL_CreateWindow("Acros Soft-Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               width, height, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    mTargetTex = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, mWinWidth, mWinHeight);
    mPixelArray = new Uint32[mWinHeight*mWinWidth];
    
    mAcCanvas = new acRender::Canvas(mPixelArray,mWinWidth,mWinHeight);
    
	return APP_OK;
}

void SdlApplication::destroy()
{
	if (mWindow)
	{
        delete mAcCanvas;
        delete [] mPixelArray;
		SDL_DestroyWindow(mWindow);
		SDL_DestroyRenderer(mRenderer);
		SDL_Quit();
	}
}

int SdlApplication::run(int width, int height)
{
	int state = init(width, height);
	if (state != APP_OK) return state;
	
	// Enter to the SDL event loop.
	SDL_Event ev;
	_running = true;
	
	while (SDL_WaitEvent(&ev))
	{
		onEvent(&ev);
        
        update( 0.1f );
		
        render();
		
		if (_running == false)
		{
			break;
		}
	}
	
	return APP_OK;
}

void SdlApplication::onEvent(SDL_Event* ev)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			_running = false;
			break;
			
		case SDL_KEYDOWN:
		{
			if (ev->key.keysym.sym == SDLK_ESCAPE)
			{
				_running = false;
			}
		}
	}
}

void SdlApplication::update(float dt)
{
    
    mAcCanvas->update();
}

void SdlApplication::render()
{
    
    //Copy the custom image to GPU memory
    SDL_UpdateTexture(mTargetTex, nullptr, mPixelArray, mWinWidth * sizeof (Uint32));
//	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0, 0xff);
	SDL_RenderClear(mRenderer);
    SDL_RenderCopy(mRenderer, mTargetTex, nullptr, nullptr);
    SDL_RenderPresent(mRenderer);
}

int main(int argc, char* argv[])
{
	SdlApplication app;
	return app.run(800, 600);
}