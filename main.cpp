#include <iostream>
#include <string>
#include <memory>
#include <LuaStateManager.hpp>

class Character
{
public:
    Character(const LuaStateMan& luaState, std::int32_t health) : m_health{health}, m_luaState{luaState} {}

    Character& SetScript(std::string script) noexcept
    {
        m_scriptPath = std::move(script);

        return *this;
    }

    Character& LoadScript() noexcept
    {
        m_luaState.OpenScript(m_scriptPath);

        return *this;
    }

    Character& Update()
    {
        m_luaState.CallFunctionV("Update");

        return *this;
    }

    Character& Health()
    {
        m_health = m_luaState.CallFunction<decltype(m_health)>("GetHealth", m_health);

        return *this;
    }

    Character& Type()
    {
        m_type = m_luaState.CallFunction<decltype(m_type)>("GetType");

        return *this;
    }

    [[nodiscard]]
    std::int32_t GetHealth() const noexcept
    {
        return m_health;
    }

    [[nodiscard]]
    std::string GetType() const noexcept
    {
        return m_type;
    }

private:
    std::string m_type;
    std::int32_t m_health;
    const LuaStateMan& m_luaState;
    std::string m_scriptPath;
};

int main()
{
    LuaStateMan stateMan{};

    std::cout << "Before Update : \n";

    Character character1{stateMan, 20};
    character1.SetScript("../LuaSrc/Human.lua");

    character1.LoadScript().Health().Type();

    std::cout << "Character 1 Type: " << character1.GetType()
    << " Health: " << character1.GetHealth() << "\n";

    Character character2{stateMan, 18};
    character2.SetScript("../LuaSrc/Elf.lua");

    character2.LoadScript().Health().Type();

    std::cout << "Character 2 Type: " << character2.GetType()
    << " Health: " << character2.GetHealth() << "\n";

    std::cout << "After Update : \n";
    
    character1.LoadScript().Update().Health().Type();

    std::cout << "Character 1 Type: " << character1.GetType()
    << " Health: " << character1.GetHealth() << "\n";

    character2.LoadScript().Update().Health().Type();

    std::cout << "Character 2 Type: " << character2.GetType()
    << " Health: " << character2.GetHealth() << "\n";

    return 0;
}