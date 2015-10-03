
function rotate.OnInit()
	
end

function rotate.OnEnable()
	this.moveSpeed = 15.0;
end

function rotate.Update(dt)

	local go = this.GameObject;
	
	local transform = go:GetTransform();
	
	transform:TranslateZ(-dt * this.moveSpeed);

	if transform.Position:Z() < -9.0 then
		transform.Position = transform.Position + Vector3(0.0, 0.0, 225.0);
	end
	
	
end

function rotate.OnDisable()
	
end

function rotate.OnDestroy()
	
end
