local type = "Human"
local healthChange = 0

function Update()
    healthChange = -9
end

function GetHealth(health)
    return health + healthChange
end

function GetType()
    return type
end