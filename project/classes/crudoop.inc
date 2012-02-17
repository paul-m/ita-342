<?php

/**
 * OOP on CRUD
 */

class CRUDOOP {

  private $db_connection; // mysqli object
  private $db_info; // db credentials/server info

  function __construct($db = array()) {
    $this->db_connect($db);
  }
  
  function __destruct() {
    $this->db_disconnect();
  }

  function db_connect($db = array()) {
    // init db connection.
    $this->db_connection = new mysqli($db['host'], $db['user'], $db['password'], $db['database'], $db['port']);
    $this->db_info = $db;
    if ($this->db_connection->connect_errno) {
      // this should be an exception.
      echo "Failed to connect to MySQL: " . $this->db_connection->connect_error;
      $this->db_connection = NULL;
      $this->db_info = NULL;
    }
    return $this->db_connection;
  }

  function db_disconnect() {
    // close db connection.
    if ($this->db_connection) {
      $this->db_connection->close();
      $this->db_connection = NULL;
      $this->db_info = NULL;
    }
  }

  function write_record($record, $table, $idkey = NULL) {
    // if 'id' is given, then it's an update. otherwise, an insert.
    // if there's no id, then this is an insert.
    $schema = get_schema($table);
    $keys = array_intersect_key($record, $schema);
    if (!array_key_exists($idkey, $keys)) {
      // prepare an insert.
      $into = array();
      $values = array();
      foreach ($keys as $key=>$value) { // discard $value
        $into[] = $key;
        $values[] = $record[$key];
      }
      // in this case I know that all columns are strings, so
      // it's easy to put the ticks around them.
      $queryString = 'INSERT INTO ' . $table . ' (' .
        implode(", ", $into) .
        ") VALUES ('" .
        implode("', '", $values) . "')";
    } else {
      // prepare an update.
      $set = array();
      foreach ($keys as $key=>$value) {
        $set[$key] = $key . "='" . $record[$key] . "'";
      }
      // remove the id from the SET part of the query
      unset($set[$idkey]);
      $queryString = 'UPDATE ' . $table . ' SET ' .
        implode(", ", $set) .
        " WHERE " . $idkey . " = " . $record[$idkey];
    }
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
    if ($this->db_connection) {
      $query = $this->db_connection->query("SELECT * FROM " . $table .
        " WHERE " . $idkey . " = " . $id);
      return $query->fetch_assoc();
    }
    return array();
  }
}

