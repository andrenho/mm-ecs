ecs = require 'ecs'

-- setup

E = ecs.new {
  position = {
    x   = 'float',
    y   = 'float',
    dir = 'u8?',
  },
  info = {
    name   = 'string_20',
    age    = 'u8',
    things = 'object?',
  }
}

-- setup entities

e1 = E:add({ tags={ 'mytag' }, name='hero' })
--[[
e2 = E:add()

e1.position = { x = 4.0, y = 5.0, dir = 40 }
e1.info = { name = 'Hello', age = 42, things = { 3, 4, 5 } }

e2.position = { x = 35.0, y = -24.5 }

-- events

E.add_event('inc_x', { value = 1.0 })

-- mutable functions

E:run_mutable(function(E)
  for _, event in E:events('inc_x') do
    for _, entity in E:entities{ components = { 'position' } } do
      entity.position.x = entity.position.x + event.value
    end
  end
end)

E.clear_event_queue()

-- multithreaded

function show_positions(E)
  for _, entity in E:entities{ tags = { 'mytag' } } do
    -- entity.position.x = 0  -- this is an error
    print(entity)
  end
end

function show_infos(E)
  for _, entity in E:entities{ components = { 'info' } } do
    print(entity.info)
  end
end

E:run_mt(show_positions, show_infos)

]]

-- vim: st=2:sts=2:sw=2:expandtab
