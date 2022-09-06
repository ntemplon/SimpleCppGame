Lifecycle of the Simple Cpp Game
================================

.. image:: img/SimpleCppGameLifecycle.svg

The lifecycle of the Simple Cpp Game is governed by a state machine (implemented with `the StateMachine class <./doxygen/html/classStateMachine.html>`_),
approximated in the above UML state machine diagram. The game transitions through the various stages of the game (main menu, gameplay, etc.) in response
to actions taken by the user and the natural evolution of the program state.