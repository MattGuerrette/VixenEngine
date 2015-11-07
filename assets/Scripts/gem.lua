function gem.OnInit()
	
end

function gem.OnEnable()
    gem.mineShaft = nil;
    this.player = Scene.FindObjectWithName("minecart1");
end

function gem.Update(dt)
    --static member variable
    if gem.mineShaft == nil then
        local obj = Scene.FindObjectWithName("railspawner");
        local id = obj:GetID();
        gem.mineShaft = MineShaft.hash[""..id];
	end

	local go = this.GameObject;
	
	local transform = go:GetTransform();

    local distance = transform.WorldPosition - this.player:GetTransform().WorldPosition;
    local distanceSqrd = distance:Z() * distance:Z() + distance:X() * distance:X();

    if distanceSqrd <= 16.0 then
        gem.mineShaft.score = gem.mineShaft.score + 100;
        go:Delete();
        go = nil;
    end
end

function gem.OnDisable()
	
end

function gem.OnDestroy()
	
end
