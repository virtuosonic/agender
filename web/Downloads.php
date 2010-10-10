<?php
	$Agender_Version = '1.1.7.1';
$Agender_Release = '5';

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
<p>
<link rel="stylesheet" type="text/css" href="download.css" media="screen"/>
Congratulations you have reached the downloads page, if you like Agender consider making
a donation that way you will help the development of Agender, you can also help reporting
<a href="http://sourceforge.net/tracker/?group_id=271084&atid=1152801">bugs</a>
or translating it to more languages
</p>
<ul id="download">
	<li id="msw"><a href="http://sourceforge.net/projects/agender/files/Agender-<?php ver() ?>.exe">Windows Installer</a>
		- 2000, XP, Vista & Se7en<br/>
		Windows 95, 98 & me - currently we aren't building for this versions of windows, but if you need one
		you can make a <a href="http://sourceforge.net/tracker/?group_id=271084&atid=1152801">request</a>
	</li>
	<li id="apple">
	Currently we don't provide Mac bundles, if you would like to help comment in the
	<a href="http://sourceforge.net/tracker/?func=detail&aid=3041223&group_id=271084&atid=1152801">bug</a>
	</li>
	<li id="tar">
	If you use a Operating System for which we don't provide packages or simply want to know
	how Agender works, you can download the
	<a href="http://sourceforge.net/projects/agender/files/Agender-1.1.6.tar.bz2@">sourcecode</a>
	</li>
	<li id="svn">
	Keep up with Agender development.<br/>
	svn co https://agender.svn.sourceforge.net/svnroot/agender/trunk Agender
	</li>
</ul>
