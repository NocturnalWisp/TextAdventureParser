# TextAdventureParser
A parser for text adventures, written in C++.

You can check out the releases section for the tap.dll file to use in any of your projects.

To run the example game.ta and print the file to the console after parsing, use [cmake](https://cmake.org/cmake/help/latest/guide/tutorial/A%20Basic%20Starting%20Point.html#exercise-1-building-a-basic-project)(Jump to build and run section.) to build the c++ source code.

The following diagram showcases the initial .ta file being transitioned into a TextAdventure object for your use.
You can find the .ta script here: [game.ta](assets/game.ta) instead of reading it in the table on the left side of the diagram.

![](Git%20Resources/TextAdventureParserMap.jpg?raw=true)

TextAdventure contains 3 useful lists: scenes, items, and events. Use these to build your text adventure.
