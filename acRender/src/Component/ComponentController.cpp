#include "ComponentController.h"
#include "Base/AcObject.h"
#include "Input/InputManager.h"
#include "Camera/Camera.h"
#include "SDL_scancode.h"

using namespace Acros;

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

		//Translation
		const AcVector& pos = trans.getTranslation();
		const AcVector& right = cam->GetRight();
		const AcVector& forward = cam->GetForward();

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

		static AcVector up(0, 1, 0);
		if (state[SDL_SCANCODE_Q]) {
			deltaMove += (speed * deltaTime * up);
		}
		if (state[SDL_SCANCODE_E]) {
			deltaMove -= (speed * deltaTime * up);
		}

		trans.setTranslation(pos + deltaMove);


		/*
		//Camera rotation
		const AcQuat& rot = trans.getRotation();

		static float rotationSpeed = AcMath::RadToDeg(5);

		float deltaAngle = rotationSpeed * deltaTime * input.DeltaMouseMove.x;
		if (glm::abs(deltaAngle) > glm::epsilon<float>())
		{
			AcQuat QuatAroundY(sin(deltaAngle / 2.f), 0.0, 0.0, cos(deltaAngle / 2.f));

			trans.setRotation(rot * QuatAroundY);

		}
		*/
	}
}

