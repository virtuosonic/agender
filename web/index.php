<?php
$page = $_GET['page'];
if ($page == '') {$page = 'Home';}

$active = "id='active'";
$inactive = "";
if ($page == 'Home') {
	$Home = $active;
	$title="A cross-platform schedule tool!";
}
if ($page == 'Downloads') {
	$Home = $active;
	$title="Get Agender";
}
else {
	$Home = $inactive;
	$title = $page;
}

// TODO (virtuoso#1#): add google search here

$error404 = "<center><img src='Agender-screenshot-svn-1.png'><br><br></center>\n".
            "<h3 class='heading'>This page cannot be found <i>try using google</i>.</h3>error 405";


if ($page == 'Downloads') {$Downloads = $active;}
else {$Downloads = $inactive;}

if ($page == 'Screenshots') {$Screenshots = $active;}
else {$Screenshots = $inactive;}

if ($page == 'Links') {$Links = $active;}
else {$Links = $inactive;}

$page_name = $page.'.elf';

$pages = glob("*.elf");

if (in_array($page_name, $pages) and file_exists($page_name)){
    $page_data = file_get_contents($page_name);
}
else {$page_data = $error404;}
?>

<html>
<head>
	<title>Agender - <?php echo $title ?></title>
	<link rel="stylesheet" type="text/css" href="agender.css" media="screen"/>
	<link rel="alternate" type="application/rss+xml"
		href="https://sourceforge.net/export/rss2_keepsake.php?group_id=271084"
		title="Agender - a cross-platform schedule tool!"/>
</head>

<body>
	<!-- menu -->
		<ul id="menu">
		<li><a href="index.php?page=Home">Home</a></li>
		<li><a href="index.php?page=Downloads">Downloads</a></li>
		<li><a href="index.php?page=Press">Press</a></li>
		<li><a href="index.php?page=Screenshots">Screenshots</a></li>
		<li><a href="index.php?page=About">About</a></li>
		<li><a href="index.php?page=Links">Links</a></li>
		</ul>
	

	<!--
	<div class="lshadow"/>
	<div class="rshadow">
-->

	<div class="container">
		<!-- contents -->
		<?php echo $page_data ?>
		<!-- end of contents -->
	</div>
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

