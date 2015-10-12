function floor.OnInit()
	
end

function floor.OnEnable()
	this.moveSpeed = 15.0;
end

function floor.Update(dt)

	
	

	GameObject.TranslateZ(-dt * this.moveSpeed);

     

	if GameObject.GetTransformZ() < -35.0 then
		GameObject.SetTransformPos(GameObject.GetTransformPos() + Vector3(0.0, 0.0, 250.0));
	end

end

function floor.OnDisable()
	
end

function floor.OnDestroy()
	
end
