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

LuaStateMan& LuaStateMan::LoadGlobal(const std::string& varName) noexcept
{
    lua_getglobal(m_state, varName.c_str());

    return *this;
}

std::string LuaStateMan::GetString(std::int32_t index) const noexcept
{
    if (lua_isstring(m_state, index))
        return lua_tostring(m_state, index);

    return std::string{};
}

bool LuaStateMan::OpenScript(const std::string& filePath) const noexcept
{
    return CheckError(luaL_dofile(m_state, filePath.c_str()));
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