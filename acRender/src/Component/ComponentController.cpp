#include "ComponentController.h"
#include "Base/AcObject.h"
#include "Input/InputManager.h"

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
		AcTransform& trans = m_Owner->GetTransform();

		const InputData& input = InputManager::GetInstance()->GetInputData();

	}

}
