# Steam X Proper

This is a small application that will read the `STEAM_GAME` window property from any game launched by Steam® and writes the appropriate desktop entry onto the window.

With it, you can pin Steam® games to your task manager as well as get the correct window icon in KDE Plasma 5.

This only works for games that you had create a desktop file (e.g. start menu entry) on installation.

Before:
![Screenshot of KDE Plasma's task manager showing a game context menu with no application icon and "Pin to task bar" grayed out"](screenshot_before.png?raw=true "Before")
After:
![Screenshot of KDE Plasma's task manager showing a game context menu with proper application icon and "Pin to task bar" hovered"](screenshot_after.png?raw=true "After")

## How to install

This project is configured using `cmake`.
You need to have development packages for XCB, Qt X11 Extras, KService, and KWindowSystem as well as Extra CMake Modules installed to build it, for example `libxcb1-dev`, `libqt5x11extras5-dev`, `libkf5windowsystem-dev`, and `libkf5service-dev` as well as `extra-cmake-modules`.

Basically:
```
mkdir build
cd build
cmake ..
make
```

Then simply run the application. You can also add it to your autostart.

## License

```
The MIT License (MIT)

Copyright 2020 Kai Uwe Broulik

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```

Steam and the Steam logo are trademarks and/or registered trademarks of Valve Corporation in the U.S. and/or other countries.
