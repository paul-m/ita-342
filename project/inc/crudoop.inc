<?php

/**
 * OOP on CRUD
 */

require_once 'db.inc';

class CRUDOOP {
  protected $schema;

  function __construct($schema = array()) {
//  echo '<pre>' . var_dump($schema) . '</pre>';
    $this->set_schema($schema);
  }

  function set_schema($schema = array()) {
    $this->schema = $schema;
  }

  /**
   * helper function to convert a unix timestamp to a proper
   * DATETIME, for a given key within the record.
   */
  function convert_unix_to_datetime_for_key($record, $table, $key) {
    if ($this->$schema[$key] == 'DATETIME') {
      // convert the item in the record.
      $timestamp = $record[$key];
      $record[$key] = date("Y-m-d H:i:s", $timestamp);
    }
  }

  /**
   * helper function to convert a DATETIME to a
   * timestamp, for a given key within the record.
   */
  function convert_datetime_to_unix_for_key($record, $table, $key) {
    if ($this->schema[$key] == 'DATETIME') {
      // convert the item in the record.
      $datetime = $record[$key];
      $record[$key] = strtotime($datetime);
    }
  }
  
  /**
   * Given a value and a key, 'entick' string values
   * as determined by the schema. Helper for building
   * SQL queries.
   */
  function sql_value_entick($value, $key) {
//echo "sql_value_entick: $key : $value\n";
    switch ($this->schema[$key]) {
      // textual types get ticks
      // PASSWORD is expected to have been hashed.
      // DATETIME is expected to be formatted properly by caller.
      case 'VARCHAR':
      case 'PASSWORD':
      case 'DATETIME':
        return "'" . $value . "'";
    }
    return $value;
  }

  function write_record($record, $table, $idkey = NULL) {
    // if 'id' is given, then it's an update. otherwise, an insert.
    $keys = array_intersect_key($record, $this->schema);
    // check if the id key exists. if it's not there, insert.
    if (!array_key_exists($idkey, $keys)) {
      // prepare an insert.
      $into = array();
      $values = array();
      foreach ($keys as $key=>$value) { // discard $value
        $into[] = $key;
        $values[] = $this->sql_value_entick($record[$key], $key);
      }
      $queryString = 'INSERT INTO ' . $table . ' (' .
        implode(", ", $into) .
        ") VALUES (" .
        implode(", ", $values) . ")";
    } else { // id key exists, so do an update.
      // prepare an update.
      $set = array();
      foreach ($keys as $key=>$value) {
        $set[$key] = $key . "=" . $this->sql_value_entick($record[$key], $key);
      }
      // remove the id from the SET part of the query
      unset($set[$idkey]);
      $queryString = 'UPDATE ' . $table . ' SET ' .
        implode(", ", $set) .
        " WHERE " . $idkey . " = " . $record[$idkey];
    }
echo "<br><br>SQL: $queryString<br><br>";
if (!$this->db_connection) echo "woops no db!";
    $query = $this->db_connection->query($queryString);
    // TODO: exception for a bad outcome.
  }

  function delete_record($id, $table, $idkey) {
    // for schema, delete record where key = id.
    if ($this->db_connection) {
      $query = $this->db_connection->query("DELETE FROM " . $table .
        ' WHERE ' . $idkey . ' = ' . $id);
      if (!$query) {
        echo "Failed to delete id $id from MySQL.";
      }
    }
  }
  
  function load_all_records($table) {
    if ($this->db_connection) {
      $query = $this->db_connection->query("SELECT * FROM " . $table);
      $i=0;
      $result = array();
      while($i++ < $query->num_rows) {
        $row = $query->fetch_assoc();
        $result[$row['id']] = $row;
      }
      return $result;
    }
    return array();
  }
  
  function load_record($id, $table, $idkey) {
    // for schema, load record where key = id.
    // load a single president into an associative array
    $db_connection = DB::connection();
    if ($db_connection) {
      $query = $db_connection->query("SELECT * FROM " . $table .
        " WHERE " . $idkey . " = " . $id);
      return $query->fetch_assoc();
    }
    return array();
  }
}

