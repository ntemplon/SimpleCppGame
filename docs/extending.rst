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

The Entity Component System is managed by the :ref:`EntityEngine<EntityEngine>` class. The game creates and maintains a single instance
of this class throughout the lifetime of the game. Behavior can be added to the game by defining new :ref:`Components<Entities and Components>`
and :ref:`Systems<Entity Systems>` that control the desired new behavior and adding them to the engine.

Entities and Components
~~~~~~~~~~~~~~~~~~~~~~~~


Entity Systems
~~~~~~~~~~~~~~