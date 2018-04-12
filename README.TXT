Release notes for Multimedia Logic 1.6.1

o Changed device properties dialog box tab stop order for:
    Text , Oscillator, Buzzer, Signal Sender and Signal Receiver.
   
Modified Plus device icon on palette to look less like an antenna.

Changed/added keyboard accelerators:
o Selector is now Escape. Escape still works to cancel editing device options.
o Switch is S without having to press Shift.
o Added accelerator "T" for drawing text.
o Added accelerator for Page Up and Page Down to navigate to the Previous and Next pages.
o Added accelerator "8" for the 8 Segment LED (A.K.A. 7 Segment LED).
o Set Color Wires to default to off.
o Added menu accelerator for toggling Color Wires
o Fixed bug where wires that were colored would remain colored upon turning colored wires off.
o Removed unused license code.
o Removed Menu item: Help, Using Help
o Added Menu item: Help, Contents
o Added Undo, Redo, Select All to pop-up menu
o fixed bisect wire bug where half the wire disappeared. If a wire is bisected too many times,
  Bad wires are attempted to be created which gives error message but does not crash. Should we
  protect the user against their trying to bisect a wire a ridiculous number of times?
o implemented ability to undo and redo Bisect Wire. Undo bisect wire can be slow if a large
  number of wires with closely spaced nodes are bisected at once. This is because the
  transaction is per wire bisected, not for all selected wires.
o Made Bisect Wire show disabled in menu when paused or running.
o added Bisect Wire accelerator (Ctrl+B) to menu
--possible TODO: add Bisect Wire to Palette, or should Bisect Wire not be in the Draw menu?
  Maybe better in Edit menu?

o Linked CHM file to Multimedia Logic project
o Added Help Topic for Analyze Tool
--TODO: complete implementation of Analyze Tool

o Changed behavior when simulation is running and user tries to close document or exit program.
  now it prompts if user wants to stop simulation and close document or exit. Previously user had to
  close dialog box and manually stop simulation and then re-attempt closing document or exiting
  program.
o Changed behavior when simulation is running and user attempts to start another document simulating.
  Now user is prompted and can choose to have previous simulation stopped and new one started.

o Set default filter for opening memory file to *.TXT and *.BIN

   //TODO: Should we use m_iBinaryMode to dynamically set filter for drop down?
   //I am leaning toward making drop-down be "Memory Files (*.TXT;*.BIN)" followed by option for 
   //"All Files (*.*)"
   //We would then eliminate *.TXT and *.BIN as separate filter choices in the drop down.
   //
   //Is there any advantage to using the full path? Seems it would be better to use relative path.
   //this would benefit when sending zipped MMLogic project that has WAV, BMP, TXT etc files so receiver 
   //does not have to manually select file location since they most likely are using different directory structure.
--TODO: when the proper implementation above is decided upon, change filter for devices:
        Write File, Read File

--TODO:
Fix bug where accelerators disabled while running simulation but not while paused or in Draw mode
  o button accelerators on print preview dead including Tab, Enter,directional keys, (ALT) P, N, T, I, C, Escape
     o Space works! Press close button no error but press X on print preview closes and gives
       error about simulator must be stopped before closing.
     o closing print preview with X when simulator not running also closes the current document.
  o Menu accelerators dead such as Ctrl-F Ctrl-P etc
  o Find works from menu but Tab, Enter, Escape all dead while running simulation

--TODO: I think it would be good to add option to Find/Replace text for doing case insensitive
        search. This would help user to find non-matching tags.

--TODO: Consider moving Examples, and Release Notes text files to the help file. Or are
        they better as separate files?
--TODO: implement auto-close blank document when opening document.
--TODO: Add ability to draw lines at any angle.
o Fixed Ctrl-Drag on a Flip-Flop with preset/reset so it now clones properly.

===================
Need documentation:
  o How Find/Replace text works...in selected items, or entire project if nothing selected
  o Bisect wire
  o Color wires
  o Keyboard Accelerators
  o Change or remove documentation on Network Setup Basics?


==============================================================================
==================== Previous Version Release Notes Below ====================
==============================================================================

    Softronics MMLogic Version 1.4 for Microsoft Windows 95/98/Me/NT/2k/Xp
    ----------------------------------------------------------------------

                                Contents
                                --------

Part    I) Kit Description/Location:
Part   II) License/Pricing:
Part  III) New features/bugs fixed:
Part   IV) Installation:
Part    V) Standard features:
Part   VI) Recommended usage:
Part  VII) Bugs / Missing features / Wish List:
Part VIII) Reporting bugs:
Part   IX) Minimum System Requirements:

Part I) Kit Description/Location:

mmlogic14.exe (Full kit for all Win32 Windows Platforms)
mmsource14.zip(Visual Studio V6.0 SP5)

You will find kits at the following locations.

          http://www.softronix.com/

Note: Win32s is no longer supported

Part II) License/Pricing

   See License.txt file.

Part III) New features/bugs fixed:

Version 1.0

   o Initial Release

Version 1.1

   o Enhanced Counter to allow 4 or 8 Bit.
   o Enhanced Counter to have an Initial Value.
   o Enhanced Counter to be an Up and Down Counter.
   o Added Zoom mode for young hands and old eyes.
   o Fixed bug where an unconnected Node Device that was Forced to
     0 or 1 with and unconnected Bus Device would cause simulator to
     Hang.
   o Added Tape Drive device.
   o Enhanced performance of Robot Device for slower graphics cards.
   o Fixed LED7 device to properly reflect Unknown State on initial
     cycle.
   o Infinite Undo/ReDo editing for (Add Remove Only not for moves yet)

Version 1.2

   o Examples Fixed

Version 1.2a

   o Examples Fixed with counters

Version 1.2b

   o Fixed Right Mouse Click on Window when not maximized

Version 1.2c

   o Fixed XOR gate with 3 and 4 inputs.
   o Restored Missing Examples.TXT

Version 1.3

   o New Installation kit for Xp.

Version 1.4

   o Added 64KB option for Memory device (16-bit addresses).
   o Added Reset/Clear lines option for Flipflop devices.
   o Fixed emulation of Flipflop Hold state for MS Flipflops.
   o Added Canvas Size fields to View, Grid Settings to permit
     a larger workspace page.
   o Added Simulation Rate field to Simulate, Setup dialog to
     optionally slow down the simulation.
   o A Signal Sender may now have more than one Signal Receiver
     (the signal is duplicated to all Signal Receivers having the
     same name as the Signal Sender).
   o Implemented Edit, Find / Edit, Replace commands.
   o Added View, Goto Page dialog that also supports page naming.
   o Improved simulator performance.
   o Implemented View, Snap to Grid option (previous command
     renamed to View, Snap Selection to Grid).
   o Save spaces in filename strings in devices properly (previously truncated at first whitespace)
   o Prevent zoom in / zoom out too far (crash)
   o Problems with NULL FILE* pointers in devices (crash)
   o Memory device was leaking FILE* handles
   o Problems with Halt() during Initialize()
   o Other Reset() problems related to failure cases
   o Make AnodeNULL variable document-specific instead of a global variable. Avoids problems when a simulator is active
     (including paused) and the unconnected node type is changed for another document.
   o Nicer icon for document (instead of white rectangle)
   o Edit/Find should not make a selection if sim running, but should go to the correct page
   o BreakGate now displays gate's page upon break, if necessary, so user can see which BreakGate was hit
   o Calls to btn.Autoload() in dialog.cpp were generating a debug warning. This is because the correct call should be btn.SubclassDlgItem(). Fixed.
   o In some places (especially Reset()), objects from the m_objects list are blindly cast to CLogiGate*, but wires do not descend from CLogiGate*.
     Fixed to use the CLogiObj* base class where appropriate.
   o Disable View, Grid Settings when running/paused
   o Replace "MS Sans Serif" with "MS Shell Dlg", which is the proper font to use in recent MFC. (in logicli.rc)
   o Added some Tips of the Day regarding new features
   o Nodes queued for update if their state changes, instead of processing every node every cycle. Hugh performance increase if there are many nodes in the project.
   o Similar change to Post-Simulate handling.
   o Re-implemented undo/redo. Transactions supported. Move and property edits now un-doable.
   o Copy/paste was pasting bad wires in some cases, when selection did not include both endpoint devices.
   o Configurable canvas size in Simulate, Setup dialog
   o Configurable simulation rate in Hz via Simulate, Setup dialog
   o Add canvas size, simrate, and page name tokens to file format to implement saving of these new document properties. The changes are backward compatible.
     That is, the previous release will open the files created by this release but ignore the new features.
   o Windows XP theme support when running on Windows XP In particular, addition of manifest.xml resource
   o Snap to Grid while moving mode now supported.
   o Fixed bug in wire numbering on 3-input mux/demux device images.
   o Fixed state change bug in bus device that manifested following the addition of the node queue
   o Fixed propagation of bus float through Signal sender/receiver
   o Disallow Undo, Redo, Paste, Select All, Snap Selection to Grid when simulator running
   o Simulator will display a message if attempting to run a project with Port IO devices on a WinNT system.
   o Fixed pop-up menu to enable/disable items as appropriate
   o Implemented OnSetCursor for tools, so cursor is properly updated while moving across views in the splitter frame
   o Find/Replace text in selected items, or entire project if nothing selected
   o Fixed detected memory leaks. Most were in document destructor and the undo system.
   o Changed wire tool to display a "no" icon when trying to draw an illegal wire
   o Minor fixes to menu items, especially duplicate mnemonics and status bar text
   o If document window closed while Paused, the Palette is redisplayed if desired
   o Cleaned up the VERSIONINFORMATION resource, as WinXP Explorer displays this info in the "tiled" file view
   o Changes to Tip of Day needed for paint to be compatible with Windows XP support
   o Used an automated utility to renumber resources, to correct duplicate resource numbers
   o Put Zoom In / Zoom Out buttons on toolbar
   o When zoomed out far, fill entire rectangle with gray instead of drawing oversampled grid dots, which was very slow


Part IV) Installation:

   Run MMLogic14.EXE from Explorer

Part VI) Recommended usage:

   o Ages 8 and up. 

Part VII) Bugs / Missing features / Wish List:

   o See http://www.softronix.com

Part VIII) Reporting bugs:

   Report bugs to Softronics, Inc.:

   internet: mills@softronix.com

Part IX) Minimum System Requirements:

   Minimum: Pentium with 8meg running Windows 95.
