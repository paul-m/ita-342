<?php

/**
 * @file Array-based schema abstraction for CRUD
 */

/**
 * get_db function.
 * 
 * @access public
 * @return Array with database credentials.
 */
function get_db() {
  return array(
    'database'=> 'paulm77',
    'user' => 'paulm77',
    'password' => 'paulm77',
    'host' => "ovid.u.washington.edu",
    'port' => "2900",
    'table_prefix' => '',
  );
}

/**
 * get_schema function.
 * 
 * @access public
 * @param Schema name $name. (default: '')
 * @return Array specifying schema for given name.
 */
function get_schema($name = '') {
  $schema = array(
    'presidents' => array(
      'id' => 'INT', // unique ID in the database
    //    'delta' => 'INT',
      'first_name' => 'VARCHAR',
      'last_name' => 'VARCHAR',
      'startdate' => 'VARCHAR',
      'enddate' => 'VARCHAR',
      'party' => 'VARCHAR',
    ),
  );
  return $schema[$name];
}

/*
CREATE TABLE presidents (
    id INT UNSIGNED AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    startdate VARCHAR(4) DEFAULT NULL,
    enddate VARCHAR(4) DEFAULT NULL,
    party VARCHAR(90),
);
*/
