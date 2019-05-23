#include "ComponentController.h"
#include "Base/AcObject.h"
#include "Input/InputManager.h"
#include "Camera/Camera.h"
#include "SDL_scancode.h"

namespace Acros
{
	ComponentController::ComponentController(AcObject* o): BaseComponent(o)
	{

	}

	ComponentController::~ComponentController()
	{
	}

	void ComponentController::Update(float deltaTime)
	{
		Camera* cam = static_cast<Camera*>(m_Owner);
		if (cam != nullptr)
		{
			AcTransform& trans = cam->GetTransform();

			const InputData& input = InputManager::GetInstance()->GetInputData();

			static float speed = 5;
			static float roationSpeed = 5;
			//Translation

			AcVector pos = trans.getTranslation();
			AcVector right = cam->GetRight();
			AcVector forward = cam->GetForward();

			ImGuiIO& io = ImGui::GetIO();

			AcVector deltaMove(0,0,0);

			const Uint8 *state = SDL_GetKeyboardState(NULL);
			if (state[SDL_SCANCODE_A]) {
				deltaMove -= (speed * deltaTime * right);
			}
			if (state[SDL_SCANCODE_D]) {
				deltaMove += (speed * deltaTime * right);
			}

			if (state[SDL_SCANCODE_W]) {
				deltaMove += (speed * deltaTime * forward);
			}

			if (state[SDL_SCANCODE_S]) {
				deltaMove -= (speed * deltaTime * forward);
			}


			pos += deltaMove;
			trans.setTranslation(pos);
		}
	}

}
