<?php

require_once 'crudoop.inc';
require_once 'arraycheck.inc';

class CRUDDisplay extends CRUDOOP {

  // return HTML as a nice display of the data.
  // we'll just make a table for now. easy to process.
  function html_display($id = -1) {
//    if ($id < 0) return "<div><h3>Unable to load non-existent record.</h3></div>";
//echo "loading: $id";
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
      $record = array($this->idkey => $id);
    }
    $table = array();
    $schema = $this->schema;
    $html = '';
    foreach($schema as $db_col=>$info) {
      $display_info = ArrayCheck::arr_get($info, 'form', NULL);
      // we don't want to show #uniqueid.
      // there's probably a better way to structure this.
      if ($display_info && (!($db_col == '#UNIQUEID'))) {
        if ($display_info['type'] != 'hidden') {
          $html .= '<label for="' . $db_col . '">' . $display_info['label'] . "</label>\n";
        }
        $html .= '<input type="' . $display_info['type'] .
          '" name="' . $db_col . 
          '" value="' . ArrayCheck::arr_get($record, $db_col, '') . '" /><br>' . "\n";
      }
    }
    return $html;
  }

  // dump our table to an XML file.
  function xml_to_file($filepointer = NULL) {
//    if (!$filepointer) return;
    $xml = '';
echo 'xml_to_file...';
    $data = $this->load_all_records();
    echo '<pre>'; print_r($data); echo '</pre>';
    $xml .= '<?xml version="1.0" ?>' . "\r\n" .
      '<' . $this->table . ">\r\n";
    foreach($data as $recordID=>$record) {
      $xml .= '<recordtype ID="' . $recordID . '">' . "\r\n";
      foreach($record as $key=>$value) {
        $xml .= "<$key>" . $value . "/$key>";
      }
    }

    echo $xml;
  }
/*
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
*/
}



