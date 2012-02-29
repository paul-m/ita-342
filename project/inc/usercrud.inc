<?php

/**
 * UserCRUD consumes user arrays and turns them into database records.
 * It can also load database user records and give you arrays.
 */

require_once 'crudoop.inc';
require_once 'db.inc';
require_once 'user.inc';

class UserCRUD extends CRUDOOP {
  private $table = 'users';
  private $idkey = 'id';

  /**
   * Constructor method.
   */
  function __construct() {
    parent::__construct(get_schema($this->table));
  }

  /**
   * We want to hash the password on the way to the DB.
   */
  function write_user($record) {
    if ($id < 0) return FALSE;
    foreach ($this->schema as $column->$type) {
      // todo: convert this to key union like in crudoop.
      if ($type == 'PASSWORD') {
        $record[$key] = User::hash_password($record[$key]);
      }
    }
    parent::write_record($record, $this->table, $this->idkey);
  }

  function load_user($id) {
    if ($id < 0) return array('id' => $id);
    return parent::load_record($id, $this->table, $this->idkey);
  }
  
  function delete_user($id = NULL) {
    if ($id) {
      parent::delete_record($id, $this->table, $this->idkey);
    }
  }
}
