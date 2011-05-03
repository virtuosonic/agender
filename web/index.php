<?php
$page = $_GET['page'];
if ($page == '') {
$page = 'Home';
}
//langs
function DetectLang($langs)
{
	$tok = strtok($_SERVER['HTTP_ACCEPT_LANGUAGE'],",;");
	while($tok !== false) {
		if (in_array($tok,$langs))
			return $tok;
		$tok = strtok(",;");
	}
	return '';
}
//read language
$language = $_GET['language'];
$langs=scandir('htm');
//probe language
if ($language == '' || !in_array($language, $langs)) {
	$language=DetectLang($langs);
	if ($language == '')
		$language='en';
}
include 'htm/'.$language.'/messages.php';
//selected option from lang form
$selected = 'selected="selected"';
$en = $es = '';
if ($language == 'en')
	$en = $selected;
else if ($language == 'es')
	$es = $selected;
//active link
$active = 'id="active"';
$inactive = "";
$Home = $Downloads =$Press = $Screenshots = $About = $Links = $Help = $inactive;
//page title
if ($page == 'Home') {
	$Home = $active;
	$title=$Home_title;
}
else if ($page == 'Downloads') {
	$Downloads = $active;
	$title=$Downloads_title;
}
else if ($page == 'Press') {
	$Press = $active;
	$title=$Press_title;
}
else if ($page == 'Screenshots') {
	$Screenshots = $active;
	$title=$Screenshots_title;
}
else if ($page == 'About') {
	$About = $active;
	$title=$About_title;
}
else if ($page == 'Links') {
	$Links = $active;
	$title=$Links_title;
}
else if ($page == 'Help') {
	$Help = $active;
	$title=$Help_title;
}
//time function
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
//page
$page_name = 'htm'.'/'.$language.'/'.$page.'.htm';

exitIfNotModifiedSince(setLastModified($page_name));
//page exists?
$pages = glob('htm'.'/'.$language.'/'."*.htm");
$page_data = '';
if (in_array($page_name, $pages) and file_exists($page_name)){
    $page_data = file_get_contents($page_name);
}
else {$page_data = $error404;}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" lang="<?php echo $language ?>" xml:lang="<?php echo $language ?>">
<head>
	<meta content="text/html; charset=utf-8" http-equiv="Content-Type"/>
	<meta name="author" content="Gabriel Espinoza"/>
	<meta name="keywords" content="Agender,agender,agenda,schedule,calendar,calendario,wxWidgets,cross platform,free software,windows,linux,opensource,XP,se7en,osx,mac,MacPorts,freebsd"/>
	<meta name="description" content=<?php  echo $Description ?>/>
	<meta name="google-site-verification" content="iUBg-Nc16oi8DZuLt_3KwE8exy7fstuQjP7nMNeTSU4" />
	<title>Agender - <?php echo $title ?></title>
	<link rel="stylesheet" type="text/css" href="agender.css" media="screen"/>
	<link rel="alternate" type="application/rss+xml" href="rss.xml"
		title="Agender - a cross-platform schedule tool!"/>
	<link rel="icon" href="agender32.png"/>
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
<body>
<div id="left_pane">
	<!-- lang-form -->
	<form id="lang-form" method="GET" action="index.php">
	<input type="hidden" name="page" value="<?php echo $page ?>"/>
	<label for="language"><?php echo $lang_label ?></label>
	<select id="language" name="language" onchange="this.form.submit()">
		<option value="en" <?php echo $en ?>>English</option>
		<option value="es" <?php echo $es ?>>Español</option>
	</select>
	<br/>
	<noscript><input type="submit" value="Change language"/></noscript>
	</form>
	<!-- sf_net logo-->
	<a href="http://sourceforge.net/projects/agender" >
		<img src="http://sourceforge.net/sflogo.php?group_id=271084&amp;type=1" alt='SourceForge.net Logo' title="SourceForge.net"/>
	</a>
	<br/>
	<a href="http://sourceforge.net/donate/index.php?group_id=271084">
		<img src="http://images.sourceforge.net/images/project-support.jpg" alt="Support This Project"  title=<?php echo $Donate ?>/>
	</a>
	<br/>
<!-- ohloh statistics START-->
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
</div><!-- end of left_pane -->
<!-- center container -->
<div id="container">
	<center><img src="hdr.png"/></center>
	<!-- menu -->
	<div id="menu">
		<a <?php echo $Home ?> href="?page=Home&language=<?php echo $language ?>"><?php echo $Home_menu ?></a> |
		<a <?php echo $Downloads ?> href="?page=Downloads&language=<?php echo $language ?>"><?php echo $Downloads_menu ?></a> |
		<a <?php echo $Press ?> href="?page=Press&language=<?php echo $language ?>"><?php echo $Press_menu ?></a> |
		<a <?php echo $Screenshots ?> href="?page=Screenshots&language=<?php echo $language ?>"><?php echo $Screenshots_menu ?></a> |
		<a <?php echo $About ?> href="?page=About&language=<?php echo $language ?>"><?php echo $About_menu ?></a> |
		<a <?php echo $Links ?> href="?page=Links&language=<?php echo $language ?>"><?php echo $Links_menu ?></a> |
		<a <?php echo $Help ?> href="?page=Help&language=<?php echo $language ?>"><?php echo $Help_menu ?></a>
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
	<script type="text/javascript" src="http://www.google.com/cse/brand?form=cse-search-box&amp;lang=es"></script>
	</div>
	<!-- start of contents -->
	<?php echo $page_data;?>
	<!-- end of contents -->
</div>
<!-- adsense -->
<div id="vs_google_adsense">
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
<div id="mail">
<form method="POST" action="http://lists.sourceforge.net/lists/subscribe/agender-announce">
	<p><?php echo $mailmessage ?></p>
	<label for="email">email:</label><input id="email" type="Text" name="email" size="30" value=""/>
	<input type="Submit" name="email-button" value=<?php echo $Subscribe?>/>
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
