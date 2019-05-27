#pragma once

#include <memory>
#include "Math/AcMath.h"

namespace Acros
{
	struct InputData
	{
	public:

		AcVector2	DeltaMouseMove;

		bool MousePressed[3];

		bool        KeyCtrl_L;
		bool        KeyShift_L;
		bool        KeyAlt_L;

		bool        KeysDown[512];

		void clear()
		{
			MousePressed[0] = false;
			MousePressed[1] = false;
			MousePressed[2] = false;
			KeyCtrl_L = KeyAlt_L = KeyShift_L = false;

			DeltaMouseMove.x = 0;
			DeltaMouseMove.y = 0;

			memset(KeysDown, 0, sizeof(bool) * 512);
		}
	};


	class InputManager
	{
	private:
		static InputManager* sInstance;
		InputManager();
		~InputManager();

	public:
		static InputManager* GetInstance();

		void ProcessEvent(const void* ev);

		const InputData& GetInputData()const { return m_InputData; }

	private:
		InputData		m_InputData;
	};

}

