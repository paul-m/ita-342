<?php

/***

form maker arrays are like this:

[formname] = array (
  [elementname] = array (
    ['type'] = 'textfield/radiobutton/whatever' // corresponds to HTML elements
    ['required'] = TRUE
    ['schema'] = sub-array of db schema where this data will end up
    
    special case for passwords
    ['type'] = 'password'
    will create two textfields: elementname and elementname_repeat

***/

