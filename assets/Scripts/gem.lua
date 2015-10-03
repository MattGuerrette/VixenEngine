function gem.OnInit()
	
end

function gem.OnEnable()
	this.moveSpeed = 15.0;
end

function gem.Update(dt)

	
	local go = this.GameObject;
	
	local transform = go:GetTransform();

	transform:TranslateZ(-dt * this.moveSpeed);

    local player = Scene.FindObjectWithName("minecart1");

    distance = transform.Position - player:GetTransform().Position;

    if distance:Z() < 2.0 and distance:X() <= 1.0 then
        go:Delete();

        go = nil;
    end

	if transform.Position:Z() < -15.0 then

        go:Delete();

        go = nil;
	end

end

function gem.OnDisable()
	
end

function gem.OnDestroy()
	
end
