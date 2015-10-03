function wallspawn.OnInit()
	
end

function wallspawn.OnEnable()
	
	local numWalls = 20;

	local go = this.GameObject;
	
	local transform = go:GetTransform();


	local wallLeftPrefab = Prefab.Load("wallLeft.pfb");
    local wallRightPrefab = Prefab.Load("wallRight.pfb");

	for i=0, numWalls, 1
	do
		local wall = wallLeftPrefab:CreateObject();

		wall:GetTransform().Position = transform.Position + Vector3(-2.0, -1.0, 0.0 + (10 * i));
	end

	for i=0, numWalls, 1
	do
		local wall = wallRightPrefab:CreateObject();

		wall:GetTransform().Position = transform.Position + Vector3(2.0, -1.0, 0.0 + (10 * i));
	end
	
end

function wallspawn.Update(dt)

	

end

function wallspawn.OnDisable()
	
end

function wallspawn.OnDestroy()
	
end
