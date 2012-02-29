<?php

/**
 * User class wraps some basic user-related stuff in a
 * static class.
 */

require_once 'session.inc';

class User {
  // Only the User class can get the hash salt.
  // Call me paranoid if you must.
  private static $hash_salt = 'mm.salty.';

  /**
   * Need to hash a password? Here's your function.
   */
  public static function hash_password($password) {
    return md5(self::$hash_salt . $password);
  }

  public static function session_user_id() {
    return Session::variable('user_id', -1);
  }

  /**
   * class function logged_in().
   * Return TRUE if the current session reflects a logged-in user.
   */
  public static function logged_in() {
    $user = self::current_user();
    return ($user['id'] > 0);
  }
}
