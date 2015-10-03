function wall.OnInit()
	
end

function wall.OnEnable()
	this.moveSpeed = 15.0;
end

function wall.Update(dt)

	
	local go = this.GameObject;
	
	local transform = go:GetTransform();

	transform:TranslateZ(-dt * this.moveSpeed);

	if transform.Position:Z() < -10.0 then
		transform.Position = transform.Position + Vector3(0.0, 0.0, 200.0);
	end

end

function wall.OnDisable()
	
end

function wall.OnDestroy()
	
end
