Extending the Simple CPP Game Engine
=====================================

Engine Architecture
--------------------
Simple CPP Game is implemented with a `Entity Component System <https://en.wikipedia.org/wiki/Entity_component_system>`_ that handles
complex behavior of the actors in the game world. Rather than traditional inheritance, where game objects have an "is-a" relationship
to classes that provide game behavior, Entity Component Systems define game objects that have a "has-a" relationship to classes (called
Systems) that provide game behavior. This creates a much more modular and scalable framework for game behavior (that is supported even
by languages that disallow multiple inheritance) without sacrificing the performance and ecosystem of a popular language like C++. In
essence, Entity Component Systems bring the best parts of `Duck Typing <https://en.wikipedia.org/wiki/Duck_typing>`_ to the part of the
program that needs it without sacrificing the value of static typing elsewhere in the codebase.

Adding New Behavior
--------------------

The Entity Component System is managed by the :ref:`EntityEngine class<EntityEngine>`. The game creates and maintains a single instance
of this class throughout the lifetime of the game. Behavior can be added to the game by defining new :ref:`Components<Entities and Components>`
and :ref:`Systems<Entity Systems>` that control the desired new behavior and adding them to the engine.

Entities and Components
~~~~~~~~~~~~~~~~~~~~~~~~

The primary objects in an Entity Component System are the :ref:`entities<Entity>` and :ref:`components<Component>`.

:ref:`Entities<Entity>` are little more than "bags" of components - groupings of characteristics that are together treated as a single entity (hence the name). When extending
the functionality of an Entity Component System, new entity types are not defined; instead, new components are created that entities
can own.

:ref:`Components<Component>` serve as components (hence, the name) of entities. They mark which :ref:`systems<Entity Systems>` should act
on the entity and store any state data related to the systems they are built for. For example, the
`RenderComponent <../doxygen/html/classRenderComponent.html>`_ stores sprite data and marks an entity as belonging to the
`RenderSystem <../doxygen/html/classRenderSystem.html>`_. Custom components can be anything from color information to ball spin to
paddle speed. Once a custom Component has been defined, simply `add <../doxygen/html/classEntity.html#a72c8542219615793e0610617a7e5f3f4>`_
it to the entities it applies to and define a system to act on it. Speaking of systems...

Entity Systems
~~~~~~~~~~~~~~

Entity Systems are implementations of the :ref:`EntitySystem class<EntitySystem>`. Designing an Entity System requires two major
components:

**1. Define the Entities the System Acts on**

Each Entity System defines some behavior that components that match its criteria and "quack like a duck" will exhibit. In Simple Cpp
Game's implementation, an `EntityFamily <../doxygen/html/classEntityFamily.html>`_ is used to filter the entities in the engine to
those that are appropriate for a given system. A custom system should pass this family to the appropriate constructor of
:ref:`EntitySystem<EntitySystem>` or whatever subclass thereof it inherits from (such as 
`IteratingSystem <../doxygen/html/classIteratingSystem.html>`_). The simplist implementation of `EntityFamily <../doxygen/html/classEntityFamily.html>`_
(and the only one implemented in Simple Cpp Game at this time) is the `ComponentFamily <../doxygen/html/classComponentFamily.html>`_,
which allows the system to specify a set of Component each entity it will process must have.

**2. Define the Behavior of those Entities**

Each Entity System defines one class of behavior for its constituent entities. In the base game, `VelocitySystem <../doxygen/html/classVelocitySystem.html>`_
defines how position updates from velocity, `PlayerInputSystem <../doxygen/html/classPlayerInputSystem.html>`_ defines how the player
paddle moves given input, etc. Each custom system should implement a similarly narrow scope of functionality - this is what gives
the Entity Component System its flexibility and modularity. Custom systems might add score counters, terrain, or the next new feature
that no Pong clone has ever seen before.

The most common way to implement an Entity System mis to inherit from `IteratingSystem <../doxygen/html/classIteratingSystem.html>`_.
This allows the developer to just provide a `ComponentFamily <../doxygen/html/classComponentFamily.html>`_ and an implementation of
`the process() method <../doxygen/html/classIteratingSystem.html#a3fb21f26cc10e9ec82834ee86dc87b6c>`_ that processes one entity at a time.

Conclusion
-----------

Component Entity Systems are an incredible piece of technology that bring the modularity of dynamically typed languages to the statically
typed environments needed for performance in game development, allowing for modular systems, efficient code development, and performant
end solutions. With the steps here, you'll be extending the Simple Cpp Game engine to be writing custom functionality in no time!