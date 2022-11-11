<?php

class Product implements JsonSerializable {
	private $id;
	private $name;
	private $image;
	private $price;
	private $category;

	public function __construct($id, $name, $image, $price, $category) {
		$this->id = $id;
		$this->name = $name;
		$this->image = $image;
		$this->price = $price;
		$this->category = $category;
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
	public function jsonSerialize() {
        $vars = get_object_vars($this);
        return $vars;
    }
}

?>
