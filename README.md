# MultiMedia Logic

A MultiMedia Logic Design System.

This is a fork of the good old
[MultiMedia logic](http://www.softronix.com/logic.html) app by George Mills
of [Softronics](http://www.softronix.com).

## Changes

The source has been update to build on Visual Studio 2015 and some
customizations have been made:

  * **Code cleanup:** changed some bad or deprecated constructs, fixed most
    warnings, removed outdated assembly code.
  * **Device cleanup:** removed deprecated devices (i.e. CPU port I/O gates)
  * **Shared memory mode:** memory blocks referring to the same file can
    optionally share their run-time storage. Writes on one block will then be
    visible from the others.
  * **Multi-lane signals:** signal senders and receivers can be 1-, 2-, 4-,
    or 8-bits wide. Wiring a wide data bus between pages is now easier.
