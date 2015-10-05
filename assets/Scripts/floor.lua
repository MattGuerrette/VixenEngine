function floor.OnInit()
	
end

function floor.OnEnable()
	this.moveSpeed = 15.0;
	this.transform = this.GameObject:GetTransform();
end

function floor.Update(dt)

	--[[this.transform:TranslateZ(-dt * this.moveSpeed);

	if this.transform.Position:Z() < -35.0 then
		this.transform.Position = this.transform.Position + Vector3(0.0, 0.0, 250.0);
	end]]--

end

function floor.OnDisable()
	
end

function floor.OnDestroy()
	
end
