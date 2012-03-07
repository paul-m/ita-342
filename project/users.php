<?php
include 'inc/common_head.inc';

include 'site/common_header.html.inc';

require_once 'inc/schema.inc';
require_once 'inc/usercrud.inc';
require_once 'inc/superglobals.inc';
require_once 'inc/sanitize.inc';


$request_method = Server::request_method();
if ($request_method == 'GET') {
  // GET means:
  // 0) If we have a user=x param, show that user
  // 0.5) If we have user=x param and user is admin, edit/delete that user.
  // 1) Not logged in: List users minimal
  // 2) Logged in: List users minimal
  // 3) Logged in admin: List users w/ admin function
  
  $admin = FALSE;
  $userID = Session::current_user();
  if ($userID > 0) {
    // user is logged in.
    // figure out if they're an admin.
    $userdb = new UserCRUD;
    $user = $userdb->load_user($userID);
    $admin = ($user['type'] == 'admin');
  }
  
  // let's show a big table of users.
  $userdb = new UserCRUD;
  $users = $userdb->load_all_records();
//  echo '<pre>'; var_dump($users); echo '</pre>';

  echo '<h2>The Big List Of Users</h2>';

  $columns = array('first_name'=>'First name', 'last_name'=>'Last name', 'user_name'=>'Username');
  
  echo '<table border="1"><tr>';
  // header row
  foreach($columns as $column=>$label) {
    echo '<th>' . $label . '</th>';
  }
  if ($admin) {
    // label for extra edit column.
    echo '<th>Edit</th></tr>';
  }
  // ...and now all the president rows.
  foreach($users as $user) {
    echo '<tr>';
    foreach($columns as $key=>$value) {
      echo '<td>' . $user[$key] . '</td>';
    }
    // add the edit form
    if ($admin) {
      echo '<td><form name = "edituser" action = "user.php" method = "GET">';
      echo '<input type="hidden" id="edit_prez" name="type" value="edit" />';
      echo '<input type="hidden" id="id_form_thing" name="id" value="' .
        $user['id'] . '" />';
      echo '<input type="submit" value="Edit" />';
      echo '</form></td>';
    }
    echo '</tr>';
  }
  echo '</table>';

// end of GET.
}

include 'site/common_footer.html.inc';

include 'inc/common_foot.inc';
