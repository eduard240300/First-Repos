<?php
//login.php

include_once("controller.php");

$controller = new Controller();

if(isset($_COOKIE["username"]))
{
 header("location:index.php");
}
else
{
 $jsonData = json_encode(array());
 file_put_contents('shopping_cart.json', $jsonData); 
}

$message = '';

if(isset($_POST["login"]))
{
 if(empty($_POST["username"]) || empty($_POST["password"]))
 {
  $message = "<div class='alert alert-danger'>Both fields are required</div>";
 }
 else
 {
  $existsUsername = $controller->existsUsername($_POST["username"]);
  if($existsUsername == True)
  {
   $user = $controller->getUser($_POST["username"]);
   if(password_verify($_POST["password"] , $user["Password"]))
   {
    setcookie("username", $user["Username"], time()+3600);
    setcookie("name", $user["Name"], time()+3600);
    setcookie("address", $user["Address"], time()+3600);
    setcookie("zipcode", $user["ZipCode"], time()+3600);
    setcookie("phonenumber", $user["PhoneNumber"], time()+3600);
    setcookie("email", $user["Email"], time()+3600);
    setcookie("page", "0", time()+3600);
    setcookie("category", "Electronics", time()+3600);
	setcookie("id", "0", time()+3600);
    header("location:index.php");
   }
   else
   {
    $message = '<div class="alert alert-danger">Wrong Password</div>';
   }
  }
  else
  {
   $message = "<div class='alert alert-danger'>Wrong Username</div>";
  }
 }
}
?>

<!DOCTYPE html>
<html>
 <head>
  <title>Login Page</title>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" />
  <link rel="icon" href="images/icon.ico">
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
 </head>
 <body>
 <br />
 <div class="container">
  <h2 align="center">Login</h2>
  <br />
  <div class="panel panel-default">
   <div class="panel-heading">Login</div>
   <div class="panel-body">
    <span><?php echo $message; ?></span>
    <form method="post">
     <div class="form-group">
      <label>Username</label>
      <input type="text" name="username" id="username" class="form-control" />
     </div>
     <div class="form-group">
      <label>Password</label>
      <input type="password" name="password" id="password" class="form-control" />
     </div>
     <div class="form-group">
      <input type="submit" name="login" id="login" class="btn btn-info" value="Login" />
     </div>
     <div class="form-group">
      <a href="register.php">Register</a>
     </div>
    </form>
   </div>
  </div>
  <br />
 </div>
 </body>
</html>
