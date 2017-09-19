--2048 Random
while true do
  rand = math.random(0,3)
  if(rand == 0)then
    joypad.set({Up=1},1)
    joypad.set({Up=1},0)
    end
  if(rand == 1)then
  	nrand = math.random(0,4)
  	if(nrand == 1)then
    	joypad.set({Down=1},1)
    	joypad.set({Down=1},0)
    	end
    end
  if(rand == 2)then
    joypad.set({Left=1},1)
    joypad.set({Left=1},0)
    end
  if(rand == 3)then
  	nrand = math.random(0,100)
  	if(nrand == 98)then
    	joypad.set({Right=1},1)
    	joypad.set({Right=1},0)
    	end
    end
	emu.frameadvance()
end