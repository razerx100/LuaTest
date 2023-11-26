#include <LuaStateManager.hpp>
#include <fstream>

LuaStateMan::LuaStateMan() : m_state{ luaL_newstate() } {}

LuaStateMan::~LuaStateMan()
{
    lua_close(m_state);
}

lua_State* LuaStateMan::Get() const noexcept
{
    return m_state;
}

void LuaStateMan::LoadGlobal(std::string_view varName) const noexcept
{
    lua_getglobal(m_state, std::data(varName));
}

std::string LuaStateMan::GetString(std::int32_t index) const noexcept
{
    if (lua_isstring(m_state, index))
        return lua_tostring(m_state, index);

    return std::string{};
}

bool LuaStateMan::OpenScript(std::string_view filePath) const noexcept
{
    return CheckError(luaL_dofile(m_state, std::data(filePath)));
}

bool LuaStateMan::CheckError(int errorCode) const noexcept
{
    if (errorCode != LUA_OK)
    {
        // TO DO: Change it into something better.
        static std::ofstream log{
            "ErrorLog.txt", std::ios_base::app | std::ios_base::ate
        };
        log << GetString(-1) << std::endl;

        return false;
    }

    return true;
}