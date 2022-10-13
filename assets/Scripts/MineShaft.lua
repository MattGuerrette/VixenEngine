function MineShaft.OnInit()
	this.railPrefab = Prefab.Load("rail.pfb");
	this.railPrefab:MarkStore();
	this.gemPrefab = Prefab.Load("GemRail.pfb");
	this.gemPrefab:MarkStore();
	this.brokenPrefab = Prefab.Load("BrokenRail.pfb");
    this.brokenPrefab:MarkStore();
	this.bufferPrefab = Prefab.Load("Buffer.pfb");
	this.bufferPrefab:MarkStore();
	this.wallPrefab = Prefab.Load("mineSection.pfb");
	this.wallLeftLampPrefab = Prefab.Load("mineSectionLeftLamp.pfb");
	this.wallRightLampPrefab = Prefab.Load("mineSectionRightLamp.pfb");
	this.wallBothLampPrefab = Prefab.Load("mineSectionBothLamp.pfb");
	this.wallPrefab:MarkStore();
	this.wallLeftLampPrefab:MarkStore();
	this.wallRightLampPrefab:MarkStore();
	this.wallBothLampPrefab:MarkStore();
	this.speedBoostPrefab = Prefab.Load("SpeedBoostRail.pfb");
	this.speedBoostPrefab:MarkStore();

    
    this.materials = {};
    local rail = this.gemPrefab:CreateObject();
    this.materials[0] = rail:GetModelComponent():GetMaterial();
    this.materials[1] = rail:GetChild(0):GetModelComponent():GetMaterial();
    rail:Delete();
    local wall = this.wallLeftLampPrefab:CreateObject();
	this.materials[2] = wall:GetChild(2):GetModelComponent():GetMaterial();
    this.materials[3] = wall:GetChild(0):GetModelComponent():GetMaterial();
    this.materials[4] = wall:GetChild(1):GetModelComponent():GetMaterial();
	this.materials[5] = wall:GetChild(0):GetChild(0):GetModelComponent():GetMaterial();
    wall:Delete();
	local hazard = this.brokenPrefab:CreateObject();
	this.materials[6] = hazard:GetModelComponent():GetMaterial();
	hazard:Delete();
	this.materials[7] = LightManager.GetPointMaterial();
	this.materials[8] = LightManager.GetSpotMaterial();
	local buffer = this.bufferPrefab:CreateObject();
	this.materials[9] = buffer:GetChild(0):GetModelComponent():GetMaterial();
	buffer:Delete();


    this.acceleration = 0.0; --add to this in external scripts instead of directly to speed variable gets added to during this objects update
    this.moveSpeed = 15.0;
    this.distance = 0;

    this.maxDist = 120.0; --furthest rail position
    this.sectionLength = 14.8;
    this.lastRailSpawned = nil;

    this.level = 0;
	this.score = 0;
    this.scoreForNextLevel = 1000;

    MineShaft.score = this.score;
	this.hazardHits = 0.0;

	--Speed Boost
	this.speedRemaining = 0.0; --remaining speed reserve
	this.boostSpeed = 0.0;

    this.camera = nil;

end

function MineShaft.OnEnable()
    math.randomseed(os.time());
    MineShaft.SpawnMoreRails();

    print("Enabling Mineshaft");
end

function Lerp(startVal, endVal, interval)
    return (1 - interval) * startVal + interval * endVal;
end

function MineShaft.UpdateBoost(dt)
	if this.speedRemaining > 0 then 
		this.boostSpeed = this.boostSpeed + 3.0 * dt;
		this.speedRemaining = this.speedRemaining - 3.0 * dt;
	elseif this.boostSpeed > 1 then
		this.boostSpeed = this.boostSpeed - dt;
	end
end

function MineShaft.GetRandomHazardRail()
    local rand = math.random();
    if (rand > 0.4) then
        return this.brokenPrefab;
	else 
		return this.bufferPrefab;
    end
end

function MineShaft.GetRandomSafeRail()
    local rand = math.random();
    if (rand > 0.98) then
		return this.speedBoostPrefab;
    elseif (rand > 0.90) then
        return this.gemPrefab;
    else
        return this.railPrefab;
	end
end

function MineShaft.SpawnMoreRails()
    --get z of last spawned rail
    local z = 0;
    if this.lastRailSpawned ~= nil then
        z = this.lastRailSpawned:GetTransform().Position:Z();
    else
        --first time running this, make first few have no difficulty
        while z < 60 do
            MineShaft.MakeSegment(z + this.sectionLength);
            z = this.lastRailSpawned:GetTransform().Position:Z();
        end
    end
    this.level = 1;
    while z < this.maxDist do
        MineShaft.MakeSegment(z + this.sectionLength);
        z = this.lastRailSpawned:GetTransform().Position:Z();
    end
end

function MineShaft.MakeSegment(z)
    -- spawn row of rails with obstacles
    local numHazards = 0;
    if this.level ~= 0 then
        numHazards = math.random() * (3.0 - (3.0 / (1.0 + this.level)));
    end
    --which column we start spawning with
    local columns = { -1, 0, 1 };
    MineShaft.ShuffleArray(columns, 3);

    for i = 1, 3, 1 do
        if(numHazards > 1) then
	        MineShaft.SpawnRail(columns[i], z - this.sectionLength/2.0, MineShaft.GetRandomHazardRail());
            numHazards = numHazards - 1;
        else
	        MineShaft.SpawnRail(columns[i], z - this.sectionLength/2.0, MineShaft.GetRandomSafeRail());
        end
    end

    --spawn secondary row of rails
    MineShaft.SpawnRail(-1, z, this.railPrefab);
	MineShaft.SpawnRail(0, z, this.railPrefab);
	this.lastRailSpawned = MineShaft.SpawnRail(1, z, this.railPrefab);

	-- wall section
	local wallNum = math.random();
	if wallNum > .5 then
		MineShaft.SpawnWall(z - this.sectionLength/2.0, this.wallPrefab);	
	elseif wallNum > .3 then
		MineShaft.SpawnWall(z - this.sectionLength/2.0, this.wallLeftLampPrefab);	
	elseif wallNum > .1 then
		MineShaft.SpawnWall(z - this.sectionLength/2.0, this.wallRightLampPrefab);	
	elseif wallNum > 0 then
		MineShaft.SpawnWall(z - this.sectionLength/2.0, this.wallBothLampPrefab);	
	end

	MineShaft.SpawnWall(z, this.wallPrefab);
end

function MineShaft.ShuffleArray(array, size)
    for i = 0, 2 * size, 1 do
        local j, k = math.random(size), math.random(size);
        array[j], array[k] = array[k], array[j];
    end
end

function MineShaft.SpawnRail(column, row, prefab)
	local rail = prefab:CreateObject();
	rail:GetTransform().Position = Vector3(5.0 * column, 0.0, row);
    
    local id = rail:GetID();

    Rail.hash[""..id].manager = this;

	return rail;
end

function MineShaft.SpawnWall(row, prefab)
	local wall = prefab:CreateObject();
	wall:GetTransform().Position = Vector3(0.0, 0.0, row);

	local id = wall:GetID();
	MineSection.hash[""..id].manager = this;

	return wall;
end


function MineShaft.Update(dt)
    MineShaft.UpdateBoost(dt);

    this.moveSpeed = this.moveSpeed + this.acceleration;
    this.acceleration = 0.0;

	this.distance = this.distance + ((this.moveSpeed + this.boostSpeed)* dt);
	this.score = this.score + (this.moveSpeed * dt);

    --Update score ui-text with score value
    this.GameObject:GetTextComponent().Text = "Score: " .. math.floor(this.score);

    if this.score > this.scoreForNextLevel then
        this.level = this.level + 1;
        this.scoreForNextLevel = this.scoreForNextLevel + this.level * 1000;
        this.moveSpeed = this.moveSpeed + 5;
    end

    MineShaft.SpawnMoreRails();

    MineShaft.UpdateShaders();
end

--also sets fov if there's a boost
function MineShaft.UpdateShaders()
    for i=0, 9, 1 do
        this.materials[i]:SetFloat(0, "distance", this.distance);
    end
    
    if this.camera == nil then
        this.camera = Scene.FindObjectWithName("camera"):GetCameraComponent():GetCamera()
    end

    this.camera:SetFOV(math.rad(45 + this.boostSpeed));
end

function MineShaft.OnDisable()
	
end


function MineShaft.OnDestroy()
	this.railPrefab:MarkDelete();
	this.gemPrefab:MarkDelete();
	this.brokenPrefab:MarkDelete();
	this.wallPrefab:MarkDelete();
	this.wallLeftLampPrefab:MarkDelete();
	this.wallRightLampPrefab:MarkDelete();
	this.wallBothLampPrefab:MarkDelete();
	this.speedBoostPrefab:MarkDelete();
	this.bufferPrefab:MarkDelete();

end
