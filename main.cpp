#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <LuaStateManager.hpp>
#include <chrono>

class Timer 
{
   template<typename T>
    decltype(auto) GetDuration() const noexcept
    {
        return std::chrono::duration_cast<T>(std::chrono::high_resolution_clock::now() - m_timePoint);
    }

public:
	void SetTimer() noexcept
    {
        m_timePoint = std::chrono::high_resolution_clock::now();
    }

	[[nodiscard]]
	std::int64_t GetTimeNano() const noexcept
    {
        return GetDuration<std::chrono::nanoseconds>().count();
    }

	[[nodiscard]]
	std::int64_t GetTimeMicro() const noexcept
    {
        return GetDuration<std::chrono::microseconds>().count();
    }

	[[nodiscard]]
	std::int64_t GetTimeMili() const noexcept
    {
        return GetDuration<std::chrono::milliseconds>().count();
    }

	[[nodiscard]]
	std::int64_t GetTimeSecond() const noexcept
    {
        return GetDuration<std::chrono::seconds>().count();
    }

private:
	std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::nanoseconds> m_timePoint;
};

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
/*
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

    std::cout << "\n\n\n";
    */

    Timer timer{};

    std::vector<Character> test;
    const size_t charNum = 100'000;
    test.reserve(charNum);

    for(size_t index = 0u; index < charNum; ++index)
    {
        Character chara{stateMan, static_cast<std::int32_t>(index)};
        chara.SetScript("../LuaSrc/Elf.lua");
        test.emplace_back(std::move(chara));
    }

    timer.SetTimer();

    for(Character& chara : test)
        chara.LoadScript().Update().Health().Type();
    
    std::cout << "Time taken to load " << charNum << " scripts is " << timer.GetTimeMili() << "ms\n";

    return 0;
}