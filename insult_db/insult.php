<?php # Script 3.17 - sik.php
// Set the page title and include the HTML header.
$page_title = 'Shakespeare Insult Kit';
include ('./header.inc');
include ('./insults.inc');

function post_getter($key, $value) {
  if (isset($_POST[$key])) return $_POST[$key];
  else return $value;
}

function post_exists_any($keys = array()) {
  foreach ($keys as $key) {
    if (post_getter($key, NULL) != NULL)
      return TRUE;
  }
  return FALSE;
}

if(isset($_POST['insult'])){
  // This form has been populated with choices by the user.
  // Gather values of the dropdowns.
  $error = FALSE;
  $in1 = post_getter('insult1', 'formitous');
  $in2 = post_getter('insult2', 'unformed');
  $in3 = post_getter('insult3', 'form-changer');
  // handle random checkboxes
  if (post_exists_any(array('random_insult1', 'random_insult2', 'random_insult3'))) {
    $insults = load_insults();
    if ($insults) {
      if (post_getter('random_insult1', NULL))
        $in1 = $insults['adv1'][array_rand($insults['adv1'])];
      if (post_getter('random_insult2', NULL))
        $in2 = $insults['adj2'][array_rand($insults['adj2'])];
      if (post_getter('random_insult3', NULL))
        $in3 = $insults['noun3'][array_rand($insults['noun3'])];
    } else {
      $error = TRUE;
    }
  }
  if (!$error) {
    echo '<div id="insult">Thou art a ' . "$in1, $in2, $in3!" . '</div>';
    echo '<p>Shall I <a href="' . $_SERVER['PHP_SELF'] . '">insult you again</a>?</p>';
  } else {
    echo '<div id="insult">Unable to generate an insult.</div>';
    echo '<p>Shall we <a href="' . $_SERVER['PHP_SELF'] . '">try again</a>?</p>';
  }
}else{
  // Ask the user for their choices
  // This function makes three pull down menus
  function make_insult_pulldowns($insults, $this_insult1 = NULL,$this_insult2 = NULL,$this_insult3 = NULL) {
  	// Make the insult array.
  	// Make the pull down menus.
    make_pulldown("insult1", $insults['adv1'], $this_insult1);
    make_pulldown("insult2", $insults['adj2'], $this_insult2);
    make_pulldown("insult3", $insults['noun3'], $this_insult3);
    echo '<br>';
    make_checkbox("random_insult1", 1);
    make_checkbox("random_insult2", 1);
    make_checkbox("random_insult3", 1);
  
  } // End of the make_insult_pulldown() function.
  
  /**
   * Construct pulldown select elements.
   */
  function make_pulldown($name, $items = array(), $current = '') {
    echo '<select name="' . $name . '">';
    foreach ($items as $key=>$value) {
      echo "<option value =\"$value\"";
      if ($value == $current) echo ' selected="selected"';
      echo ">$value</option>\n";
    }
  	echo '</select>';
  }
  
  function make_checkbox($name, $value = 1, $checked = 'checked') {
    echo
      '<input type="checkbox" name="'. $name .
      '" value="'. $value .
      '" checked = "' . $checked .
      '" />';
  }
  ?>
  
  <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
  
  <?
  make_insult_pulldowns(load_insults()); // Make the insult.
  echo '<div align="left"><input type="submit" name="insult" value="insult!" /></div>';
  echo '</form>'; // End of form.
}//end of if\else statement

include ('./footer.inc'); // Include the HTML footer.
?>