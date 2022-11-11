<?php

require_once 'DBUtils.php';
require_once 'shoppingCartList.php';
require_once 'product.php';
require_once 'shoppingCartElement.php';

class Model {
	private $db;
	private $shoppingCartList;

	public function __construct() {
		$this->db = new DBUtils ();
		$this->shoppingCartList = new ShoppingCartList ();
	}

	public function existsUsername($username) {
		return $this->db->existsUsername($username);
	}

	public function getUser($username)
	{
		return $this->db->getUser($username);
	}

	public function addUser($username, $password, $name, $address, $zipcode, $phonenumber, $email)
	{
		return $this->db->addUser($username, $password, $name, $address, $zipcode, $phonenumber, $email);
	}

	public function getShoppingCart() {
		return $this->shoppingCartList->getList();
	}

	public function addToShoppingCart($id) {
		if ($this->shoppingCartList->isElement($id) != -1)
		{
			$this->shoppingCartList->increaseAmountElement($id);
		}
		else
		{
			$product = $this->getProduct($id);
			$shoppingCartElement = new ShoppingCartElement($product->getId(), $product->getName(), $product->getImage(), $product->getPrice(), $product->getCategory(), 1);
			$this->shoppingCartList->addElement($shoppingCartElement);
		}
	}

	public function removeFromShoppingCart($id) {
		if ($this->shoppingCartList->isElement($id) == -1)
		{
			return False;
		}
		else
		{
			$this->shoppingCartList->decreaseAmountElement($id);
		}
	}

	public function getProduct($id) {
		$product = $this->db->selectProduct($id);
		$newProduct = new Product ($product['ProductID'], $product['ProductName'], $product['ProductImage'], $product['Price'], $product['Category']);
	    return $newProduct;
	}

	public function getProducts($category, $page) {
		$min_max_array = $this->db->getProductsIDRangeForPage($category, $page);
		$min = $min_max_array[0];
		$max = $min_max_array[1];
		$resultset = $this->db->selectProducts($category, $min, $max);
		$products = array();
		foreach($resultset as $key=>$val) {
			$product = $val;
			$newProduct = new Product ($product['ProductID'], $product['ProductName'], $product['ProductImage'], $product['Price'], $product['Category']);
	    	array_push($products, $newProduct);
		}

	    return $products;
	}

}

?>
