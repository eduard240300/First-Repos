<?php
//index.php

if(!isset($_COOKIE["username"]))
{
 header("location:login.php");
}

include_once("controller.php");
$controller = new Controller();

if (!(($_COOKIE["category"] == "Electronics") || ($_COOKIE["category"] == "Books") || ($_COOKIE["category"] == "Clothes")))
{
  setcookie("category", "Electronics", time()+3600);
}

if (!(($_COOKIE["page"] == "0") || ($_COOKIE["page"] == "1")))
{
  setcookie("page", "0", time()+3600);
}

?>

<script>
function changeCategoryJavascript () {
  <?php setcookie("page", "0", time()+3600); ?>
  var select1 = document.getElementById("categories");
  var selected = select1.value;
  var d = new Date();
  d.setTime(d.getTime() + (60*60*1000));
  var expires = "expires="+ d.toUTCString();
  document.cookie = "category = " + selected + ";" + expires;
  $("#box").load("index.php", function(){});
}

function nextPage () {
  var currentPage = <?php echo $_COOKIE["page"]; ?>;
  if (currentPage <= 0)
  	currentPage = currentPage + 1;
  var d = new Date();
  d.setTime(d.getTime() + (60*60*1000));
  var expires = "expires="+ d.toUTCString();
  document.cookie = "page = " + currentPage + ";" + expires;
  $("#box").load("index.php", function(){});
}

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

function previousPage () {
  var currentPage = <?php echo $_COOKIE["page"]; ?>;
  if (currentPage >= 1)
  	currentPage = currentPage - 1;
  var d = new Date();
  d.setTime(d.getTime() + (60*60*1000));
  var expires = "expires="+ d.toUTCString();
  document.cookie = "page = " + currentPage + ";" + expires;
  $("#box").load("index.php", function(){});
}

function addToCart(id) {
  jQuery.ajax({
    type: "POST",
    url: 'controllerHelper.php',
    dataType: 'json',
    data: {functionname: 'addToShoppingCart', arguments: [id]},

    success: function (obj, textstatus) {
                  if( !('error' in obj) ) {
                      yourVariable = obj.result;
                  }
                  else {
                      console.log(obj.error);
                  }
            }
  });
}
</script>

<!DOCTYPE html>
<html>
 <head>
  <title>Products</title>
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
    <?php
     echo $_COOKIE["name"];
    ?>
   </div>
   <br />
   <h2 align="center">Products</h2>
   <br>
   <center><h4>Select Category : <select id="categories">  
     <option value="Electronics">Electronics</option>  
     <option value="Clothes">Clothes</option>  
     <option value="Books">Books</option>  
   </select> <button type="button" onclick="changeCategoryJavascript()">Search</button> </h4></center>
   <br>
   <center><h4>Page : <?php echo $_COOKIE["page"] + 1; ?></h4></center>
   <?php
    $products = $controller->getProducts($_COOKIE["category"], $_COOKIE["page"]);
   ?>
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
      <td><b><center></center></b></td>
     </tr>
    </thead>
    <tbody>
    <?php foreach ($products as $product){ ?>
     <tr>
      <td><center><?php echo $product->getName(); ?></center></td>
      <td><center><img src='./images/<?php echo $product->getImage(); ?>'></center></td>
      <td><center><?php echo $product->getPrice(); ?></center></td>
      <td><center><?php echo $product->getCategory(); ?></center></td>
      <td><center><button type="button" onclick="addToCart(<?php echo $product->getId(); ?>)">Add one item to cart</button></center></td>
     </tr>
     <?php } ?>
    </tbody>
   </table>
   </h4>
   <h2></h2>
   <h4>
   <table align="center">
    <tr>
     <td><button type="button" onclick="previousPage()">Previous Page</button></td>
     <td><button type="button" onclick="nextPage()">Next Page</button></td>
    </tr>
   </table>
   </h4>
   <?php $conn = null; ?>
  </div>
 </div>
 </body>
</html>

<script>
var select1 = document.getElementById("categories");
if ("<?php echo $_COOKIE["category"]; ?>" === "Electronics") {
	select1.selectedIndex = 0;
}
if ("<?php echo $_COOKIE["category"]; ?>" === "Clothes") {
	select1.selectedIndex = 1;
}
if ("<?php echo $_COOKIE["category"]; ?>" === "Books") {
	select1.selectedIndex = 2;
}
</script>
