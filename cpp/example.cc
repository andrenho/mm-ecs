#include <mm_ecs.hh>

#include <iostream>

class Object {};

int main()
{
    // setup
    ECS ecs({
        { "position", {
            { "x", "float" },
            { "y", "float" },
            { "dir", "float?" },
        } },
        { "info", {
            { "name", "string_20" },
            { "age", "u8" },
            { "things", "object?" }
        } },
    });

    // setup entities
    auto e1 = ecs.add({"mytag"}, "hero");
    auto e2 = ecs.add();

    // setup components
    ecs.set_component(e1, "position", {
        { "x", 4.0 },
        { "y", 5.0 },
        { "dir", 40 }
    });
    ecs.set_component(e1, "info", {
        { "name", "Hello" },
        { "age", 42 },
        { "things", new Object() }
    });

    ecs.set_component(e2, "position", {
        { "x", 35.0 },
        { "y", -24.5 },
    });

    // events

    struct Event {
        float value;
        Event(float value) : value(value) {}
    };
    ecs.add_event("inc_x", new Event { 1.0 });

    // mutable functions

    ecs.run_mutable([](ECS& ecs) {
        for (auto const& event : ecs.events("inc_x")) {
            for (auto entity : ecs.entities({ "position" })) {
                int value = std::any_cast<int>(ecs.get_component_value(entity, "position", "x"));
                Event* e = static_cast<Event*>(event);
                ecs.set_component_value(entity, "position", "x", value + e->value);
            }
        }
    });

    ecs.clear_event_queue();

    // multithreaded

    auto show_positions = [&](ECS const& ecs) {
        for (auto entity : ecs.entities({}, { "mytag" })) {
            // ecs.set_component_value(e2, "position", "x", 0);  // this is an error
            std::cout << ecs.entity_tostring(entity) << "\n";
        }
    };

    auto show_infos = [](ECS const& ecs) {
        for (auto entity : ecs.entities({ "info" })) {
            std::cout << ecs.component_tostring(entity, "info") << "\n";
        }
    };

    ecs.run_mt({ show_positions, show_infos });
    ecs.join();
}

// vim: st=4:sts=4:sw=4:expandtab
