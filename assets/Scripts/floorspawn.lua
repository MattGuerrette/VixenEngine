function floorspawn.OnInit()
	
end

function floorspawn.OnEnable()
	
	local numfloors = 4;

	local go = this.GameObject;
	
	local transform = go:GetTransform();


	local floorPrefab = Prefab.Load("floor.pfb");


	for i=0, numfloors, 1
	do
		local floor = floorPrefab:CreateObject();

		floor:GetTransform().Position = transform.Position + Vector3(0.0, 0.0, 0.0 + (50 * i));
	end

	
end

function floorspawn.Update(dt)

	

end

function floorspawn.OnDisable()
	
end

function floorspawn.OnDestroy()
	
end