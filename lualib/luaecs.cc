#include <lua.hpp>

#include <cstring>

#include <map>
#include <string>

extern "C" {
    int luaopen_ecs(lua_State* L);
}

#include "mm_ecs.hh"

// {{{ util

ECS* ecs_ptr(lua_State* L, int index)
{
    return *reinterpret_cast<ECS**>(lua_touserdata(L, 1));
}

// }}}

const std::map<std::string, lua_CFunction> functions = {
};

// {{{ entity



// }}}

// {{{ initialization / destruction

ECS* initialize_ecs(lua_State* L)
{
    Components components;

    lua_pushnil(L);
    while (lua_next(L, -2) != 0) {
        const char* comp_name = lua_tostring(L, -2);
        components.emplace(comp_name, Parameters {});
        lua_pushnil(L);
        while (lua_next(L, -2) != 0) {
            components[comp_name].emplace(lua_tostring(L, -2), ECS_Type { lua_tostring(L, -1) });
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

    return new ECS(components);
}

static int ecs_index(lua_State* L)
{
    auto it = functions.find(lua_tostring(L, -1));
    if (it != functions.end()) {
        lua_pushcfunction(L, it->second);
        return 1;
    } else {
        luaL_error(L, "Invalid method '%s'", lua_tostring(L, -1));
        return 0;
    }
}

static int ecs_free(lua_State* L)
{
    delete ecs_ptr(L, 1);
    return 0;
}

static int libecs_new(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);

    *reinterpret_cast<ECS**>(lua_newuserdata(L, sizeof(ECS*))) = initialize_ecs(L);

    lua_newtable(L);
    lua_pushcfunction(L, ecs_free); lua_setfield(L, -2, "__gc");
    lua_pushcfunction(L, ecs_index); lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2);

    return 1;
}

// }}}

// {{{ library

static int libecs_index(lua_State* L)
{
    const char* key = lua_tostring(L, 2);
    if (strcmp(key, "new") == 0) {
        lua_pushcfunction(L, libecs_new);
        return 1;
    } else {
        luaL_error(L, "'%s': invalid method", key);
        return 0;
    }
}

int luaopen_ecs(lua_State* L)
{
    lua_newuserdata(L, 0);
    
    // functions
    lua_newtable(L);
    lua_pushcfunction(L, libecs_index); lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2);

    return 1;
}

// }}}

// vim: st=4:sts=4:sw=4:expandtab:foldmethod=marker
