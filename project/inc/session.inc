<?php

/**
 * Session is a static class to deal with the current session.
 */
class Session {
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
    if (isset($_SESSION) && isset($_SESSION[$key]))
      return $_SESSION[$key];
    return $default;
  }
  
  /**
   * Set session variables.
   */
  public static function set($key = '', $value = 1) {
    self::start();
    if ($key) {
      if (isset($_SESSION)) {
        $_SESSION[$key] = $value;
      }
    }
  }
  
/*  public static function unset($key = '') {
    self::start();
    if (isset($_SESSION) && isset($_SESSION[$key])) unset($_SESSION[$key]);
  }*/

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
