<?php

require_once 'model.php';
require_once 'view.php';

class Controller
{
    private $view;
    private $model;	

    public function __construct(){
    	$this->model = new Model ();
        $this->view = new View();
    }

    /*public function service() {
	   if (isset($_GET['action']) && !empty($_GET['action'])) {
            if ($_GET['action'] == "getUser") {
   	            $this->{$_GET['action']}($_GET['user']);
            } else {
                $this->{$_GET['action']}();
            } 
	   }
    }*/

    public function existsUsername($username) {
		return $this->model->existsUsername($username);
	}

	public function getUser($username)
	{
		return $this->model->getUser($username);
	}

	public function addUser($username, $password, $name, $address, $zipcode, $phonenumber, $email)
	{
		return $this->model->addUser($username, $password, $name, $address, $zipcode, $phonenumber, $email);
	}

    public function addToShoppingCart($id)
    {
        $this->model->addToShoppingCart($id);
    }

    public function removeFromShoppingCart($id)
    {
        $this->model->removeFromShoppingCart($id);
    }

    public function getShoppingCart() {
       $shoppingCart = $this->model->getShoppingCart();
       return $shoppingCart;
    }

    public function getProducts($category, $page) {
       $products = $this->model->getProducts($category, $page);
       return $products;
    }
}

?>
