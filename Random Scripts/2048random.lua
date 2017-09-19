--2048 Random
while true do
  rand = math.random(0,2)
  if(rand == 0)then
    joypad.set({Up=1},1)
    joypad.set({Up=1},0)
    end
  if(rand == 1)then
  	joypad.set({Down=1},1)
  	joypad.set({Down=1},0)
    end
  if(rand == 2)then
    joypad.set({Left=1},1)
    joypad.set({Left=1},0)
    end
  if(rand == 3)then
    joypad.set({Right=1},1)
    joypad.set({Right=1},0)
    end
	emu.frameadvance()
end