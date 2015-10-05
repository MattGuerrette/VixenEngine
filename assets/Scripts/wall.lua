function wall.OnInit()
	
end

function wall.OnEnable()
	this.moveSpeed = 15.0;
	this.transform = this.GameObject:GetTransform();
end

function wall.Update(dt)

	--[[this.transform:TranslateZ(-dt * this.moveSpeed);

	if this.transform.Position:Z() < -10.0 then
		this.transform.Position = this.transform.Position + Vector3(0.0, 0.0, 200.0);
	end]]--

end

function wall.OnDisable()
	
end

function wall.OnDestroy()
	
end
