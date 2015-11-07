
function rotate.OnInit()
	
end

function rotate.OnEnable()
	this.moveSpeed = 15.0;
end

function rotate.Update(dt)
	this.GameObject:GetTransform():RotateY(dt* this.moveSpeed);
end

function rotate.OnDisable()
	
end

function rotate.OnDestroy()
	
end
