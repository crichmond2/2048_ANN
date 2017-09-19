 compare_numbers = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000 }
 values ={0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001,0x0001}
 list = {0x004c,0x004d,0x004e,0x004f,0x0050,0x0051,0x0052,0x0053,0x0054,0x0055,0x0056,0x0057,0x0058,0x0059,0x005a,0x005b}
 emptyspaces = {0x000c,0x000d,0x000e,0x000f,0x0010,0x0011,0x0012,0x0013,0x0014,0x0015,0x0016,0x0017,0x0018,0x0019,0x001a,0x001b}
 compare_spaces = {0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000 }


local list2 = {}
count = 0

while true do

  for i=1,16,1 do
    values[i] = memory.readbyte(emptyspaces[i])
    if(compare_numbers[i]~=values[i])then
	    compare_numbers[i] = values[i]
	    written = 1	
      list2[i] = compare_numbers[i]
      end
  end

  if(count > 50)then --if 50 frames pass

    count = 0

    if(written == 1)then
      written = 0
  	  change = io.open("Changes.txt","w")
  	  for k,v in pairs(list2) do
  		  change:write(k," ",v,"\n")
  		  end
    	  change:close()
    	  --end

        f = io.open("commands.txt")
        mod = f:read()
        modified = mod
        f:close()

        if(modified == "up")then
          joypad.set({Up=1},1)
          joypad.set({Up=1},0)
          end
        if(modified == "down")then
          joypad.set({Down=1},1)
          joypad.set({Down=1},0)
          end
        if(modified == "left")then
          joypad.set({Left=1},1)
          joypad.set({Left=1},0)
          end
        if(modified == "right")then
          joypad.set({Right=1},1)
          joypad.set({Right=1},0)
          end

    end
  end
  count = count + 1


  emu.frameadvance()
  end
