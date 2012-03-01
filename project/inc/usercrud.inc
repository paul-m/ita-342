<?php

/**
 * UserCRUD consumes user arrays and turns them into database records.
 * It can also load database user records and give you arrays.
 */

require_once 'cruddisplay.inc';
require_once 'user.inc';

class UserCRUD extends CRUDDisplay {

  /**
   * Constructor method.
   */
  function __construct() {
    // UserCRUD only ever deals with the 'users' table.
    parent::__construct('users');
  }

  /**
   * Some 'users' use-cases for write_record().
   */
  function write_user($record = array()) {
    // hash the password on the way out... if it's set.
    // unset the password to update a record without changing it.
    if (isset($record['password'])) {
      $record['password'] = User::hash_password($record[$key]);
    }
    $this->convert_unix_to_datetime_for_key($record, 'modified');
    $this->convert_unix_to_datetime_for_key($record, 'created');
    parent::write_record($record);
  }

  function load_user($id = -1) {
    if ($id < 0) return array('id' => $id);
    $record = parent::load_record($id);
    if ($record) {
      $this->convert_datetime_to_unix_for_key($record, 'modified');
      $this->convert_datetime_to_unix_for_key($record, 'created');
    }
    return $record;
  }
  
  function delete_user($id = -1) {
    if ($id > 0) {
      parent::delete_record($id, $this->table, $this->idkey);
    }
    // TODO: return a success/fail value.
  }

}
