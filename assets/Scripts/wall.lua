function wall.OnInit()
	
end

function wall.OnEnable()
	this.moveSpeed = 15.0;
end

function wall.Update(dt)

	

	GameObject.TranslateZ(-dt * this.moveSpeed);

    
    
	if GameObject.GetTransformZ() < -10.0 then
		GameObject.SetTransformPos(GameObject.GetTransformPos() + Vector3(0.0, 0.0, 200.0));
	end

end

function wall.OnDisable()
	
end

function wall.OnDestroy()
	
end
