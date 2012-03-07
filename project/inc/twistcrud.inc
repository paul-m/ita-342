<?php

/**
 * UserCRUD consumes user arrays and turns them into database records.
 * It can also load database user records and give you arrays.
 */

require_once 'arraycheck.inc';
require_once 'superglobals.inc';
require_once 'cruddisplay.inc';

class TwistCRUD extends CRUDDisplay {

  /**
   * Constructor method.
   */
  function __construct() {
    // UserCRUD only ever deals with the 'users' table.
    parent::__construct('questions');
  }

  function write_twist($record = array()) {
    // add user type
    ArrayCheck::set_if_not_set($record, 'type', 'user');
    ArrayCheck::set_if_not_set($record, 'survey_id', -1);
    ArrayCheck::set_if_not_set($record, 'sequence', -1);
    // add modified time, created time if we're doing an insert.
    $record['modified'] = time();
    if (ArrayCheck::arr_get($record, 'id', -1) < 1)
      $record['created'] = time;
    $this->convert_unix_to_datetime_for_key($record, 'modified');
    $this->convert_unix_to_datetime_for_key($record, 'created');
    parent::write_record($record);
  }

  function load_twist($id = -1) {
    if ($id < 0) return array('id' => $id);
    $record = parent::load_record($id);
    if ($record) {
      $this->convert_datetime_to_unix_for_key($record, 'modified');
      $this->convert_datetime_to_unix_for_key($record, 'created');
    }
    return $record;
  }
  
  function delete_twist($id = -1) {
    if ($id > 0) {
      parent::delete_record($id, $this->table, $this->idkey);
    }
  }

}
