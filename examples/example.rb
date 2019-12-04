require 'ecs'

# setup

$ecs = ECS.new({
  :position => {
    :x => :float,
    :y => :float,
    :dir => :u8?,
  },
  :info => {
    :name => :string,
    :age => :u8,
    :things => :object?
  }
})

# setup entities

e1 = $ecs.add(tags: [:mytag], name: :hero)
e2 = $ecs.add

e1.position = { :x => 4.0, :y => 5.0, :dir => 40 }
e1.info = { :name => 'Hello', :age => 42, :things => [ 3, 4, 5 ] }

e2.position = { :x => 35.0, :y => -24.5 }

# add event

$ecs.add_event :inc_x, { :value => 1.0 }

# mutable functions

$ecs.run_mutable do |ecs|
  ecs.events(:inc_x) do |ecs, event|
    ecs.entities([:position]) { |ecs, entity| entity.position.x += event[:value] }
  end
end

$ecs.clear_event_queue!

# multithread

def show_positions(ecs)
  ecs.entities(tags: [:mytag]) do |ecs, entity|
    # entity.x = 0  # this is an error
    p entity
  end
end

def show_infos(ecs)
  ecs.entities([:info]) { |ecs, entity| p entity.info }
end

$ecs.run_mt :show_positions, :show_infos
