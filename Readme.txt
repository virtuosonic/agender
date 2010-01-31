/***************************************************************
*			Agender, a crossplataform schedule tool
***************************************************************/
Web:
====
	http://agender.souceforge.net
	http://sourceforge.net/projects/agender
Intro:
======
	Thanks for trying this software, Agender is a small tool for
	writing your schedule, it is  a crossplataform software and should
	compile and run on un*x, Windows, Mac OSX and someother platforms.

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
	using 2.8.10 maybe	it works with another, not sure. The
	website is www.wxwidgets.org.

	Under fedora you can install it with the command:

		yum install wxGTK-devel gcc-c++

	Or for cross-compiling to win32

		yum install minggw32-gcc-c++
Compiling & Installing:
=======================
	Read the file INSTALL, if you don't wan't to read so much, here
	are some short instructions:
		type on a terminal:
			$cd $(Agender)
			$./configure
			$make
			$su -c 'make install'
	$(Agender) is the directory where this file is (unless you have
	move it), don't type the $ at the start of every line.

	If you aren't using a un*x operating system, there is an archive
	containing the makefiles and project files for several compilers
	you can find it at http://sourceforge.net/projects/agender/files
Bugs:
=====
	I don't call them that way, i call them "advanced user features".
	If you find one report it at the project bug tracker, patches are
	welcome, thank you.

Porting/Packaging:
===============
	Agender uses, the wxWidgets library, it almost doesn't use the
	STL, doesn't use advanced C++ features like templates, C++
	RTTI or exceptions. So it should be easy to port, since wxWidgets
	it self has been ported to several platforms.

	Some platforms already	supported by wxWidgets that I would like
	to see running Agender would be: Mac OSX, WindowsMobile,
	PDA's running Linux (like Familiar Linux, Intimate Linux and
	Angstrom) and portable video consoles based on linux (like
	Pandora).

	If you want to join the	Agender project, please mail me and I will
	give you access to svn and rights to upload files to the filemanager.
Translating/i18n:
==============
	The wxWidgets approach to i18n closely follows the GNU gettext
	package. I use and recommend the Poedit program, you can use a
	simple text editor and the command line tools, but Poedit is more
	easy to use.

	You can get Poedit at:
		http://www.poedit.net

Distro Makers:
=============
	Hi distro maker, if you wan't to include Agender in your operating
	system, you are free to do it, just follow the license, but i request
	you to send me the instructions on how to install Agender on your
	system, so i can add them to the website documentation.
Author:
=======
	Gabriel Espinoza <virtuosonic@users.sourceforge.net>

Thanks for reading :) EOF
