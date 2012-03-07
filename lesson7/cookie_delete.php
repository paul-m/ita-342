<?
setcookie('username', 'Bob', time()-1, '/', '', 0);
echo 'user name is ' . $_COOKIE['username'];
?>