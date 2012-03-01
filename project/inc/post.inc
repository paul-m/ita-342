<?php

require_once 'arraycheck.inc';

/**
 * Session is a static class to deal with the current session.
 */
class Post extends ArrayCheck {
  /**
   * helper method to get a value from $_POST.
   * Pass the name of the key to gather
   * Pass default value you want returned if the variable doesn't exist.
   */
  public static function get($key, $default = NULL) {
    if (isset($_POST)) return parent::get($_POST, $key, $default);
    return $default;
  }

  /**
   * Set session variables.
   */
  public static function set($key = '', $value = 1) {
    if (isset($_POST)) return parent::set($_POST, $key, $value);
    return FALSE;
  }
  
  public static function post_unset($key = '') {
    if (isset($_POST)) parent::arr_unset($_POST, $key);
  }
}
