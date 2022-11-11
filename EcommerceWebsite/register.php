<?php
//register.php

require_once("controller.php");
$controller = new Controller();

if(isset($_COOKIE["username"]))
{
 header("location:index.php");
}

$message = '';

if(isset($_POST["register"]))
{
 if(empty($_POST["name"]) || empty($_POST["username"]) || empty($_POST["password"]) || empty($_POST["password_repeat"]) || empty($_POST["address"]) || empty($_POST["zipcode"]) || empty($_POST["phonenumber"]) || empty($_POST["email"]))
 {
  $message = "<div class='alert alert-danger'>All Fields are required</div>";
 }
 else
 {
  $existsUsername = $controller->existsUsername($_POST["username"]);
  if($existsUsername == True)
  {
   $message = "<div class='alert alert-danger'>Username already exists !</div>";
  }
  else
  {
   if ($_POST["password"] == $_POST["password_repeat"])
   {
    $executed = $controller->addUser($_POST["username"], $_POST["password"], $_POST["name"], $_POST["address"], $_POST["zipcode"], $_POST["phonenumber"], $_POST["address"]);
    if($executed){
     $message = "<div class='alert alert-success'>Account created successfully !</div>";
    } else{
     $message = "<div class='alert alert-danger'>Account not created successfully !</div>";
    }
   }
   else {
    $message = "<div class='alert alert-danger'>Password fields should match</div>";
   }
  }
 }
}
?>

<!DOCTYPE html>
<html>
 <head>
  <title>Register Page</title>
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.0/jquery.min.js"></script>
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css" />
  <link rel="icon" href="images/icon.ico">
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
 </head>
 <body>
  <br />
  <div class="container">
   <h2 align="center">Register</h2>
   <br />
   <div class="panel panel-default">
   <div class="panel-heading">Register</div>
    <div class="panel-body">
     <span><?php echo $message; ?></span>
   <form method="post">
   <div class="form-group">
    <label>Full Name</label>
    <input type="text" name="name" id="name" class="form-control" />
   </div>
   <div class="form-group">
    <label>Username</label>
    <input type="text" name="username" id="username" class="form-control" />
   </div>
    <div class="form-group">
     <label>Password</label>
     <input type="password" name="password" id="password" class="form-control" />
   </div>
   <div class="form-group">
    <label>Repeat password</label>
    <input type="password" name="password_repeat" id="password_repeat" class="form-control" />
   </div>
   <div class="form-group">
     <label>Address</label>
     <input type="text" name="address" id="address" class="form-control" />
   </div>
   <div class="form-group">
     <label>Zip Code</label>
     <input type="text" name="zipcode" id="zipcode" class="form-control" />
   </div>
   <div class="form-group">
     <label>Phone Number</label>
     <input type="text" name="phonenumber" id="phonenumber" class="form-control" />
   </div>
   <div class="form-group">
     <label>Email</label>
     <input type="text" name="email" id="email" class="form-control" />
   </div>
   <div class="form-group">
    <input type="submit" name="register" id="register" class="btn btn-info" value="Register" />
   </div>
   <div class="from-group">
    <a href="login.php">Login</a>
   </div>
   </form>
  </div>
  </div>
  <br />
  </div>
 </body>
</html>
