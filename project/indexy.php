<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html><head><title>Rate-O-Rama!</title></head>

<?php

error_reporting(E_ALL);

// display login/logout link based on login status
//require_once 'inc/login_header.inc';
?>

<div><h1>Welcome to Rate-O-Rama!</h1></div>

<div><a href="add.php">Add Item</a></div>

<div><h2>Rated Items</h2></div>

<?php

require_once 'inc/usercrud.inc';

$userDB = new UserCRUD;

$user = $userDB->load_user(28);

//echo '<form name="input" action="html_form_action.asp" method="get">';

echo $userDB->html_display(28);

//echo '<input type="submit" value="Submit" />';

//echo '<pre>'; var_dump($user); echo '</pre>';

?>

</html>
