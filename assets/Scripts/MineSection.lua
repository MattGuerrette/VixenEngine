
function MineSection.OnInit()
end

function MineSection.OnEnable()
end


function MineSection.Update(dt)

local moveSpeed = this.manager.moveSpeed + this.manager.boostSpeed;

GameObject.TranslateZ(-dt * moveSpeed);
if GameObject.GetTransformZ() < -9.0 then
		this.GameObject:Delete();
	end
	
	
end

function MineSection.OnDisable()
end

function MineSection.OnDestroy()
end
