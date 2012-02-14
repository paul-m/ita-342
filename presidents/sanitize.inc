<?php

//include_once "debug.inc";

// various functions to deal with sanitizing inputs.

function sanitize_schema_input($input = array(), $schema = array()) {
  // return an array made up of key/value pairs from $input,
  // for keys in $schema, with sanitized values.
  $result = array();
  $keys = array_intersect_key($input, $schema);
  echo 'keys';
  foreach($keys as $key=>$value) {
    $funcName = 'sanitize_' . $schema[$key];
    if (function_exists($funcName)) {
      $result[$key] = $funcName($input[$key]);
    }
  }
  return $result;
}

function sanitize_INT($int) {
  // input something and output an int
  if (!is_numeric($int)) return -1;
  return (int) $int;
}

function sanitize_VARCHAR($varchar) {
  // Standard sanitize voodoo for varchar input text
  // heading for a MySQL database.
  if (get_magic_quotes_gpc()) $varchar = stripslashes($varchar);
  return mysql_real_escape_string($varchar);
}
