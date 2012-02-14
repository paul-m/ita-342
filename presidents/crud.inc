<?php

include_once "db.inc";
include_once "sanitize.inc";
//include_once "debug.inc";

/*
   We want to use object-oriented mysqli for this project because
   we like OOP and because I want to learn it. So there.
*/

function crud_president_db_connect(&$mysqli = NULL) {
  // create a new connection if one is needed.
  // return TRUE if we created one.
  if ($mysqli) {
    return FALSE;
  }
  $db = get_db();
  $mysqli = new mysqli($db['host'], $db['user'], $db['password'], $db['db'], $db['port']);
  if ($mysqli->connect_errno) {
    echo "Failed to connect to MySQL: " . $mysqli->connect_error;
    return FALSE;
  }
  return TRUE;
}

function crud_president_load_all() {
  // load all presidents. there aren't that many.
  $mysqli = NULL;
  crud_president_db_connect($mysqli);
  if ($mysqli) {
    $query = $mysqli->query("SELECT * FROM presidents ORDER BY startdate ASC");//
    $i=0;
    $result = array();
    while($i++ < $query->num_rows) {
      $row = $query->fetch_assoc();
      $result[$row['id']] = $row;
    }
    $mysqli->close();
    return $result;
  }
  return array();
}

function crud_president_load_by_id($id, $mysqli = NULL) {
  // load a single president into an associative array
  $shouldClose = crud_president_db_connect($mysqli);
  $query = $mysqli->query("SELECT * FROM presidents WHERE id = " . $id);//
  if ($shouldClose) $mysqli->close();
  return $query->fetch_assoc();
}

function crud_president_delete_by_id($id, $mysqli = NULL) {
//echo 'deleting prez: ' . $id;
  $shouldClose = crud_president_db_connect($mysqli);
  $query = $mysqli->query("DELETE FROM presidents WHERE id = " . $id);
  if (!$query) {
    echo "Failed to delete id $id from MySQL.";
  }
  if ($shouldClose) $mysqli->close();
}

function crud_president_insert($data, $mysqli = NULL) {
  // $data is in the form 'key'=>'value' where key is the column
  // and value is the value. since this is insert, we don't need
  // an id column; one will be generated.
  if (array_key_exists('id', $data)) unset($data['id']);
  $keys = array_intersect_key($data, get_schema());
  $into = array();
  $values = array();
  foreach ($keys as $key=>$value) {
    $into[] = $key;
    $values[] = $data[$key];
  }
  // in this case I know that all columns are strings, so
  // it's easy to put the ticks around them.
  $queryString = 'INSERT INTO presidents (' .
    implode(", ", $into) .
    ") VALUES ('" .
    implode("', '", $values) . "')";
  $shouldClose = crud_president_db_connect($mysqli);
  $query = $mysqli->query($queryString);
  $result = crud_president_load_by_id($mysqli->insert_id, $mysqli);
  if ($shouldClose) $mysqli->close();
  return $result;
}

function crud_president_update($data, $mysqli = NULL) {
  // if there's no id, then this is an insert.
  if (!array_key_exists('id', $data))
    return crud_president_insert($data, $mysqli);
  $keys = array_intersect_key($data, get_schema());
  $set = array();
  foreach ($keys as $key=>$value) {
    $set[$key] = $key . "='" . $data[$key] . "'";
  }
  unset($set['id']);
  // in this case I know that all columns are strings, so
  // it's easy to put the ticks around them.
  $queryString = 'UPDATE presidents SET ' .
    implode(", ", $set) .
    " WHERE id = " . $data['id'];
  $shouldClose = crud_president_db_connect($mysqli);
  $query = $mysqli->query($queryString);
  $result = crud_president_load_by_id($data['id'], $mysqli);
  if ($shouldClose) $mysqli->close();
  return $result;
}






