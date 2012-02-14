<?php

/**
 * @file Array-based schema abstraction for CRUD
 */

function get_db() {
  return array(
    'db'=> 'paulm77',
    'user' => 'paulm77',
    'password' => 'paulm77',
    'host' => "ovid.u.washington.edu",
    'port' => "2900",
    'table_prefix' => '',
  );
}

function get_schema() {
  return array(
    'id' => 'INT', // unique ID in the database
  //    'delta' => 'INT',
    'first_name' => 'VARCHAR',
    'last_name' => 'VARCHAR',
    'startdate' => 'VARCHAR',
    'enddate' => 'VARCHAR',
    'party' => 'VARCHAR',
  );
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
