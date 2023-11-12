#include <iostream>
#include <LuaStateManager.hpp>

struct Data
{
    std::string name;
    std::uint32_t age;
};

int main()
{
    LuaStateMan stateMan{};

    Data data{};
    if (stateMan.OpenScript("../LuaSrc/test.lua"))
    {
        data.name = stateMan.LoadGlobal("Name").GetString();
        data.age  = stateMan.LoadGlobal("Age").GetNumber<std::uint32_t>();
    }

    std::cout << "Name = " << data.name << " Age = " << data.age << std::endl;

    return 0;
}