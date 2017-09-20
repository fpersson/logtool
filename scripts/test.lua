--
-- Created by IntelliJ IDEA.
-- User: fredrik
-- Date: 2017-09-20
-- Time: 22:00
-- To change this template use File | Settings | File Templates.
--

-- This function will be called from C++
function parseString(msg)
    --return msg
    --return msg .. " [" .. Text.Red .. "OK" .. Text.Default .. "]"
    if string.match(msg, "Sensors") then
        return Text.Red .. TextFormat.Bold ..  msg .. TextFormat.Reset .. Text.Default
    elseif string.match(msg, "PlayCommon") then
        return TextFormat.Bold ..  msg .. TextFormat.Reset
    else
        return msg
    end
end


