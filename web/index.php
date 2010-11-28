<?php
$loadscript = '';
$Appear='';
$page = $_GET['page'];
if ($page == '') {
$page = 'Home';
$Appear='style="display: none"';
$loadscript = "onload=\"Effect.toggle('container','Appear');Effect.toggle('left_pane','Appear');Effect.toggle('vs_google_adsense','Appear');Effect.toggle('mail','Appear'); return false;\"";
}
$active = 'id="active"';
$inactive = "";
$Home = $Downloads =$Press = $Screenshots = $About = $Links = $inactive;
if ($page == 'Home') {
	$Home = $active;
	$title="A cross-platform schedule tool!";
}
else if ($page == 'Downloads') {
	$Downloads = $active;
	$title="Get Agender";
}
else if ($page == 'Press') {
	$Press = $active;
	$title="Press";
}
else if ($page == 'Screenshots') {
	$Screenshots = $active;
	$title="Screenshots";
}
else if ($page == 'About') {
	$About = $active;
	$title="About";
}
else if ($page == 'Links') {
	$Links = $active;
	$title="Links";
}

///blablabla

function setLastModified($pagetime)
{
    $last_modified=getlastmod();
    $header_modified=filemtime($pagetime);
    if($header_modified > $last_modified)
    {
        $last_modified=$header_modified;
    }
    header('Last-Modified: ' . date("r",$last_modified));
    return $last_modified;
}

function exitIfNotModifiedSince($last_modified)
{
    if(array_key_exists("HTTP_IF_MODIFIED_SINCE",$_SERVER))
    {
        $if_modified_since=strtotime(preg_replace('/;.*$/','',$_SERVER["HTTP_IF_MODIFIED_SINCE"]));
        if($if_modified_since >= $last_modified)
        {
            header("HTTP/1.1 304 Not Modified");
            exit();
        }
    }
}
$error404 = "<center>".
            "<h3>This page cannot be found, <i>try using google</i>.</h3>http error 404".
            "</center>\n";
$page_name = $page.'.htm';

exitIfNotModifiedSince(setLastModified($page_name));

$pages = glob("*.htm");
$page_data = '';

if (in_array($page_name, $pages) and file_exists($page_name)){
    $page_data = file_get_contents($page_name);
}
else {$page_data = $error404;}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="en" xml:lang="en">
<head>
	<meta content="text/html; charset=utf-8" http-equiv="Content-Type"/>
	<meta name="author" content="Gabriel Espinoza"/>
	<meta name="keywords" content="Agender,agender,agenda,schedule,calendar,calendario,wxWidgets,cross platform,free software,windows,linux,opensource,XP,se7en,osx,mac"/>
	<meta name="description" content="the cross platform schedule tool"/>
	<meta name="google-site-verification" content="iUBg-Nc16oi8DZuLt_3KwE8exy7fstuQjP7nMNeTSU4" />
	<title>Agender - <?php echo $title ?></title>
	<link rel="stylesheet" type="text/css" href="agender.css" media="screen"/>
	<link rel="stylesheet" type="text/css" href="menu.css" media="screen"/>
	<link rel="alternate" type="application/rss+xml" href="rss.xml"
		title="Agender - a cross-platform schedule tool!"/>
	<link rel="icon" href="agender32.png"/>
	<script src="js/prototype.js" type="text/javascript"></script >
	<script src="js/scriptaculous.js" type="text/javascript"></script >
	<!--eliminar si google no empieza a funcionar-->
	<!--google analytics-->
	<script type="text/javascript">
	var _gaq = _gaq || [];
	_gaq.push(['_setAccount', 'UA-19811940-1']);
	_gaq.push(['_trackPageview']);
	(function() {
	var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
	ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
	var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
	})();
	</script>
</head>
<body <?php echo $loadscript ?>>
<div id="left_pane" <?php echo $Appear ?>>
	<a href="http://sourceforge.net/projects/agender" >
		<img src="http://sourceforge.net/sflogo.php?group_id=146403&amp;type=1" alt='SourceForge.net Logo' title="SourceForge.net"/>
	</a>
	<br/>
	<a href="http://sourceforge.net/donate/index.php?group_id=271084">
		<img src="http://images.sourceforge.net/images/project-support.jpg" alt="Support This Project"  title="Donate"/>
	</a>
	<br/>
<script type="text/javascript"
	src="http://www.ohloh.net/p/363772/widgets/project_thin_badge.js">
</script>
<!-- google adsense vertical -->
<div id="vs_google_adsense_vert"><script type="text/javascript"><!--
	google_ad_client = "pub-8829282890738806";
	/* agender vertical 120x240 */
	google_ad_slot = "2040602416";
	google_ad_width = 120;
	google_ad_height = 240;
	//-->
</script>
	<script type="text/javascript"
		src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
	</script></div>
</div>
<!-- center container -->
<div id="container" <?php echo $Appear ?>>
	<center><img src="hdr.png"/></center>
	<!-- menu -->
	<div id="menu">
		<a <?php echo $Home ?> href="?page=Home">Home</a> |
		<a <?php echo $Downloads ?> href="?page=Downloads">Downloads</a> |
		<a <?php echo $Press ?> href="?page=Press">Press</a> |
		<a <?php echo $Screenshots ?> href="?page=Screenshots">Screenshots</a> |
		<a <?php echo $About ?> href="?page=About">About</a> |
		<a <?php echo $Links ?> href="?page=Links">Links</a>
	</div>
	<!-- google search -->
	<div id="vs_google_search_id">
	<form action="http://www.google.com/cse" id="cse-search-box" target="_blank">
		<div>
			<input type="hidden" name="cx" value="partner-pub-8829282890738806:o7d14avk586" />
			<input type="hidden" name="ie" value="ISO-8859-1" />
			<input type="text" name="q" size="31" />
			<input type="submit" name="sa" value="Buscar" />
		</div>
	</form>
	<script type="text/javascript" src="http://www.google.com/cse/brand?form=cse-search-box&amp;lang=es"></script></div>
	<!-- start of contents -->
	<?php echo $page_data;?>
	<!-- end of contents -->
</div>
<!-- adsense -->
<div id="vs_google_adsense" <?php echo $Appear ?>>
	<script type="text/javascript"><!--
		google_ad_client = "pub-8829282890738806";
		/* agender website */
		google_ad_slot = "0472286487";
		google_ad_width = 336;
		google_ad_height = 280;
		//-->
	</script>
	<script type="text/javascript"
		src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
	</script>
</div>
<!-- mailing list -->
<div id="mail"<?php echo $Appear ?>>
<form method="POST" action="https://lists.sourceforge.net/lists/subscribe/agender-announce">
	<p>Want to know about new Agender Releases? subscribe to the agender-announce mailing list</p>
	<div style="display: inline">email:<input type="Text" name="email" size="30" value=""/></div>
	<input type="Submit" name="email-button" value="Subscribe"/>
</form>
</div>
<!-- Piwik -->
<script type="text/javascript">
	var pkBaseURL = (("https:" == document.location.protocol) ? "https://sourceforge.net/apps/piwik/agender/" : "http://sourceforge.net/apps/piwik/agender/");
	document.write(unescape("%3Cscript src='" + pkBaseURL + "piwik.js' type='text/javascript'%3E%3C/script%3E"));
</script>
<script type="text/javascript">
	try {
	var piwikTracker = Piwik.getTracker(pkBaseURL + "piwik.php", 1);
	piwikTracker.trackPageView();
	piwikTracker.enableLinkTracking();
	} catch( err ) {}
</script>
<noscript>
	<p><img src="http://sourceforge.net/apps/piwik/agender/piwik.php?idsite=1" style="border:0" alt=""/></p>
</noscript>
<!-- End Piwik Tag -->
</body>
</html>
