
function camera.OnInit()
	
end

function camera.OnEnable()
	this.speed = 40;
	this.mouseLook = 0.25;

    this.freeform = false;

    this.position = this.GameObject:GetTransform().Position;
    this.rotation = this.GameObject:GetTransform().Rotation;
end

function camera.Update(dt)

	local go = this.GameObject;

	local transform = go:GetTransform();

	-- Handle Keyboard Controls

    if Input.SingleKeyPress(IKEY.M) then

        if this.freeform then
            this.freeform = false;
            transform.Position = this.position;
            transform.Rotation = this.rotation;
        else
            this.freeform = true;
        end
    end

    if this.freeform then

	    if Input.KeyPress(IKEY.W) then
		    local v = transform:Forward();

		    transform:Translate(v * dt * this.speed);
	    end

	    if Input.KeyPress(IKEY.S) then
		    local v = transform:Forward();

		    transform:Translate(v * dt * -1.0 * this.speed);
	    end

	    if Input.KeyPress(IKEY.A) then
		    local v = transform:Right();

		    transform:Translate(v * dt * -1.0 * this.speed);
	    end

	    if Input.KeyPress(IKEY.D) then
		    local v = transform:Right();

		    transform:Translate(v * dt * this.speed);
	    end

	    --Handle Mouse Look Controls

	    deltaX = Input.MouseDeltaX(1280/2);
	    deltaY = Input.MouseDeltaY(720/2);
	    transform:RotateX(deltaY * this.mouseLook);
	    transform:RotateY(deltaX * this.mouseLook);

    end

end

function camera.OnDisable()
	
end

function camera.OnDestroy()
	
end