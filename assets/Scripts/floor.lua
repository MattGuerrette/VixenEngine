
_G.this = _G.floor.hash.floor1;

function floor.Start()
	print('Start called');
end

function floor.Update(dt)
	go = this.GameObject;
	transform = go:GetTransform();
end


function floor.Stop()
	print('Stop called');
end