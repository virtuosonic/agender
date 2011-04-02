/******************************************************************************
*                   Agender, a cross-platform schedule tool
******************************************************************************/

Web:
====
    http://agender.sourceforge.net
    http://sourceforge.net/projects/agender
    http://sourceforge.net/apps/mediawiki/agender
    http://sourceforge.net/apps/gallery/agender
    agender-announce@lists.sourceforge.net
    agender-support@lists.sourceforge.net

Intro:
======
    Thanks for trying this software, Agender is a small tool for
    writing your schedule, it is  a cross-platform software and should
    compile and run on Unix, Windows, Mac OSX and someother platforms.

    If you're tired of using slow, big and complicated software
    like Microsoft Works, Evolution or iCal then Agender is for
    you, Agender makes it all simple.

    If you like Agender consider making a donation, that way you will
    help the development of Agender, we will also add you to the
    Hall of Fame and link to your website if you like so, you can send
    a donation via paypal by clicking in the Support this project button
    that can be found on the left of Agender's website.

Special:
========
    I'll send an edition of Agender with your name in the
    title bar if you're the first one to send a mail saying
    you read this.

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
    Agender is being developed with the Microsoft C/C++ 12.00, and
    wxWidgets 2.8.11 maybe it works with anothers, not sure.
    The website is www.wxwidgets.org.

Compiling & Installing:
=======================
    If you are using Windows you can dowload the installer from the
    website is named something like Agender-x.x.x.exe where x.x.x
    is the version.

    Read the file INSTALL, if you don't wan't to read so much, here
    are some short instructions:

        Type on a terminal:
            $cd $(Agender)
            $./configure
            $make
            $su -c make\ install

    $(Agender) is the directory where this file is , don't type
    the $ at the start of every line.

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

    http://sourceforge.net/tracker/?group_id=271084&atid=1152801

    You can also send a mail to agender-support@lists.sourceforge.net

Porting/Packaging:
==================
    Agender uses, the wxWidgets library, doesn't use advanced C++
    features like templates, C++ RTTI or exceptions. So it should be
    easy to port, since wxWidgets it self has been ported to several
    platforms.

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

Help wanted:
============
   If you are a programmer and want to help you could start
   choosing a task from the todo list below

TODO:
=====
    -Sticky notes
    -notifications
    -Trash bin
    -Undo/Redo!!!!!!!!!
    -iCalendar support
    -Clipboard/Drag & Drop support
    -Search
    -Integrate with Windows se7en dock
    -Sticky weekday notes
    -richtextctrl
    -More translations
    -Windows mobile port
    -OSX packages
    -FreeBSD testing

Changelog:
==========
Read ChangeLog.txt

Distro Makers:
==============
    Hi distro maker, if you want to include Agender in your operating
    system, you are free to do it, just follow the license, but I request
    you to send me the instructions on how to install Agender on your
    system, so I can add them to the website, screenshots are also cool.

Author:
=======
    Gabriel Espinoza
        <virtuosonic@users.sourceforge.net>
        http://virtuosonicplusplus.blogspot.com
        http://virtuosonic.users.sourceforge.net/

Thanks for reading :) EOF
