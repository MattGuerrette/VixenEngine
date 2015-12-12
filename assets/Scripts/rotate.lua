

function rotate.OnInit()
	
end

function rotate.OnEnable()
   
end

function rotate.Update(dt)
  
    this.GameObject:GetTransform():RotateY(dt * 100);
   
end

function rotate.OnDisable()
	
end

function rotate.OnDestroy()
	
end
