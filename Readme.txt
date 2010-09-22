/******************************************************************************
*                   Agender, a cross-platform schedule tool
******************************************************************************/

Web:
====
    http://agender.sourceforge.net

Intro:
======
    Thanks for trying this software, Agender is a small tool for
    writing your schedule, it is  a cross-platform software and should
    compile and run on X, Windows, Mac OSX and someother platforms.

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
    Agender is being developed with GNU g++ 4.3.2, and
    wxWidgets 2.8.10 maybe it works with anothers, not sure.
    The website is www.wxwidgets.org.

Compiling & Installing:
=======================
    If you are using Windows you can dowload the installer from the
    website is named something like Agender-x.x.x.exe where x.x.x
    is the version. If you are upgrading from version 1.1.6 please first
    run the uninstaller and then install, the way translations are installed
    haves changed. There also are rpm packages for some Linux
    distros. Take a look at
        http://agender.sf.net/index.php?page=Downloads

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
        bakefile -f msvc Agender.bkl

    If you're building from svn then you need to generate your
    makefile using bakefile, you can get bakefile at:
        http://www.bakefile.org/

Bugs:
=====
    I don't call them that way, I call them "advanced user features".
    If you find one report it at the project bug tracker, patches are
    welcome, thank you.

    You can also send a mail to agender-support@lists.sourceforge.net

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

Translating/i18n:
=================
    The wxWidgets approach to i18n closely follows the GNU gettext
    package. The use of Poedit is recommend for translating
    messages catalogs, you can use a simple text editor and the
    command line tools, but Poedit is more easy to use.

    You can get Poedit at:
        http://www.poedit.net

TODO:
=====
    -Undo/Redo!!!!!!!!!
    -Clipboard/Drag & Drop support
    -Search
    -Sticky weekday notes
    -new file format in xml
    -richtextctrl
    -More translations
    -notifications

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
    system, you are free to do it, just follow the license, but I request
    you to send me the instructions on how to install Agender on your
    system, so I can add them to the website.

Author:
=======
    Gabriel Espinoza
        <virtuosonic@users.sourceforge.net>
        http://virtuosonicplusplus.blogspot.com
        http://virtuosonic.users.sourceforge.net/

Thanks for reading :) EOF
