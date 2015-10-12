
function rotate.OnInit()
	
end

function rotate.OnEnable()
	this.moveSpeed = 15.0;
end

function rotate.Update(dt)

	--local go = this.GameObject;
	

	GameObject.TranslateZ(-dt * this.moveSpeed);

   
	if GameObject.GetTransformZ() < -9.0 then
		GameObject.SetTransformPos(GameObject.GetTransformPos() + Vector3(0.0, 0.0, 225.0));
	end
	
	
end

function rotate.OnDisable()
	
end

function rotate.OnDestroy()
	
end
