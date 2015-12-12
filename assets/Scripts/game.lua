
function game.OnInit()
	
end

function game.OnEnable()
   
end

function game.Update(dt)
  
    if Input.KeyPressSingle(IKEY.ESC) or Input.KeyPressSingle(IKEY.F2) then
        Game.Exit();
    end

--    if Input.KeyPressSingle(IKEY.P) then
--        Scene.ShowScene("pause");
--        Scene.UnpauseScene("pause");
--        Scene.PauseScene("scene1");
--        --Scene.SetOrder("pause", 1);
--    end

end

function game.OnDisable()
	
end

function game.OnDestroy()
	
end
