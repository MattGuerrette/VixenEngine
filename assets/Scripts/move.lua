
function move.OnInit()
	
end

function move.OnEnable()
	local go = this.GameObject;
	
	local transform = go:GetTransform();

	--transform:RotateX(90);

	this.moveSpeed = 50.0;
end

function move.Update(dt)

	
	local go = this.GameObject;
	
	local transform = go:GetTransform();

	--[[if Input.KeyPress(IKEY.S) then
		transform:TranslateZ(-dt * this.moveSpeed);
	end

	if Input.KeyPress(IKEY.W) then
		transform:TranslateZ(dt * this.moveSpeed);
	end

	if Input.KeyPress(IKEY.A) then
		transform:TranslateX(-dt * this.moveSpeed);
	end

	if Input.KeyPress(IKEY.D) then
		transform:TranslateX(dt * this.moveSpeed);
	end]]--

	--[[local deltaX = Input.MouseDeltaX(1280.0 / 2.0);
	local deltaY = Input.MouseDeltaY(720.0 / 2.0);
	--print(deltaX * 0.25 .. " : " .. deltaY * 0.25)
	transform:RotateX(deltaY * 0.25);
	transform:RotateY(deltaX * 0.25);]]--	
end

function move.OnDisable()
	
end

function move.OnDestroy()
	
end
