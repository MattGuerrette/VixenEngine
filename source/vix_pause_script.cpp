//
// Created by direc on 10/12/2022.
//

#include "vix_pause_script.h"
#include "vix_input.h"
#include "vix_game.h"
#include "vix_scenemanager.h"

namespace Vixen
{
	PauseScript::PauseScript()
		: Component(Component::Type::PAUSE_SCRIPT)
	{

	}

	void PauseScript::VOnInit()
	{

	}

	void PauseScript::VOnEnable()
	{
		SceneManager& manager = SceneManager::instance();
		manager.OpenScene("scene1");
		manager.ShowScene("scene1");
		manager.PauseScene("scene1");
		manager.SetOrder("pause", 1);
	}

	void PauseScript::VUpdate()
	{
		if (Input::KeyPressSingle(IKEY::ESC))
		{
			Game::Exit();
		}

		if (Input::KeyPressSingle(IKEY::SPACE))
		{
			SceneManager& manager = SceneManager::instance();
			manager.HideScene("pause");
			manager.PauseScene("pause");
			manager.UnpauseScene("scene1");
		}
	}

	void PauseScript::VOnDisable()
	{

	}

	void PauseScript::VOnDestroy()
	{

	}
}