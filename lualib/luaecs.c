#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static const struct luaL_reg ecslib = {
    { NULL, NULL },
};


int luaopen_ecs(lua_State* L)
{
    luaL_register(L, "ecs", ecslib);
    return 1;
}

// vim: st=4:sts=4:sw=4:expandtab
