<?php

require_once 'shoppingCartElement.php';

class ShoppingCartList {
    private $list;

    public function __construct() {
        $inp = file_get_contents('shopping_cart.json');
        $tempArray = json_decode($inp);
        $this->list = array();
        foreach($tempArray as $element){
            $newElement = new ShoppingCartElement($element->{'id'}, $element->{'name'}, $element->{'image'}, $element->{'price'}, $element->{'category'}, $element->{'amount'});
            array_push($this->list, $newElement);
        }
	}
    public function addElement($shoppingCartElement)
    {
        array_push($this->list, $shoppingCartElement);
        $jsonData = json_encode($this->list);
        file_put_contents('shopping_cart.json', $jsonData); 
    }
    public function isElement($id)
    {
        $item = null;
        $index = 0;
        foreach($this->list as $element) {
            if ($id == $element->getId()) {
                $item = $element;
                break;
            }
            $index++;
        }
        if ($item == null)
        {
            $index = -1;
        }
        return $index;
    }
    public function increaseAmountElement($id)
    {
        $item = null;
        foreach($this->list as $element) {
            if ($id == $element->getId()) {
                $item = $element;
                break;
            }
        }
        $item->increaseAmount();
        $jsonData = json_encode($this->list);
        file_put_contents('shopping_cart.json', $jsonData); 
    }
    public function decreaseAmountElement($id)
    {
        $item = null;
        $index = 0;
        foreach($this->list as $element) {
            if ($id == $element->getId()) {
                $item = $element;
                break;
            }
            $index++;
        }
        $item->decreaseAmount();
        if ($item->getAmount() == 0)
        {
            array_splice($this->list, $index, 1);
        }
        $jsonData = json_encode($this->list);
        file_put_contents('shopping_cart.json', $jsonData); 
    }
    public function getList()
    {
        return $this->list;
    }
}

?>