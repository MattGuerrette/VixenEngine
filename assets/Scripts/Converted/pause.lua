
function pause.OnInit()

end

function pause.OnEnable()
	 Scene.OpenScene("scene1");
	 Scene.ShowScene("scene1");
	 Scene.PauseScene("scene1");
     Scene.SetOrder("pause", 1);
end

function pause.Update(dt)
	
    if Input.KeyPressSingle(IKEY.ESC) or Input.KeyPressSingle(IKEY.F2) then
        Game.Exit();
    end

	if (Input.ControllerButtonPressSingle(IBUTTON.A, 0) or Input.KeyPressSingle(IKEY.SPACE)) then
        Scene.HideScene("pause");
        Scene.PauseScene("pause");
		Scene.UnpauseScene("scene1");
	end

end

function pause.OnDisable()

end

function pause.OnDestroy()

end