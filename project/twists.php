<?php
include 'inc/common_head.inc';

include 'site/common_header.html.inc';

require_once 'inc/db.inc';
require_once 'inc/schema.inc';
require_once 'inc/usercrud.inc';
require_once 'inc/twistcrud.inc';
require_once 'inc/superglobals.inc';
require_once 'inc/sanitize.inc';

// this page exists so you can post 'twists,' which is what
// I call tweets in the context of this web app.

// break the DB oop model because that's just how it goes. :-)
// this code is designed to work when I show off my project,
// not in a production environment.

$twistdb = new TwistCRUD;

$twists = $twistdb->load_all_records();

if (count($twists) > 0) {
  $db = DB::connection();
  
  // 'survey_id' is our stand-in for user id.
  $result = $db->query("SELECT DISTINCT survey_id FROM questions");
  $uids = array();
  while ($uid = $result->fetch_assoc()) $uids[$uid['survey_id']] = $uid['survey_id'];
  
  // $uids now contains all the users we'll need.
  // let's load all the users.
  
  $users = array();
  $userdb = new UserCRUD;
  foreach ($uids as $uid=>$foo) {
    $user = $userdb->load_user($uid);
    if ($user) $users[$user['id']] = $user;
  }
  
  // and now we figure out if we have admin privs
  $admin = FALSE;
  $current_user = $userdb->load_user(Session::current_user());
  if ($current_user['id'] > 0) $admin = $current_user['type'] == 'admin';
  
  // start showing stuff.
  echo '<h2>The Big List Of Twists</h2>';
  
  $columns = array('question'=>'Twist');
  
  echo '<table border="1"><tr>';
  // header row
  foreach($columns as $column=>$label) {
    echo '<th>' . $label . '</th>';
  }
  // add authorship
  echo '<th>By</th>';
  if ($admin) {
    // label for extra edit column.
    echo '<th>Edit</th></tr>';
  }
  // ...and now all the twist rows.
  foreach($twists as $twist) {
    echo '<tr>';
    foreach($columns as $key=>$value) {
      echo '<td>' . $twist[$key] . '</td>';
    }
    $user = $users[$twist['survey_id']];
    echo '<td>' . $user['user_name'] . '</td>';
    // add the edit form
    if ($admin) {
      echo '<td><form name = "edittwist" action = "twist.php" method = "GET">';
      echo '<input type="hidden" id="edittwist" name="type" value="edit" />';
      echo '<input type="hidden" id="id_form_thing" name="id" value="' .
        $twist['id'] . '" />';
      echo '<input type="submit" value="Edit" />';
      echo '</form></td>';
    }
    echo '</tr>';
  }
  echo '</table>';
}
// end of normal results... how about if there aren't any twists?
else {
echo "<h2>Sorry, there aren't any twists to lists.</h2>";
echo '<div>Why not <a href="twist.php?type=add">add one</a>?</div>';
}

/*

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
*/

include 'site/common_footer.html.inc';

include 'inc/common_foot.inc';
