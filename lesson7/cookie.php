<?
setcookie('username', 'Bob', time()+3600, '/', '', 0);
echo 'user name is ' . $_COOKIE['username'];
?>