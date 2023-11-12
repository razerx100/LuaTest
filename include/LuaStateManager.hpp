#ifndef LUA_STATE_MANAGER_HPP_
#define LUA_STATE_MANAGER_HPP_
#include <cstdint>
#include <string>
#include <concepts>

#include <lua.hpp>

template<typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

class LuaStateMan
{
public:
    LuaStateMan();
    ~LuaStateMan();

    [[nodiscard]]
    lua_State* Get() const noexcept;

    LuaStateMan& LoadGlobal(const std::string& varName) noexcept;

    [[nodiscard]]
    std::string GetString(std::int32_t index = -1) const noexcept;

    template<Arithmetic T>
    [[nodiscard]]
    T GetNumber(std::int32_t index = -1) const noexcept
    {
        if (lua_isnumber(m_state, index))
            return static_cast<T>(lua_tonumber(m_state, index));

        return T{};
    }

    bool OpenScript(const std::string& filePath) const noexcept;

private:
    bool CheckError(int errorCode) const noexcept;

private:
    lua_State* m_state;
};
#endif