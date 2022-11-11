<?php
//logout.php

if(!isset($_COOKIE["username"]))
{
 header("location:login.php");
}

$jsonData = json_encode(array());
file_put_contents('shopping_cart.json', $jsonData); 

setcookie("username", "", time()-3600);
setcookie("name", "", time()-3600);
setcookie("address", "", time()-3600);
setcookie("zipcode", "", time()-3600);
setcookie("phonenumber", "", time()-3600);
setcookie("email", "", time()-3600);
setcookie("page", "", time()-3600);
setcookie("category", time()-3600);
header("location:login.php");

?>
