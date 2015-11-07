
function Rail.OnInit()
end

function Rail.OnEnable()
end


function Rail.Update(dt)

    local moveSpeed = this.manager.moveSpeed + this.manager.boostSpeed;

	GameObject.TranslateZ(-dt * moveSpeed);
	if GameObject.GetTransformZ() < -9.0 then
		this.GameObject:Delete();
	end
end


function Rail.OnDisable()
end

function Rail.OnDestroy()
end
