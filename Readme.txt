			Agender, a crossplataform schedule tool
			***************************************
Web:
====
	http://agender.souceforge.net
	http://sourceforge.net/projects/agender
Intro:
======
	Thanksfor trying this software, Agender is a small tool for
	writing your schedule, it is  a crossplataform software and should
	compile and run on un*x, Windows, Mac OSX and someother platforms.

Licence:
========
	Agender is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along
	with this program; if not, write to the Free Software Foundation, Inc.,
	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

Dependencies:
=============
	To compile you will need wxWidgets 2.8, I'm using 2.8.10 maybe
	it works with another, not sure. The website is
	www.wxwidgets.org.

	Under fedora you can install it with the command:

		yum install wxGTK-devel

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
	welcome, thank you. If you have patch to fix a build with an
	old/non compliant compiler (like VC 6, or Turbo C++) and those
	 broke build/portability/coding style/etc they aren't welcome,
	please don't be silly get a new compiler :P
Author:
=======
	Gabriel Espinoza <virtuosonic@users.sourceforge.net>

Thanks for reading :) EOF
