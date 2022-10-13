function gemspawner.OnInit()
	
end

function gemspawner.OnEnable()

	
    this.gemCount = 0;
    this.maxGems = 5;

	this.time = 0.0;
	

    math.randomseed( os.time() );

end

function gemspawner.Update(dt)

	this.time = this.time + dt;

    if (this.time > 10.0) then
        this.time = 0.0;

        local gemPrefab = Prefab.Load("gem_red.pfb");

        --spawn gem at random location
        local gem = gemPrefab:CreateObject();

        this.gemCount = this.gemCount + 1;
        
	    local go = this.GameObject;
	
	    local transform = go:GetTransform();

        lane = math.random(-1, 1);

        xPosition = 0.0;

        if lane < 0 then
            xPosition = -4.0;
        end

        if lane > 0 then
            xPosition = 4.0;
        end

        randomZ = math.random(15, 35);

        gem:GetTransform().Position = transform.Position + Vector3(xPosition, 2.0, randomZ);

    end
   

end

function gemspawner.OnDisable()
	
end

function gemspawner.OnDestroy()
	
end