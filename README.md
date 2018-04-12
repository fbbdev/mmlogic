# MultiMedia Logic

A MultiMedia Logic Design System.

This is a fork of the good old [MultiMedia logic](http://www.softronix.com/logic.html) app
by George Mills of [Softronics](http://www.softronix.com).

## Changes

The source has been update to build on Visual Studio 2015 and some customization have
been added:
  * **Shared memory mode:** memory blocks referring to the same file can optionally share
    their run-time storage. Writes on one block will then be visible from the others.
