function MineShaft.OnInit()
	this.railPrefab = Prefab.Load("rail.pfb");
	this.gemPrefab = Prefab.Load("GemRail.pfb");
	this.brokenPrefab = Prefab.Load("BrokenRail.pfb");
	this.railPrefab:MarkStore();
	this.gemPrefab:MarkStore();
    this.brokenPrefab:MarkStore();
	this.wallPrefab = Prefab.Load("mineSection.pfb");
	this.wallPrefab:MarkStore();

	this.speedBoostPrefab = Prefab.Load("SpeedBoostRail.pfb");

	this.speedBoostPrefab:MarkStore();
    this.acceleration = 0.0; --add to this in external scripts instead of directly to speed variable gets added to during this objects update
    this.moveSpeed = 15.0;
    

    this.maxDist = 120.0; --furthest rail position
    this.sectionLength = 12.0;
    this.lastRailSpawned = nil;

    this.level = 0;
	this.score = 0;
    this.scoreForNextLevel = 1000;

    MineShaft.score = this.score;
	this.hazardHits = 0.0;

	--Speed Boost
	this.boostAmt = 0.0; --strength of boost
	this.boostDuration = 0.0; --length of boost remaining
    this.boostSpeed = 0.0; --actual quantity added to speed
end

function MineShaft.OnEnable()
    math.randomseed(os.time());
    MineShaft.SpawnMoreRails();

    print("Enabling Mineshaft");
end

function MineShaft.UpdateBoost(dt)
	if this.boostDuration == 0 or this.boostAmt == 0 then
		return;
	end

	this.boostDuration = this.boostDuration - dt;

	if this.boostDuration < 0 then
		this.boostDuration = 0;
		this.boostAmt = 0;
	end
    
    this.boostSpeed = this.boostAmt * math.sqrt(this.boostDuration);

end

function MineShaft.GetRandomHazardRail()
    local rand = math.random();
    if (rand > 0.0) then
        return this.brokenPrefab;
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
	        MineShaft.SpawnRail(columns[i], z - 6.0, MineShaft.GetRandomHazardRail());
            numHazards = numHazards - 1;
        else
	        MineShaft.SpawnRail(columns[i], z - 6.0, MineShaft.GetRandomSafeRail());
        end
    end

    --spawn secondary row of rails
    MineShaft.SpawnRail(-1, z, this.railPrefab);
	MineShaft.SpawnRail(0, z, this.railPrefab);
	this.lastRailSpawned = MineShaft.SpawnRail(1, z, this.railPrefab);

	-- wall section
	MineShaft.SpawnWall(z - 6.0, this.wallPrefab);
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
	
	this.score = this.score + (this.moveSpeed * dt);

    --Update score ui-text with score value
    this.GameObject:GetTextComponent().Text = "Score: " .. math.floor(this.score);

    if this.score > this.scoreForNextLevel then
        this.level = this.level + 1;
        this.scoreForNextLevel = this.scoreForNextLevel + this.level * 1000;
        this.moveSpeed = this.moveSpeed + 5;
    end

    MineShaft.SpawnMoreRails();

end

function MineShaft.OnDisable()
	
end


function MineShaft.OnDestroy()
	this.railPrefab:MarkDelete();
	this.gemPrefab:MarkDelete();
	this.brokenPrefab:MarkDelete();
	this.wallPrefab:MarkDelete();
	this.speedBoostPrefab:MarkDelete();

end
