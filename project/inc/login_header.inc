<?php

// Show the login/logout link for all pages.

require_once 'user.inc';

if (User::logged_in()) {
  $path = 'login.php?type=logout';
  $text = 'Logout';
} else {
  $path = 'login.php?type=login';
  $text = 'Login';
}
echo '<div><a href="' . $path . '">' . $text . '</a></div>';
