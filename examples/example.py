import ecs

# setup

E = ecs.ECS({
    'position': {
        'x': 'float',
        'y': 'float',
        'dir': 'u8?',
    },
    'info': {
        'name': 'string_20',
        'age': 'u8',
        'things': 'table?'
    }
})

# setup entities

e1 = E.add(tags=['mytag'], name='hero')
e2 = E.add()

e1.position = { 'x': 4.0, 'y': 5.0, 'dir': 40 }
e1.info = { 'name': 'Hello', 'age': 42, things: [ 3, 4, 5 ] }

e2.position = { 'x': 35.0, 'y': -24.5 }

# add event

E.add_event('inc_x', { 'value': 1.0 })

# mutable functions

def run_events(E):
    for event in E.events('inc_x'):
        for entity in E.entities(components=['position']):
            entity.x += event['value']
E.run_mutable(run_events)

E.clear_event_queue()

# multithreaded

def show_positions(E):
    for entity in E.entities(tags=['mytag']):
        print(entity)
        # entity.x = 0  # this is an error

def show_infos(E):
    for entity in E.entities(components=['info']):
        print(info)
    
E.run_mt(show_positions, show_infos)
