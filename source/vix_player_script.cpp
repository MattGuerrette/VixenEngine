//
// Created by direc on 10/13/2022.
//

#include "vix_player_script.h"
#include "vix_gameobject.h"
#include "vix_input.h"
#include "vix_time.h"

namespace Vixen
{

	static float Lerp(float start, float end, float interval)
	{
		return (1 - interval) * start + interval * end;
	}

	static float GetTrackPosition(int pos)
	{
		return 5.0f * pos;
	}

	PlayerScript::PlayerScript()
		: Component(Component::Type::PLAYER_SCRIPT), Jumping(false), Position(0), JumpCount(0.0f),
		  MoveSpeed(6.5f)
	{

	}

	void PlayerScript::VOnInit()
	{

	}

	void PlayerScript::VOnEnable()
	{
		Position = 0;
	}

	void PlayerScript::VUpdate()
	{
		// TODO(mguerrette): Access mineshaft spawner
		// Scene.FindObjectWithName("railspawner")

		auto* object = m_parent;
		auto* transform = object->GetTransform();

		if (!Jumping)
		{
			if (Input::KeyPressSingle(IKEY::A) && Position > -1)
			{
				StartX = GetTrackPosition(Position);
				Position--;
				TargetX = GetTrackPosition(Position);
				Jumping = true;
				transform->SetRotation(Vector3(0, 0, 10));
			}

			if (Input::KeyPressSingle(IKEY::D) && Position < 1)
			{
				StartX = GetTrackPosition(Position);
				Position++;
				TargetX = GetTrackPosition(Position);
				Jumping = true;
				transform->SetRotation(Vector3(0, 0, -10));
			}
		}

		if (Jumping)
		{
			if (transform->GetPosition().X() == TargetX || (JumpCount * MoveSpeed) > 1)
			{
				Jumping = false;
				JumpCount = 0.0f;
				transform->SetPosition(Vector3(TargetX, transform->GetPosition().Y(), transform->GetPosition().Z()));
				transform->SetRotation(Vector3(0, 0, 0));
			}
			else
			{
				float x = Lerp(StartX, TargetX, JumpCount * MoveSpeed);
				transform->SetPosition(Vector3(x, transform->GetPosition().Y(), transform->GetPosition().Z()));
				JumpCount += Time::DeltaTime();
			}
		}

		// TODO(mpguerrette): Update material with distance in mineshaft
		// this.material:SetFloat(0, "distance", this.mineShaft.distance);
		// go:GetChild(2):GetModelComponent():GetMaterial():SetFloat(0, "distance", this.mineShaft.distance);

	}

	void PlayerScript::VOnDisable()
	{

	}

	void PlayerScript::VOnDestroy()
	{
	}
}