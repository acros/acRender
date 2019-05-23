#include "InputManager.h"

#define USE_SDL_INPUT  true


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
#if USE_SDL_INPUT && false
	const ImGuiIO*  event = static_cast<const ImGuiIO*>(ev);

	m_InputData.clear();

	switch (event->type)
	{
		case SDL_MOUSEMOTION:
		{
			m_InputData.DeltaMouseMove.x = event->motion.xrel;
			m_InputData.DeltaMouseMove.y = event->motion.yrel;
			break;
		}
		case SDL_MOUSEBUTTONDOWN:
		{
			if (event->button.button == SDL_BUTTON_LEFT) m_InputData.MousePressed[0] = true;
			if (event->button.button == SDL_BUTTON_RIGHT) m_InputData.MousePressed[1] = true;
			if (event->button.button == SDL_BUTTON_MIDDLE) m_InputData.MousePressed[2] = true;
			break;
		}
		case SDL_KEYDOWN:
		{
			int key = event->key.keysym.scancode;
			m_InputData.KeysDown[key] = (event->type == SDL_KEYDOWN);
			m_InputData.KeyShift_L = ((SDL_GetModState() & KMOD_LSHIFT) != 0);
			m_InputData.KeyCtrl_L = ((SDL_GetModState() & KMOD_LCTRL) != 0);
			m_InputData.KeyAlt_L = ((SDL_GetModState() & KMOD_LALT) != 0);
//			io.KeySuper = ((SDL_GetModState() & KMOD_GUI) != 0);
			break;
		}
		case SDL_KEYUP:
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
