/******************************************************************************
*                   Agender, a cross-platform schedule tool
******************************************************************************/

Web:
====
    http://agender.sourceforge.net
    http://sourceforge.net/projects/agender

Intro:
======
    Thanks for trying this software, Agender is a small tool for
    writing your schedule, it is  a cross-platform software and should
    compile and run on X, Windows, Mac OSX and someother platforms.

    Its creation started on 21 november 2008, I created Agender because
    I didn't want to use software like M$ Works or Evolution, they were
    so big, complicated, and sometimes slow, not only talking of
    processor usage but in usage flow.

    So one I started playing with wxCalendarCtrl, and sometimes later
    I get something that work, Agender was born...


Licence:
========
    Agender is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Agender is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Agender. If not, see <http://www.gnu.org/licenses/>.

Dependencies:
=============
    To compile you will need a C++ compiler and wxWidgets 2.8,
    Agender is being developed with GNU g++ 4.3.2, and I'm
    using wxWidgets 2.8.10 maybe it works with another, not sure.
    The website is www.wxwidgets.org.

    Under fedora you can install it with the command:

        yum install wxGTK-devel gcc-c++

    Or for cross-compiling to win32

        yum install mingw32-gcc-c++

Compiling & Installing:
=======================
    Read the file INSTALL, if you don't wan't to read so much, here
    are some short instructions:

        Type on a terminal:
            $cd $(Agender)
            $./configure
            $make
            $su -c 'make install'

    $(Agender) is the directory where this file is (unless you have
    move it:), don't type the $ at the start of every line.

    If you aren't using a un*x operating system, you can generate
    makefiles and project file for several compiler using bakefile
    for example:
        bakefile -f gnu Agender.bkl
    If you're building from svn then you need to generate your
    makefile using bakefile, you can get bakefile at:
        http://www.bakefile.org/
Bugs:
=====
    I don't call them that way, i call them "advanced user features".
    If you find one report it at the project bug tracker, patches are
    welcome, thank you.

Porting/Packaging:
==================
    Agender uses, the wxWidgets library, it almost doesn't use the
    STL, doesn't use advanced C++ features like templates, C++
    RTTI or exceptions. So it should be easy to port, since wxWidgets
    it self has been ported to several platforms.

    Some platforms already supported by wxWidgets that I would like
    to see running Agender would be: Mac OSX, Windows Mobile,
    PDA's running Linux (like Familiar Linux, Intimate Linux and
    Angstrom) and portable video consoles based on linux (like
    Pandora).

    If you want to join the Agender project, please email me and I will
    give you access to svn and rights to upload files to the filemanager.

Hacking:
========
    Some knogledge of C++, OOP and wxWidgets is required for
    understanding Agender, here is a description of what every
    file does.

    src/AgenderApp.{cpp,h}
        This files include the application class, its the equivalent
	to the main function, it initialize some things, like the
        locale, command line parsing, checking for other instances,
        creating the main window, and creating the interprocess
        communications server. It also cleans up this things.

    src/AgenderMain.{cpp,h}
        This may be the more important files of the program, they
        contain the class for the main window it also loads and
        saves configuration files and creates the tray icon.

    src/AgenderCal.{cpp,h}
        Here is the class that abstracts read & writing notes, once
        AgenderFrame loads the files AgenderCal reads from wxConfig::Get

    src/AgenderTray.{cpp,h}
        Agender's tray icon lives heres it uses wxEvent's to communicate
        with the rest of the gui, it is owned by AgenderFrame.

    src/AgenderIPC.{cpp,h}
        AgenderServer is used for some interprocess communication, when you
        start Agender it will check for another instances of Agender, if it
        founds one it will create a wxClient that will connect with
        AgenderServer and AgenderServer will show the main window of the
        instance that was already running, this should be completely
        invisible to the user, like if it where magic ;)

    src/AgenderDnd.{cpp,h}
        All the code related to copy/paste and Drag&Drop is in this file,
        actually its incomplete, and doesn't work, it even isn't in the makefiles.

    Agender.bkl
        Bakefile is used for generating makefile for several system

    Agender.nsi
        Windows installer, must be compiled with makensis

Translating/i18n:
=================
    The wxWidgets approach to i18n closely follows the GNU gettext
    package. The use of Poedit is recommend for translating
    messages catalogs, you can use a simple text editor and the
    command line tools, but Poedit is more easy to use.

    You can get Poedit at:
        http://www.poedit.net
    Or from my beloved fedora:
        yum install poedit

TODO:
=====
    -Undo/Redo!!!!!!!!!
    -Clipboard/Drag & Drop support
    -Search
    -Sticky weekday notes
    -new file format in xml
    -richtextctrl
    -More translations
    -Re-structure project's tree

Changelog:
==========
28 junio 2009
   released version 1.0.6

     Change log:
        -Applied: cambio del archivo de configuracion para que sea oculto en un*x

18 abril 2009
   released version 1.0.5

     Change log:
        -Fixed: Error de manejo de memoria, que provocaba que el programa recibiera la señal SIGSEGV
        -Added: el submenu opacity se deshabilita si no se soporta tranparencia
        -New: ahora los dias se marcan inmediatamante al agregar o eliminar notas

21 February 2009
   released version 1.0.4

     Change log:
        -Fixed: ahora las fechas que solo tienen un digito tambien se colorean si contienen notas

21 February 2009
   released version 1.0.3

     Change log:
        -New: parcial: los dias que tinen notas aparecen marcados de rojo (se puede cabiar el color) en el calendario

30 January 2009
   released version 1.0.2

     Change log:
        -Fixed: Fallo al escribir al registro

27 January 2009
   released version 1.0.1

     Change log:
        -Fixed: Escribe en el registro solo cuando es necesario
        -New: Iconos de la barra de tareas, programa y del cuadro acerca de...
        -Fixed: Carga las notas del dia correspondiente

Distro Makers:
==============
    Hi distro maker, if you want to include Agender in your operating
    system, you are free to do it, just follow the license, but i request
    you to send me the instructions on how to install Agender on your
    system, so i can add them to the website documentation.

Author:
=======
    Gabriel Espinoza
        <virtuosonic@users.sourceforge.net>
	http://virtuosonicplusplus.blogspot.com
        http://virtuosonic.users.sourceforge.net/
        http://sourceforge.net/users/virtuosonic/

Thanks for reading :) EOF
