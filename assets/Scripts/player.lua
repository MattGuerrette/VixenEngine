
function player.OnInit()
	
end

function player.OnEnable()
	this.position = 0;
end

function player.Update(dt)

	local go = this.GameObject;
	
	local transform = go:GetTransform();

	if Input.SingleKeyPress(IKEY.A) and (this.position > -1) then
		transform.Position = transform.Position + Vector3(-5, 0.0, 0.0);
		this.position = this.position - 1;
	end

	if Input.SingleKeyPress(IKEY.D) and (this.position < 1) then
		transform.Position = transform.Position + Vector3(5, 0.0, 0.0);
		this.position = this.position + 1;
	end
	
end

function player.OnDisable()
	
end

function player.OnDestroy()
	
end