<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html><head><title>Rate-O-Rama!</title></head>

<?php
// display login/logout link based on login status
//require_once 'inc/login_header.inc';
?>

<div><h1>Welcome to Rate-O-Rama!</h1></div>

<div><a href="add.php">Add Item</a></div>

<div><h2>Rated Items</h2></div>

<?php

require_once 'inc/usercrud.inc';

$user_db = new UserCRUD;
$user = $user_db->load_user(1);

echo '<pre>';
print_r($user);
echo '</pre>';

?>

</html>
