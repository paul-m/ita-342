<?php

// generate the UI forms for the presidents.

function form_all_presidents($presidents, $schema) {
  // given all the presidents, make a nice display table.
  // use db column names for headers.
  reset($schema);
  reset($presidents);
  // table elements
  // add president form
  echo '<form name = "addprezform" action = "'. $_SERVER['PHP_SELF'] . '" method = "GET">';
  echo '<label for="add_prez">Add a President:</label>';
  echo '<input type="hidden" id="add_prez" name="type" value="add" />';
  echo '<input type="submit" value="Add" />';
  echo '</form>';
  echo '<br>';
  echo '<table border="1"><tr>';
  // header row
  foreach($schema as $header=>$value) {
    echo '<th>' . $header . '</th>';
  }
  // label for extra edit column.
  echo '<th>Edit</th></tr>';
  // ...and now all the president rows.
  foreach($presidents as $president) {
    echo '<tr>';
    foreach($schema as $key=>$value) {
      echo '<td>' . $president[$key] . '</td>';
    }
    // add the edit form
    echo '<td><form name = "editprezform" action = "'. $_SERVER['PHP_SELF'] . '" method = "GET">';
    echo '<input type="hidden" id="edit_prez" name="type" value="edit" />';
    echo '<input type="hidden" id="id_form_thing" name="id" value="' .
      $president['id'] . '" />';
    echo '<input type="submit" value="Edit" />';
    echo '</form></td>';
    echo '</tr>';
  }
  echo '</table>';
}

function form_one_president($president, $schema) {
  // make a form for the one president, including a delete button.
  // $president might be null, given that we're adding a president
  if (!$president) $president = array();
  echo '<h2>Edit a President</h2>';
  // edit form.
  echo '<form name="editAPrez" action="'. $_SERVER['PHP_SELF'] . '" method="POST">' . "\n";
  // figure out if this is an update or an add
  $actionType = $_GET['type']; // this should be an argument
  if ($actionType == 'add') {
    // put empty value in each key so we don't have to check for the form.
    foreach($schema as $key=>$value) {
      $president[$key] = '';
    }
    unset($president['id']);
    $president['last_name'] = 'fooo barrrr';
  }
  echo '<input type="hidden" id="action_type" name="type" value="' . $actionType . '" />' . "\n";
  if ($actionType == 'update') {
    echo '<input type="hidden" id="prez_id" name="id" value="' . $president['id'] . '" />' . "\n";
  }
  foreach ($schema as $key=>$value) {
    // make the form elements for each row on the table
    // except id. There should be another row for the president count, rather than using id.
    if ($key != 'id') {
      echo '<label for="' . $key . '">' . $key . ':</label>';
      echo '<input type="text" id="' . $key . '" name="' . $key . '" value="' . $president[$key] . '" /><br />' . "\n";
    }
  }
  echo '<input type="submit" value="Submit" />' . "\n";
  echo '</form>';

  // delete form, separate from the edit form.
  if ($actionType == 'edit') {
    echo '<form name="deleteAPrez" action="'. $_SERVER['PHP_SELF'] . '" method="POST">';
    echo '<input type="hidden" id="action_type" name="type" value="delete" />';
    echo '<input type="hidden" id="prez_id" name="id" value="' . $president['id'] . '" />';
    echo '<input type="submit" value="Delete" />';
    echo '</form>';
  }
}
