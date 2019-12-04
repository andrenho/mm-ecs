#include <ecs_ll.h>

struct Event {
    float value;
};

static ECS* initialize_ecs() 
{
    ECS_Components[] comp = {
        ecs_component_new("position"),
        ecs_component_new("info")
    };

    // position
    ecs_component_add_field(comp[0], "x", ECS_FLOAT);
    ecs_component_add_field(comp[0], "y", ECS_FLOAT);
    ecs_component_add_field(comp[0], "dir", ECS_U8_OPT);

    // info
    ecs_component_add_field_str(comp[1], "name", 20, false);
    ecs_component_add_field(comp[1], "age", ECS_U8);
    ecs_component_add_field(comp[1], "things", ECS_PTR_OPT);

    return ecs_new(comp, 2);
}

static void ecs_run_mutable(ECS* ecs, void* data) 
{
}

static void show_positions(ECS* ecs, void* data) 
{
}

static void show_infos(ECS* ecs, void* data) 
{
}

int main() 
{
    ECS* ecs = initialize_ecs();

    int things[] = { 3, 4, 5 };

    // setup entities

    uint64_t e1 = ecs_add("mytag");
    uint64_t e2 = ecs_add(NULL);

    ecs_set_float(ecs, e1, "position", "x", 4.0);
    ecs_set_float(ecs, e1, "position", "y", 5.0);
    ecs_set_u8_opt(ecs, e1, "position", "dir", 40);
    ecs_set_str(ecs, e1, "info", "name", "Hello");
    ecs_set_u8(ecs, e1, "info", "age", 42);
    ecs_set_ptr_opt(ecs, e1, "info", "things", things);

    ecs_set_float(ecs, e2, "position", "x", 35.0);
    ecs_set_float(ecs, e2, "position", "y", -24.5);

    // events

    Event* e = malloc(sizeof(Event));
    e->value = 1.0;

    ecs_add_event(ecs, "inc_x", e, free);

    // mutable functions

    ecs_run_mutable(ecs, change_position_each_event, NULL);

    // multithreaded

    ecs_run_mt(ecs, show_positions, NULL);
    ecs_run_mt(ecs, show_infos, NULL);

    ecs_free(ecs);
}

// vim: st=4:sts=4:sw=4:expandtab
