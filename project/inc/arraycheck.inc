<?php

/**
 * ArrayCheck is a static class to deal with array checking.
 * Subclass this for various use cases, including superglobals.
 */
class ArrayCheck {

  /**
   * get() checks if the array exists, and has a given key.
   * Returns key for array, or $default otherwise.
   * ex: ArrayCheck::get($_POST, 'id', array('id' => -1));
   */
  public static function arr_get($array, $key, $default = NULL) {
    if ($array && isset($array[$key])) {
      return $array[$key];
    }
    return $default;
  }

  /**
   * Set array for key, if they exist.
   * We do this so we can deal with superglobals that might
   * not exist, like $_SESSION.
   */
  public static function arr_set($array, $key = '', $value = 1) {
    if ($key && $array) {
      $array[$key] = $value;
      return $value;
    }
    return FALSE;
  }
  
  public static function arr_unset($array, $key = '') {
    if ($key && $array) unset($array[$key]);
  }
}
