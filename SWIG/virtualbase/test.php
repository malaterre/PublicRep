<?php
require_once( 'demo.php' );

Ko::threats();

$t = new base();
if( is_resource($t) )
{
echo "toto";
}
else
{
echo "bla";
}
//echo get_resource_type($t);

$d = base::create_concrete();
//if( is_resource($d) )
//{
//echo "toto4";
//echo get_resource_type($d);
//}
$d->foo();

$c = create_concrete_for_swig();
//$c = create_concrete_for_php();
//$c.foo();
if( is_resource($c) )
{
echo "toto2";
echo get_resource_type($c);
}
else
{
echo "toto3";
}

?>
