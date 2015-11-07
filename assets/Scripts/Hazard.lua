function Hazard.OnInit()
	
end

function Hazard.OnEnable()
    Hazard.mineShaft = nil;
    this.player = Scene.FindObjectWithName("minecart1");
end

function Hazard.Update(dt)
    --static member variable
    if Hazard.mineShaft == nil then
        local obj = Scene.FindObjectWithName("railspawner");
        local id = obj:GetID();
        Hazard.mineShaft = MineShaft.hash[""..id];
	end

	local go = this.GameObject;
	
	local transform = go:GetTransform();

    local distance = transform.WorldPosition - this.player:GetTransform().WorldPosition;
    local distanceSqrd = distance:Z() * distance:Z() + distance:X() * distance:X();

    if distanceSqrd <= 3.0 then
		Scene.OpenScene("GameOver");
        Scene.ShowScene("GameOver");
        Scene.SetOrder("GameOver", 2);
        Scene.UnpauseScene("GameOver");
		Scene.PauseScene("scene1");
    end
end

function Hazard.OnDisable()
	
end

function Hazard.OnDestroy()
	
end
