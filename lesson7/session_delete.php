<?
session_start();
unset($_SESSION['username']);
$_SESSION = array();
session_destroy();
setcookie('phpsessid', '', time()-300, '/', '', 0);
?>