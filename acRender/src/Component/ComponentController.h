#pragma once

#include "Base/AcObject.h"

namespace Acros
{
	class BaseComponent
	{
	public:
		BaseComponent(AcObject* o) : m_Owner(0){}
		virtual ~BaseComponent() {

		}

		virtual void Update(float deltaTime) {}

	protected:
		class AcObject*	m_Owner;
	};




	class ComponentController : BaseComponent
	{
	public:
		ComponentController(AcObject* o);
		~ComponentController();

		virtual void Update(float deltaTime)override;

	};

}
