<?php
$page = $_GET['page'];
if ($page == '') {$page = 'home';}

$active = "id='active'";
$inactive = "";
if ($page == 'home') {
	$home = $active;
	$title="Agender";
}
else {
	$home = $inactive;
	$title = $page;
}


$error404 = "<center><img src='Agender-screenshot-svn-1.png'><br><br></center>\n".
            "<h3 class='heading'>This cannot be a page <i>since it doesn't exist</i>.</h3>error 405";


if ($page == 'get-agender') {$get-agender = $active;}
else {$get-agender = $inactive;}

if ($page == 'screenshots') {$screenshots = $active;}
else {$screenshots = $inactive;}

if ($page == 'links') {$links = $active;}
else {$links = $inactive;}

$page_name = $page.'.html';

$pages = glob("*.html");

if (in_array($page_name, $pages) and file_exists($page_name)){
    $page_data = file_get_contents($page_name);
}
else {$page_data = $error404;}
?>

<html>
<head>
	<title>Agender - <?= $title ?></title>
	<link rel="stylesheet" type="text/css" href="agender.css" media="screen"/>
	<link rel="alternate" type="application/rss+xml"
		href="rss.xml" title="Agender - a cross-platform schedule tool!"/>
</head>

<body>
	<div class="lshadow">
	<div class="rshadow">
	<div class="container">
		<!-- contents -->
		<?= $page_data ?>
		<!-- end of contents -->
	</div>
	</div>
	</div>
</body>

</html>

