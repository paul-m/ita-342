<?php

/**
 * @file schema.inc defines some functions and data structures
 * for the data we're representing.
 * DB abstraction, validation, and display are all keyed off
 * this array structure.
 */


/*

  The data structure is like this:
  
  array(
  
    [tablename]
      [columnname]
        ['type'] // eg VARCHAR, INT, DATETIME, PASSWORD
        ['sanitize'] // similar to db_type. appended to sanitize_ for function name.
        ['form'] // for input form
          ['type'] // type of element: textarea, checkbox, etc.
                   // radiobuttons not allowed at the moment.
                   // 'password' gets special treatment: two form elements to compare,
                   // one named columnname and one named columname_compare.
                   // Will need special way to work out whether we're on a login
                   // form or a register form.
          ['label'] // human-readable display label for element
          ['required'] // if not present, FALSE. set TRUE to require this element.
        ['display']
          // might not actually need this. we'll see. similar to ['form']

    )
  
  */


function get_schema($table) {
  $schema = array(
    'users' => array (
      '#UNIQUEID' => 'id',
      'id' => array(
        'type' => 'INT',
        'sanitize' => 'INT',
        'form' => array (
          'type' => 'hidden',
          'display' => 'hidden',
        ),
      ),
      'type' => array(
        'type' => 'VARCHAR',
        'sanitize' => 'VARCHAR',
        'form' => array (
          'type' => 'hidden',
          'display' => 'hidden',
        ),
      ),
      'first_name' => array(
        'type' => 'VARCHAR',
        'sanitize' => 'VARCHAR',
        'form' => array (
          'type' => 'text',
          'label' => 'First name',
        ),
      ),
      'last_name' => array(
        'type' => 'VARCHAR',
        'sanitize' => 'VARCHAR',
        'form' => array (
          'type' => 'text',
          'label' => 'Last name',
        ),
      ),
      'user_name' => array(
        'type' => 'VARCHAR',
        'sanitize' => 'VARCHAR',
        'form' => array (
          'type' => 'text',
          'label' => 'Username',
        ),
      ),
      'password' => array(
        'type' => 'VARCHAR',
        'sanitize' => 'PASSWORD',
        'form' => array (
          'type' => 'password',
          'display' => 'password',
          'label' => 'Password',
        ),
      ),
      'hint' => array(
        'type' => 'VARCHAR',
        'sanitize' => 'VARCHAR',
        'form' => array (
          'type' => 'text',
          'display' => 'hidden',
          'label' => 'Hint',
        ),
      ),
      'email_address' => array(
        'type' => 'VARCHAR',
        'sanitize' => 'EMAIL',
        'form' => array (
          'type' => 'text',
          'label' => 'Email',
        ),
      ),
    ),
  );
  if (isset($schema[$table])) return $schema[$table];
  return array();
}