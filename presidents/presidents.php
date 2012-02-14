<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">
<html><body>
<?php

include_once "db.inc";
include_once "crud.inc";
include_once "sanitize.inc";
include_once "forms.inc";

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
  if (!empty($_GET['type'])) {
    switch ($_GET['type']) {
      case 'add':
        $id = -1;
        break;
      case 'edit':
        $id = $_GET['id'];
        if (!is_numeric($id)) $id = -1;
    }
    form_one_president($id, get_schema());
  } else {
    // show big form
    form_all_presidents(crud_president_load_all(), get_schema());
  }
} else if ($_SERVER['REQUEST_METHOD'] == 'POST') {


  // POSTed forms can do one of three things: add, edit, or delete.
  if (!empty($_POST['type'])) {
    $type = $_POST['type']; // save some typing
    switch ($type) {
      case 'delete':
        // delete item
        crud_president_delete_by_id(sanitize_INT($_POST['id']));
        break;
      case 'add':
        $input = sanitize_schema_input($_POST, get_schema());
        crud_president_insert($input);
        break;
      case 'edit':
        $input = sanitize_schema_input($_POST, get_schema());
        crud_president_update($input);
        break;
    }
  }
  // show the big list.
  form_all_presidents(crud_president_load_all(), get_schema());
} else {
  echo "<h2>Unsure what you're requesting.</h2>";
  form_all_presidents(crud_president_load_all(), get_schema());
}

?>
</body></html>
