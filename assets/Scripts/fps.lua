

function fps.OnInit()
	
end

function fps.OnEnable()
   
end

function fps.Update(dt)
  
    this.GameObject:GetTextComponent().Text = "FPS: " .. Time.FPS();

end

function fps.OnDisable()
	
end

function fps.OnDestroy()
	
end
