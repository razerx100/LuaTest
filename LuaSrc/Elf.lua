local type = "Elf"
local healthChange = 0

function Update()
    healthChange = 5
    type = "High Elf"
end

function GetHealth(health)
    return health + healthChange
end

function GetType()
    return type
end