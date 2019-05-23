#pragma once

#include "Base/AcObject.h"

namespace Acros
{
	class BaseComponent
	{
	public:
		BaseComponent(AcObject* o) : m_Owner(o){}
		virtual ~BaseComponent() {

		}

		virtual void Update(float deltaTime) {}

	protected:
		class AcObject*	m_Owner;
	};




	class ComponentController : public BaseComponent
	{
	public:
		ComponentController(AcObject* o);
		~ComponentController();

		virtual void Update(float deltaTime)override;

	};

}
