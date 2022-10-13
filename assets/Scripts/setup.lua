

function BindGlobalThisToObject(scriptName, objectID)
	_G.this = _G[scriptName].hash[objectID];
end