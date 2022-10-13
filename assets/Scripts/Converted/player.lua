function player.OnInit()
    this.startX = 0;
    this.targetX = 0;
    this.isJumping = false;
    this.jumpCount = 0;
    this.moveSpeed = 6.5;
    this.material = this.GameObject:GetModelComponent():GetMaterial();
	
	
end

function player.OnEnable()
    this.position = 0;	
end

function GetTrackPos(pos)
    return pos * 5;
end

function player.Update(dt)
--     if this.mineShaft == nil then
--         this.mineShaft = MineShaft.hash[Scene.FindObjectWithName("railspawner"):GetID()..""];
--     end

	

    local go = this.GameObject;

    local transform = go:GetTransform();

	if not this.isJumping then
		if (Input.ControllerButtonPressSingle(IBUTTON.LEFT, 0) or Input.KeyPressSingle(IKEY.A)) and this.position > -1 then
			this.startX = GetTrackPos(this.position);
			this.position = this.position - 1;
			this.targetX = GetTrackPos(this.position);
			this.isJumping = true;
			transform.Rotation = Vector3(0, 0, 10);
		end

		if (Input.ControllerButtonPressSingle(IBUTTON.RIGHT, 0) or Input.KeyPressSingle(IKEY.D)) and this.position < 1 then
			this.startX = GetTrackPos(this.position);
			this.position = this.position + 1;
			this.targetX = GetTrackPos(this.position);
			this.isJumping = true;
			transform.Rotation = Vector3(0, 0, -10);
		end
	end

    if this.isJumping then
        player.Jump(transform, dt);
    end

    
--     this.material:SetFloat(0, "distance", this.mineShaft.distance);
-- 	go:GetChild(2):GetModelComponent():GetMaterial():SetFloat(0, "distance", this.mineShaft.distance);
end

function Lerp(startVal, endVal, interval)
    return (1 - interval) * startVal + interval * endVal;
end

function player.Jump(transform, dt)
    if transform.Position:X() == this.targetX or this.jumpCount * this.moveSpeed > 1 then
        this.isJumping = false;
        this.jumpCount = 0.0;
        transform.Position = Vector3(this.targetX, transform.Position:Y(), transform.Position:Z());
        transform.Rotation = Vector3(0, 0, 0);
    else
        local lerp = Lerp(this.startX, this.targetX, this.jumpCount * this.moveSpeed);
        transform.Position = Vector3(lerp, transform.Position:Y(), transform.Position:Z());
        this.jumpCount = this.jumpCount + dt;
    end
end

function player.OnDisable()

end

function player.OnDestroy()

end