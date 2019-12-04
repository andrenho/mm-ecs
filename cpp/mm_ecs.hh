#ifndef MM_ECS_HH_
#define MM_ECS_HH_

#include <cstdint>

#include <any>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include <iostream>
#define D(...) __VA_ARGS__

enum ECS_TypeDef { U8, I64, Float, String, Ptr };

struct ECS_Type {
    ECS_TypeDef type_def;
    bool        optional;
    uint16_t     size;

    ECS_Type(std::string const& named_type) {
        // TODO
    }

    ECS_Type(ECS_TypeDef type_def) 
        : type_def(type_def), optional(false), size(0) {}
    ECS_Type(ECS_TypeDef type_def, bool optional) 
        : type_def(type_def), optional(optional), size(0) {}
    ECS_Type(ECS_TypeDef type_def, bool optional, uint16_t size) 
        : type_def(type_def), optional(optional), size(size) {}
    ECS_Type(const char* named_type) 
        : ECS_Type(std::string(named_type)) {}
};

typedef std::map<std::string, ECS_Type> Parameters;
typedef std::map<std::string, Parameters> Components;
typedef std::pair<std::string, std::any> Value;
typedef uint64_t Entity;

class EntityIterator {
public:
    EntityIterator begin() { return EntityIterator(); }
    EntityIterator end() { return EntityIterator(); }

    EntityIterator& operator++() { return *this; }
    bool            operator!=(EntityIterator const&) { return false; }
    Entity          operator*() { return 0; }
};

class EventIterator {
public:
    EventIterator begin() { return EventIterator(); }
    EventIterator end() { return EventIterator(); }

    EventIterator& operator++() { return *this; }
    bool           operator!=(EventIterator const&) { return false; }
    void*          operator*() { return 0; }
};

class ECS {
public:
    ECS(Components const& components) : components(components) {
        D(std::cout << "ECS initialized.\n");
    }

    ~ECS() {
        D(std::cout << "ECS finalized.\n");
    }

    //
    // entities
    //

    Entity add(std::string const& pool, std::vector<std::string> const& tags = {}, std::string const& name = "") {
        (void) pool; (void) tags; (void) name; // TODO
        Entity entity = entity_counter;
        D(std::cout << "Entity " << entity << " added.\n";)
        return entity_counter++;
    }

    Entity add(std::vector<std::string> const& tags = {}, std::string const& name = "") { 
        return add("", tags, name);
    }

    std::string entity_tostring(Entity entity) const {
        (void) entity;
        return "not implemented";  // TODO
    }

    EntityIterator entities(std::vector<std::string> const& components, std::vector<std::string> const& tags = {}) const {
        (void) components; (void) tags;
        return EntityIterator();
    }

    // 
    // components
    //
    
    void set_component(Entity entity, std::string const& name, std::vector<Value> const& values) {
        (void) entity; (void) name; (void) values; // TODO
        for (auto const& value : values)
            set_component_value(entity, name, value.first, value.second);
    }

    std::any get_component_value(Entity entity, std::string const& component, std::string const& field) {
        (void) entity; (void) component; (void) field;
        return 0;
    }

    void set_component_value(Entity entity, std::string const& component, std::string const& field, std::any value) {
        (void) entity; (void) component; (void) field; (void) value; // TODO
        D(std::cout << "Component " << component << " field " << field << " created for entity " << entity << ".\n";)
    }

    std::string component_tostring(Entity entity, std::string const& component) const {
        (void) entity; (void) component;
        return "not implemented";  // TODO
    }

    // 
    // events
    //

    void add_event(std::string const& name, void* event) {
        (void) name; (void) event;  // TODO
        D(std::cout << "Event added\n";)
    }

    EventIterator events(std::string const& tag) const {
        (void) tag;
        return EventIterator();
    }

    void clear_event_queue() {
        D(std::cout << "Event queue cleared\n";)
    }

    // 
    // systems
    //

    template <typename F>
    void run_mutable(F f) {
        f(*this);   // TODO
    }

    void run_mt(std::vector<std::function<void(ECS const&)>> fs) const {
        for (auto f: fs)
            f(*this);
    }

    void join() {}

private:
    Components components;
    Entity entity_counter = 0;
};

#endif

// vim: st=4:sts=4:sw=4:expandtab
