
function GameOver.OnInit()

end

function GameOver.OnEnable()
     Scene.SetOrder("GameOver", 2);
end

function GameOver.Update(dt)
	
	if Input.ControllerButtonPressSingle(IBUTTON.A, 0) or Input.KeyPressSingle(IKEY.SPACE) then
        print("Reloading scene 1");
        --Scene.HideScene("GameOver");
		Scene.ReloadScene("scene1");
        Scene.HideScene("GameOver");
        Scene.PauseScene("GameOver");
        --Scene.ShowScene("scene1");
	end

end

function GameOver.OnDisable()

end

function GameOver.OnDestroy()

end