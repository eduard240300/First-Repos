<?php
//shopping_cart.php

include_once("controller.php");
$controller = new Controller();

if(!isset($_COOKIE["username"]))
{
 header("location:login.php");
}

?>

<script>
function readCookie(name) {
    var nameEQ = name + "=";
    var ca = document.cookie.split(';');
    for(var i=0;i < ca.length;i++) {
        var c = ca[i];
        while (c.charAt(0)==' ') c = c.substring(1,c.length);
        if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length,c.length);
    }
    return null;
}

function removeFromCart(id) {
  jQuery.ajax({
    type: "POST",
    url: 'controllerHelper.php',
    dataType: 'json',
    data: {functionname: 'removeFromShoppingCart', arguments: [id]},
    success: function (obj, textstatus) {
                  if( !('error' in obj) ) {
                      yourVariable = obj.result;
                  }
                  else {
                      console.log(obj.error);
                  }
            }
  });
  setTimeout(() => console.log("First"), 40000);
  $("#box").load("shopping_cart.php", function(){});
}
</script>

<!DOCTYPE html>
<html>
 <head>
  <title>Shopping Cart</title>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" />
  <link rel="icon" href="images/icon.ico">
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
  <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.2/jquery.min.js"></script>
 </head>
 <body>
 <div id="box">
  <br />
  <div class="container">
   <br />
   <div align="right">
    <a href="index.php">Products</a>
    <a href="shopping_cart.php">My Shopping Cart</a>
    <a href="account.php">My Account</a>
    <a href="logout.php">Logout</a>
    <img src="images/standard.png" width="40" height="40">
    <?php echo $_COOKIE["name"]; ?>
   </div>
   <br />
   <h2 align="center">Shopping Cart</h2>
   <br>
   <?php
    $cart = $controller->getShoppingCart();
    if (count($cart) == 0)
    {
    	echo "<center><h4>There are no items in your shopping cart !</h4></center>";
    }
   ?>
   <?php
   if (count($cart) != 0)
   {?>
   <h4>
   <style type="text/css">
    td {
    padding: 10px 10px 10px 10px;
    align: center;
   }
   </style>
   <table align="center" border="1">
    <thead>
     <tr>
      <td><b><center>Name</center></b></td>
      <td><b><center>Image</center></b></td>
      <td><b><center>Price</center></b></td>
      <td><b><center>Category</center></b></td>
      <td><b><center>Amount</center></b></td>
      <td><b><center>Total Price</center></b></td>
      <td><b><center></center></b></td>
     </tr>
    </thead>
    <tbody>
    <?php $sum = 0; ?>
    <?php foreach ($cart as $shoppingCartElement) { ?>
     <tr>
      <td><center><?php echo $shoppingCartElement->getName(); ?></center></td>
      <td><center><img src='./images/<?php echo $shoppingCartElement->getImage(); ?>'></center></td>
      <td><center><?php echo $shoppingCartElement->getPrice(); ?></center></td>
      <td><center><?php echo $shoppingCartElement->getCategory(); ?></center></td>
      <td><center><?php echo $shoppingCartElement->getAmount(); ?></center></td>
      <td><center><?php echo $shoppingCartElement->getTotalPrice(); $sum = $sum + $shoppingCartElement->getTotalPrice(); ?>
      <td><center><button type="button" onclick="removeFromCart(<?php echo $shoppingCartElement->getId(); ?>)">Remove one item from cart</button></center></td>
     </tr>
     <?php } ?>
    </tbody>
   </table>
   </h4>
   <br>
   <center><h2>Total Sum : <?php echo $sum; ?></h2></center>
   <br>
   <center><h2><button type="button">Buy items</button></h2></center>
   <?php } ?>
   <?php $conn = null; ?>
  </div>
 </div>
 </body>
</html>