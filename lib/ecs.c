#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>

#include "ecs.h"

// {{{ components

typedef struct ECS_Component {
    const char* name;
} ECS_Component;

ECS_Component*
ecs_component_new(const char* name)
{
    ECS_Component* c = calloc(1, sizeof(ECS_Component));
    c->name = strdup(name);
    printf("new component %s\n", name);
    return c;
}

void
ecs_component_add_field(ECS_Component* component, const char* name, ECS_Type type, int size)
{
    // TODO
}

ECS_Type
ecs_component_type_translate(const char* type, int* size)
{
    return ECS_U8;  // TODO
}

// }}}

// {{{

typedef struct ECS {
    ECS_Component** components;
    int             n_components;
} ECS;

ECS*
ecs_new(ECS_Component* components[], int n_components)
{
    ECS* ecs = calloc(1, sizeof(ECS));
    ecs->components = components;
    ecs->n_components = n_components;
    printf("ECS created %p.\n", ecs);
    return ecs;
}

void ecs_free(ECS* ecs)
{
    printf("ECS free %p\n", ecs);
    // TODO
    free(ecs);
}

// }}}

// vim: st=4:sts=4:sw=4:expandtab:foldmethod=marker
