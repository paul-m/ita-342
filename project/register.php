<?php

require_once "inc/db.inc";
require_once "inc/usercrud.inc";

if ($_SERVER['REQUEST_METHOD'] == 'GET') {
  // GET shows us either the register form, maybe with fail message
  // or the success form.
  

} else if ($_SERVER['REQUEST_METHOD'] == 'POST') {
  // POST means user tried to add a user record.
  unset($input['id']);
  $input = sanitize_schema_input($_POST, get_schema('users'));

  // more stuff here.
  
  $cruddy = new UserCRUD(get_db());
  $cruddy->write_record($input, 'users', 'id');
  // form_register_success();
  
}


