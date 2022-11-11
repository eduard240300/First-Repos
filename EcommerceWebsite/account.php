<?php
//account.php

if(!isset($_COOKIE["username"]))
{
 header("location:login.php");
}

?>
<!DOCTYPE html>
<html>
 <head>
  <title>Account of <?php echo $_COOKIE["name"] ?></title>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" />
  <link rel="icon" href="images/icon.ico">
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
 </head>
 <body>
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
   <?php echo '<h2 align="center">Account of ' . $_COOKIE["name"] . '</h2>'; ?>
   <h2> </h2>
   <h2></h2>
   <h4>
   <style type="text/css">
    td {
     padding: 10px 10px 10px 10px;
     align: center;
    }
   </style>
   <table align="center">
    <tr>
      <td><h4>Name : <?php echo $_COOKIE["name"]; ?></h4></td>
    </tr>
    <tr>
      <td><h4>Address : <?php echo $_COOKIE["address"]; ?></h4></td>
    </tr>
    <tr>
      <td><h4>Zip Code : <?php echo $_COOKIE["zipcode"]; ?></h4></td>
    </tr>
    <tr>
      <td><h4>Phone Number : <?php echo $_COOKIE["phonenumber"]; ?></h4></td>
    </tr>
    <tr>
      <td><h4>Email : <?php echo $_COOKIE["email"]; ?></h4></td>
    </tr>
    <tr>
     <td><center><input type="button" onclick="location.href='logout.php';" value="Logout" /></center></td>
    </tr>
   </table>
   </h4>
   <?php $conn = null; ?>
  </div>
 </body>
</html>
