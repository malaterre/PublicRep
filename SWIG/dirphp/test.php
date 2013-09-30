<?php
require_once( 'demo.php' );

$a = new concrete();
$a->foo();
$b = new base();
$b->foo();

$d = create_concrete();
if( is_resource($d) )
  echo get_resource_type($d);
$d->foo(); // fatal error !

?>
