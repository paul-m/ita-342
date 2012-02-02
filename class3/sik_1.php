<?php # Script 3.17 - sik.php
// Set the page title and include the HTML header.
$page_title = 'Shakespeare Insult Kit';
include ('./header.inc');
include ('./insults.inc');

if(isset($_POST['insult'])){
  // This form has been populated with choices by the user.
  // handle form
  $in1 = $_POST['insult1'];
  $in2 = $_POST['insult2'];
  $in3 = $_POST['insult3'];
  // handle random checkboxes
  if ($_POST['random_insult1']) $in1 = $insult_1[array_rand($insult_1)];
  if ($_POST['random_insult2']) $in2 = $insult_2[array_rand($insult_2)];
  if ($_POST['random_insult3']) $in3 = $insult_3[array_rand($insult_3)];
  
  echo "<b>Thou art a $in1, $in2, $in3!</b>";
}else{
  // Ask the user for their choices
  // This function makes three pull down menus
  function make_insult_pulldowns($this_insult1 = NULL,$this_insult2 = NULL,$this_insult3 = NULL) {
    global $insult_1;
    global $insult_2;
    global $insult_3;
  	// Make the insult array.
  	// Make the pull down menus.
    make_pulldown("insult1", $insult_1, $this_insult1);
    make_pulldown("insult2", $insult_2, $this_insult2);
    make_pulldown("insult3", $insult_3, $this_insult3);
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
//      '<label for="' . $name . '">' . $label . '</label>' .
      '<input type="checkbox" name="'. $name .
      '" value="'. $value .
      '" checked = "' . $checked .
      '" />';
  }
  ?>
  
  <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
  
  <?
  make_insult_pulldowns(); // Make the insult.
  echo '<div align="left"><input type="submit" name="insult" value="insult!" /></div>';
  echo '</form>'; // End of form.
}//end of if\else statement

include ('./footer.inc'); // Include the HTML footer.
?>