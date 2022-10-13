//
// Created by direc on 10/12/2022.
//

#include "vix_fps_script.h"
#include "vix_gameobject.h"
#include "vix_time.h"

namespace Vixen
{
	FpsScript::FpsScript()
		: Component(Component::Type::FPS_SCRIPT)
	{

	}

	void FpsScript::VOnInit()
	{

	}

	void FpsScript::VOnEnable()
	{

	}

	void FpsScript::VUpdate()
	{
		this->m_parent->GetComponent<UIText>()->SetText(
			"FPS: " + std::to_string(Time::FPS()));
	}

	void FpsScript::VOnDisable()
	{

	}

	void FpsScript::VOnDestroy()
	{

	}
}
