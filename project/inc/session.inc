<?php

require_once 'arraycheck.inc';

/**
 * Session is a static class to deal with the current session.
 */
class Session extends ArrayCheck {
  public static function start() {
    return session_start();
  }
  // get or set a session ID.
  public static function id($id = NULL) {
    if ($id) return session_id($id);
    return session_id();
  }
  public static function destroy() {
    return session_destroy();
  }

  /**
   * helper method to get a value from $_SESSION.
   * Pass the name of the key to gather
   * Pass default value you want returned if the variable doesn't exist.
   */
  public static function get($key, $default = NULL) {
    self::start();
    if (isset($_SESSION)) return parent::get($_SESSION, $key, $default);
    return $default;
  }

  /**
   * Set session variables.
   */
  public static function set($key = '', $value = 1) {
    self::start();
    if (isset($_SESSION)) return parent::set($_SESSION, $key, $value);
    return FALSE;
  }
  
  public static function sess_unset($key = '') {
    self::start();
    if (isset($_SESSION)) parent::arr_unset($_SESSION, $key);
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
