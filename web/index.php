<?php
$loadscript = '';
$Appear='';
$page = $_GET['page'];
if ($page == '') {
$page = 'Home';
$Appear='style="display: none"';
$loadscript = "onload=\"Effect.toggle('container','Appear'); return false;\"";
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
else {
	$Home = $inactive;
	$title = $page;
}

$vs_google_search = '<div id="vs_google_search_id">
<form action="http://www.google.com/cse" id="cse-search-box" target="_blank">
  <div>
    <input type="hidden" name="cx" value="partner-pub-8829282890738806:o7d14avk586" />
    <input type="hidden" name="ie" value="ISO-8859-1" />
    <input type="text" name="q" size="31" />
    <input type="submit" name="sa" value="Buscar" />
  </div>
</form>
<script type="text/javascript" src="http://www.google.com/cse/brand?form=cse-search-box&amp;lang=es"></script></div>';

$error404 = "<center>".
            "<h3>This page cannot be found, <i>try using google</i>.</h3>http error 404".
            "</center>\n";

$page_name = $page.'.php';

$pages = glob("*.php");
$page_data = '';

if (in_array($page_name, $pages) and file_exists($page_name)){
    $page_data = '';
}
else {$page_data = $error404;}
?>
<html>
<head>
	<title>Agender - <?php echo $title ?></title>
	<link rel="stylesheet" type="text/css" href="agender.css" media="screen"/>
	<link rel="stylesheet" type="text/css" href="menu.css" media="screen"/>
	<link rel="alternate" type="application/rss+xml"
		href="rss.xml" title="Agender - a cross-platform schedule tool!"/>
	<script src="js/prototype.js" type="text/javascript"></script >
	<script src="js/scriptaculous.js" type="text/javascript"></script >
</head>

<body <?php echo $loadscript?>>
	<div id="left_pane">
		<a href="http://sourceforge.net/projects/agender" >
			<img src="http://sourceforge.net/sflogo.php?group_id=146403&amp;type=1" alt='SourceForge.net Logo' title="SourceForge.net"/>
		</a>
		<br/>
		<a href="http://sourceforge.net/donate/index.php?group_id=271084">
			<img src="http://images.sourceforge.net/images/project-support.jpg" width="88" height="32" border="0" alt="Support This Project"  title="Donate"/>
		</a>
		<br/>
		<script type="text/javascript"
			src="http://www.ohloh.net/p/363772/widgets/project_partner_badge.js">
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
			<a <?php echo $Home ?> href="index.php?page=Home">Home</a> |
			<a <?php echo $Downloads ?> href="index.php?page=Downloads">Downloads</a> |
			<a <?php echo $Press ?> href="index.php?page=Press">Press</a> |
			<a <?php echo $Screenshots ?> href="index.php?page=Screenshots">Screenshots</a> |
			<a <?php echo $About ?> href="index.php?page=About">About</a> |
			<a <?php echo $Links ?> href="index.php?page=Links">Links</a>
		</div>
		<?php echo $vs_google_search ?>
		<!-- start of contents -->
		<?php
			if ($page_data !== '')
			{
				echo $page_data;
			}
			else
			{
				include $page_name;
			}
		?>
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
</body>

</html>

