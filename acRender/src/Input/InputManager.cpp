#include "InputManager.h"

#define USE_SDL_INPUT  true

using namespace Acros;

InputManager* InputManager::sInstance = nullptr;


InputManager* InputManager::GetInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new InputManager();
	}
	return sInstance;
}

void InputManager::ProcessEvent(const void* ev)
{
#if USE_SDL_INPUT
	const SDL_Event*  event = static_cast<const SDL_Event*>(ev);

	m_InputData.clear();

	switch (event->type)
	{
		case SDL_MOUSEMOTION:
			m_InputData.DeltaMouseMove.x = event->motion.xrel;
			m_InputData.DeltaMouseMove.y = event->motion.yrel;
			break;
		default:
			break;
	}
#endif
}

InputManager::InputManager()
{

}


InputManager::~InputManager()
{
}
