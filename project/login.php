<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN"
  "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html><head><title>Rate-O-Rama!</title></head><body>

<?php

if (strtolower($_SERVER['REQUEST_METHOD']) == 'POST') {
  // process login post from this page.
  
  
  
} else if (strtolower($_SERVER['REQUEST_METHOD']) == 'get') {
  // request is either for a login form or to logout.
  $type = '';
  if (isset($_GET['TYPE'])) $type = $_GET['TYPE'];
echo $type;  
  if ($type == 'logout') {
    // User wants to logout.
    // We'd need to kill the session once we learn how. :-)
    echo '<div>woot you logged out.</div>';
  }
  if ($type == 'login' || $type == '') {
    // User wants to login. Show them the form.
    echo <<<END
<form id='login' action='<?php $_SERVER['PHP_SELF']; ?>' method='post' accept-charset='UTF-8'>
<fieldset >
<legend>Login</legend>
<input type='hidden' name='submitted' id='submitted' value='1'/>
<label for='user_name' >UserName*:</label>
<input type='text' name='user_name' id='user_name'  maxlength="50" />
<label for='password' >Password*:</label>
<input type='password' name='password' id='password' maxlength="50" />
<input type='submit' name='Submit' value='Submit' />
</fieldset>
</form>
END;

  } // end of login
} // end of GET type.
?>

</body></html>