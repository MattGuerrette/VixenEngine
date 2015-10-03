function railspawn.OnInit()
	
end

function railspawn.OnEnable()
	
	local numRails = 30;

	local go = this.GameObject;
	
	local transform = go:GetTransform();


	local railPrefab = Prefab.Load("rail.pfb");


	for i=0, numRails, 1
	do
		local rail = railPrefab:CreateObject();

		rail:GetTransform().Position = transform.Position + Vector3(0.0, 0.0, 0.0 + (7.5 * i));
	end

	for i=0, numRails, 1
	do
		local rail = railPrefab:CreateObject();

		rail:GetTransform().Position = transform.Position + Vector3(-5, 0.0, 0.0 + (7.5 * i));
	end
	

	for i=0, numRails, 1
	do
		local rail = railPrefab:CreateObject();

		rail:GetTransform().Position = transform.Position + Vector3(5, 0.0, 0.0 + (7.5 * i));
	end

	--local rail2 = railPrefab:CreateObject();
	
end

function railspawn.Update(dt)

	

end

function railspawn.OnDisable()
	
end

function railspawn.OnDestroy()
	
end
