<?php
	$Agender_Version = '1.1.7.1';
$Agender_Release = '1';

function ver_rel()
{
	global $Agender_Version,$Agender_Release;
	echo $Agender_Version.'-'.$Agender_Release;
}

function ver()
{
	global $Agender_Version;
	echo $Agender_Version;
}

?>

<link rel="stylesheet" type="text/css" href="download.css" media="screen"/>
Agender is cross-platform(do I've to repeat that :P) so it has been built on several platforms,
search in this list if it's available for yours.

<ul id="download">
	<li id="msw"><a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver() ?>.exe">Windows Installer</a>
		- 2000, XP, Vista & Se7en<br/>
		Windows 95, 98 & me - currently we aren't building for this versions of windows, but if you need one
		you can make a <a href="http://sourceforge.net/tracker/?group_id=271084&atid=1152801">request</a>
	</li>
	<li id="suse">RPM packages for openSuSE
		<br/>11.1 -
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.suse111.i585.rpm/download">i586</a>
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.suse111.x86_64.rpm/download">x86_64</a>
	<br/>11.2 -
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.suse112.i585.rpm/download">i586</a>
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.suse112.x86_64.rpm/download">x86_64</a>
	<br/>11.3 -
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.suse113.i585.rpm/download">i586</a>
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.suse113.x86_64.rpm/download">x86_64</a>
	</li>
	<li id="mdv">RPM packages for Mandriva
	<br/>2009 -
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.mdv2009.i585.rpm/download">i586</a>
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.mdv2009.x86_64.rpm/download">x86_64</a>		<br/>2010 -
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.mdv2010.i585.rpm/download">i586</a>
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.mdv2010.x86_64.rpm/download">x86_64</a>
	</li>
	<li id="fedora">RPM packages for Fedora
	<br/>12 -
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.fc12.i385.rpm/download">i386</a>
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.fc12.x86_64.rpm/download">x86_64</a>		<br/>13 -
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.fc13.i385.rpm/download">i386</a>
		<a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver_rel() ?>.fc13.x86_64.rpm/download">x86_64</a>
	</li>
	<li id="deb">
	Currently we don't provide debian packages, if you would like to help comment in the
	<a href="http://sourceforge.net/tracker/?func=detail&atid=1152801&aid=3041245&group_id=271084">bug</a>
	</li>
	<li id="apple">
	Currently we don't provide Mac bundles, if you would like to help comment in the
	<a href="http://sourceforge.net/tracker/?func=detail&aid=3041223&group_id=271084&atid=1152801">bug</a>
	</li>
	<li id="tar">
	If you use a Operating System for which we don't provide packages or simply want to know
	how Agender works, you can download the
	<a href="http://sourceforge.net/projects/agender/files/Agender-1.1.6.tar.bz2/download">sourcecode</a>
	</li>
	<li id="svn">
	Keep up with Agender development.<br/>
	svn co https://agender.svn.sourceforge.net/svnroot/agender/trunk Agender
	</li>
</ul>
