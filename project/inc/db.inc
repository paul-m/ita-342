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
 * Schema is for validation and display.
 *
 * @access public
 * @param Schema name $name. (default: '')
 * @return Array specifying schema for given name.
 */
function get_schema($name = '') {
  $schema = array(
    'users' => array(
      'id' => 'INT',//int(11) NOT NULL auto_increment,
      'type' => 'VARCHAR',// varchar(255) NOT NULL default 'user',
      'first_name' => 'VARCHAR',// varchar(256) default NULL,
      'last_name' => 'VARCHAR',// varchar(256) default NULL,
      'user_name' => 'VARCHAR',// varchar(256) default NULL,
      'password' => 'VARCHAR',// varchar(40) default NULL,
      'hint' => 'VARCHAR',// varchar(40) default NULL,
      'email_address' => 'VARCHAR',// varchar(256) default NULL,
    ),
  );
  return $schema[$name];
}

/*
CREATE TABLE IF NOT EXISTS 'users' (
  'id' int(11) NOT NULL auto_increment,
  'type' varchar(255) NOT NULL default 'user',
  'first_name' varchar(256) default NULL,
  'last_name' varchar(256) default NULL,
  'user_name' varchar(256) default NULL,
  'password' varchar(40) default NULL,
  'hint' varchar(40) default NULL,
  'created' datetime default NULL,
  'modified' datetime default NULL,
  'email_address' varchar(256) default NULL,
  PRIMARY KEY  ('id'),
  KEY 'user_name' ('user_name')
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;
*/