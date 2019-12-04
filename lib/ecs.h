#ifndef ECS_H_
#define ECS_H_

#include <stdlib.h>

typedef struct ECS ECS;
typedef struct ECS_Component ECS_Component;

typedef enum ECS_Type {
    ECS_U8,     ECS_U8_OPT,
    ECS_I64,    ECS_I64_OPT,
    ECS_FLOAT,  ECS_FLOAT_OPT,
    ECS_STRING, ECS_STRING_OPT,
    ECS_PTR,    ECS_PTR_OPT,
} ECS_Type;

ECS_Component* ecs_component_new(const char* name);
void           ecs_component_add_field(ECS_Component* component, const char* name, ECS_Type type, int size);
ECS_Type       ecs_component_type_translate(const char* type, int* size);

ECS* ecs_new(ECS_Component** components, int n_components);
void ecs_free(ECS* ecs);

#endif

// vim: st=4:sts=4:sw=4:expandtab:foldmethod=marker
