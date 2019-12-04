#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "ecs.h"

static const struct luaL_Reg functions[] = {
    { NULL, NULL },
};

// {{{ initialization

ECS_Type translate_component_type(const char* type, int* size) {
    // TODO
}

ECS* initialize_ecs(lua_State* L)
{
    int n_components = lua_len(L, 1);
    ECS_Component* components = calloc(n_components, sizeof(ECS_Component));

    int i = 0;
    lua_pushnil(L);
    while (lua_next(L, 1) != 0) {
        components[i] = ecs_component_new(lua_tostring(L, -2));
        lua_pushnil(L);
        while (lua_next(L, 1) != 0) {
            int size = 0;
            type = translate_component_type(lua_tostring(L, -1), &size);
            ecs_component_add_field(components[i], lua_tostring(L, -2), type, size);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

    return ecs_new(components, n_components);
}

static int ecs_new(lua_State* L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
    
    ECS* ecs = initialize_ecs(L);
    luaL_setfuncs(L, functions, 0);

    lua_newtable(L);
    return 1;
}

// }}}

// {{{ library setup

static const struct luaL_Reg ecslib[] = {
    { "new", ecs_new },
    // TODO - free??
    { NULL, NULL },
};

int luaopen_ecs(lua_State* L)
{
    luaL_newlib(L, ecslib);
    return 1;
}

// }}}

// vim: st=4:sts=4:sw=4:expandtab:foldmethod=marker
