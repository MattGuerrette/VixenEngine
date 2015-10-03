function floor.OnInit()
	
end

function floor.OnEnable()
	this.moveSpeed = 15.0;
end

function floor.Update(dt)

	
	local go = this.GameObject;
	
	local transform = go:GetTransform();

	transform:TranslateZ(-dt * this.moveSpeed);

	if transform.Position:Z() < -35.0 then
		transform.Position = transform.Position + Vector3(0.0, 0.0, 250.0);
	end

end

function floor.OnDisable()
	
end

function floor.OnDestroy()
	
end
