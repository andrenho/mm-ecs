ecs = require 'ecs'

local components = {
  position = {
    x   = 'float',
    y   = 'float'
    dir = 'uint8?'
  }
  info = {
    name   = 'string',
    things = '*?'
  }
}

E = ecs.ECS.new(components)

e1 = E:add('mytag')
e2 = E:add()

e1.position = { x = 4.0, y = 5.0, dir = 40 }
e1.info = { name = 'Hello', age = 42, things = { 3, 4, 5 } }

e2.position = { x = 35.0, y = -24.5 }

E:run_mutable(function(E)
  E:foreach('position', function(E, entity)
    entity.position.x = entity.position.x + 1.0
  end)
end)

-- vim: st=2:sts=2:sw=2:expandtab
