
function rotate.OnInit()
	
end

function rotate.OnEnable()
	this.moveSpeed = 15.0;
	
end

function rotate.Update(dt)

	
	--this.transform:TranslateZ(-dt * this.moveSpeed);

	this.GameObject:GetTransform():TranslateZ(-dt * this.moveSpeed);

	--[[if this.transform.Position:Z() < -9.0 then
		this.transform.Position = this.transform.Position + Vector3(0.0, 0.0, 225.0);
	end]]--
	
	
end

function rotate.OnDisable()
	
end

function rotate.OnDestroy()
	
end
