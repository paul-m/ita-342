<?php

require_once 'arraycheck.inc';

/**
 * Session is a static class to deal with the current session.
 */
class Cookie extends ArrayCheck {
  /**
   * helper method to get a value from $_COOKIE.
   * Pass the name of the key to gather
   * Pass default value you want returned if the variable doesn't exist.
   */
  public static function get($key, $default = NULL) {
    if (isset($_COOKIE)) return parent::get($_COOKIE, $key, $default);
    return $default;
  }

  /**
   * Set session variables.
   */
  public static function set($key = '', $value = 1) {
    if (isset($_COOKIE)) return parent::set($_COOKIE, $key, $value);
    return FALSE;
  }
  
  public static function sess_unset($key = '') {
    if (isset($_COOKIE)) parent::arr_unset($_COOKIE, $key);
  }

  /**
   * if a user is logged in, return their id.
   * -1 otherwise.
   */
  public static function current_user() {
    self::start();
    // we use the name of the db table, so 'users,'
    // rather than 'user.'
    $user = self::get('users', NULL);
    if ($user && exists($user['id'])) return $user['id'];
    return -1;
  }
  
  /**
   * Display messages sent from previous forms.
   */
  public static function show_message($function = '') {
    self::start();
    if ($function) return $function(self::get('messages', array()));
    return self::get('messages', array());
  }
}
