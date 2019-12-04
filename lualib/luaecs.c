#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "ecs.h"

// {{{ util

ECS* ecs_ptr(lua_State* L, int index) {
    lua_getfield(L, index, "__ptr");
    ECS* ecs = lua_touserdata(L, -1);
    lua_pop(L, 1);
    return ecs;
}

// }}}

static const struct luaL_Reg functions[] = {
    { NULL, NULL },
};

// {{{ initialization

ECS* initialize_ecs(lua_State* L)
{
    int n_components = luaL_len(L, 1);
    ECS_Component** components = calloc(n_components, sizeof(ECS_Component*));

    int i = 0;
    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
        components[i] = ecs_component_new(lua_tostring(L, -2));
        lua_pushnil(L);
        while (lua_next(L, 1) != 0) {
            int size = 0;
            ECS_Type type = ecs_component_type_translate(lua_tostring(L, -1), &size);
            ecs_component_add_field(components[i], lua_tostring(L, -2), type, size);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

    return ecs_new(components, n_components);
}

static int libecs_free(lua_State* L)
{
    ecs_free(ecs_ptr(L, 1));
    return 0;
}

static int libecs_new(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    
    // initialize
    ECS* ecs = initialize_ecs(L);
    luaL_setfuncs(L, functions, 0);

    // create table
    lua_newtable(L);
    lua_pushlightuserdata(L, ecs);
    lua_setfield(L, -2, "__ptr");

    // add destructor
    lua_newtable(L);
    lua_pushcfunction(L, libecs_free);
    lua_setfield(L, -2, "__gc");
    lua_setmetatable(L, -2);

    return 1;
}

// }}}

// {{{ library setup

static const struct luaL_Reg ecslib[] = {
    { "new", libecs_new },
    { NULL, NULL },
};

int luaopen_ecs(lua_State* L)
{
    luaL_newlib(L, ecslib);
    return 1;
}

// }}}

// vim: st=4:sts=4:sw=4:expandtab:foldmethod=marker
