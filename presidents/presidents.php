<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">
<html><body>
<?php

include_once "db.inc";
include_once "crudoop.inc";
include_once "sanitize.inc";
include_once "forms.inc";

// Create a magic db abstraction object.
// We could put this off until just before we
// need to query, but for now we're testing
// CRUDOOP, not efficiency.
$cruddy = new CRUDOOP(get_db());

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
    form_one_president($cruddy->load_record($id), get_schema('presidents'));
  } else {
    // show big form
    form_all_presidents($cruddy->load_all_records(), get_schema('presidents'));
  }
} else if ($_SERVER['REQUEST_METHOD'] == 'POST') {
  // POSTed forms can do one of three things: add, edit, or delete.
  if (!empty($_POST['type'])) {
    $type = $_POST['type']; // save some typing
    switch ($type) {
      case 'delete':
        // delete item
        $cruddy->delete_record(sanitize_int($_POST['id']));
        break;
      case 'add':
      case 'edit':
        $input = sanitize_schema_input($_POST, get_schema());
        if ($type == 'add') unset($input['id']);
        $cruddy->write_record($input);
        break;
    }
  }
  form_all_presidents($cruddy->load_all_records(), get_schema());
} else {
  echo "<h2>Unsure what you're requesting.</h2>";
  form_all_presidents($cruddy->load_all_records(), get_schema());
}

?>
</body></html>
