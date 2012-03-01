<?php

require_once 'crudoop.inc';

class CRUDDisplay extends CRUDOOP {

  // return HTML as a nice display of the data.
  // we'll just make a table for now. easy to process.
  function html_display($id = -1) {
    if ($id < 0) return "<div><h3>Unable to load non-existent record.</h3></div>";
    $record = $this->load_record($id);
    if ($record) {
      $table = array();
      $schema = $this->schema;
      foreach($schema as $db_col=>$info) {
        $display_info = NULL;
        if (isset($info['form'])) $display_info = $info['form'];
        if ($display_info && ($db_col != '#UNIQUEID')) {
          if (isset($display_info['display']) && ($display_info['display'] != 'hidden')) {
            $label = $db_col;
            if (isset($display_info['label'])) $label = $display_info['label'];
            $text = $record[$db_col];
            if ($display_info['display'] == 'password') $text = '*****';
            $table[$db_col] = array ($label => $text);
          }
        }
      }
      if (count($table) < 1)
        return "<div><h3>Unable to display user id: $user_id.</h3></div>";

      // now we have $table which is full of lovely info.
      // let's make a chart.
      $html = '<table border="0">';
      foreach($table as $foo=>$row) {
        $html .= '<tr>';
        foreach($row as $key=>$value) {
          $html .= '<td>' . $key . ':</td><td>' . $value . '</td>';
        }
        $html .= '</tr>';
      }
      return $html;

//      print_r($table);
    } else {
    return "<div><h3>Unable to load user for display. id: $user_id.</h3></div>";
    }
  }


  // return HTML as a form for entering the data.
  // caller must supply their own <form> tag and submit button.
  function html_form($id = -1) {
    if ($id > 0) {
      $record = $this->load_record($id);
    } else {
      $record = array($idkey => $id);
    }
    $table = array();
    $schema = $this->schema;
    $html = '';
    foreach($schema as $db_col=>$info) {
      $display_info = NULL;
      if (isset($info['form'])) $display_info = $info['form'];
//      echo '<pre>'; print_r($display_info); echo '</pre>';
      // we don't want to show #uniqueid.
      // there's probably a better way to structure this.
      if ($display_info && (!($db_col == '#UNIQUEID'))) {
        if ($display_info['type'] != 'hidden') {
          $html .= '<label for="' . $db_col . '">' . $display_info['label'] . "</label>\n";
        }
        $html .= '<input type="' . $display_info['type'] .
          '" name="' . $db_col . 
          '" value="' . $record[$db_col] . '" /><br>' . "\n";
      }
    }
    return $html;
  }
}



