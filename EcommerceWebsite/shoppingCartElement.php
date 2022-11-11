<?php

class ShoppingCartElement implements JsonSerializable {
	private $id;
	private $name;
	private $image;
	private $price;
	private $category;
	private $amount;	

	public function __construct($id, $name, $image, $price, $category, $amount) {
		$this->id = $id;
		$this->name = $name;
		$this->image = $image;
		$this->price = $price;
		$this->category = $category;
		$this->amount = $amount;
	}

	public function getId() {
		return $this->id;
	}
	public function getName() {
		return $this->name;
	}
	public function getImage() {
		return $this->image;
	}
	public function getPrice() {
		return $this->price;
	}
	public function getCategory() {
		return $this->category;
	}
	public function getAmount() {
		return $this->amount;
	}
	public function increaseAmount() {
		$this->amount = $this->amount + 1;
	}
	public function decreaseAmount() {
		$this->amount = $this->amount - 1;
	}
	public function getTotalPrice() {
		return $this->amount * $this->price;
	}


	public function jsonSerialize() {
        $vars = get_object_vars($this);
        return $vars;
    }
}

?>
