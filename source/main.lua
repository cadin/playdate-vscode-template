import "CoreLibs/graphics"

local gfx <const> = playdate.graphics

function playdate.update() 
    gfx.clear()
    gfx.drawText("Hello World", 20, 20)
end