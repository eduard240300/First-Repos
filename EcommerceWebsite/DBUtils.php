<?php

class DBUtils {
	private $host = '127.0.0.1';
	private $db   = 'ecommerceDB';
	private $user = 'root';
	private $pass = '';
	private $charset = 'utf8';	

	private $pdo;
	private $error;

	public function __construct () {
		$dsn = "mysql:host=$this->host;dbname=$this->db;charset=$this->charset";
		$opt = array(PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
			PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
			PDO::ATTR_EMULATE_PREPARES   => false);
		try {
			$this->pdo = new PDO($dsn, $this->user, $this->pass, $opt);		
		} // Catch any errors
		catch(PDOException $e){
			$this->error = $e->getMessage();
			echo "Error connecting to DB: " . $this->error;
		}
	}

	public function existsUsername($username) {
		$query="SELECT * FROM Users
		WHERE Username = :username";
		$statement = $this->pdo->prepare($query);
		$statement->execute(
		 array(
		  'username' => $username
		 )
		);
		$count = $statement->rowCount();
		if ($count == 0)
		{
			return False;
		}
		else
		{
			return True;
		}
	}

	public function getUser($username) {
		$query="SELECT * FROM Users
		WHERE Username = :username";
		$statement = $this->pdo->prepare($query);
		$statement->execute(
		 array(
		  'username' => $username
		 )
		);
		return $statement->fetchAll()[0];
	}

	public function addUser($username, $password, $name, $address, $zipcode, $phonenumber, $email)
	{
		$STH = $this->pdo->prepare('INSERT INTO `Users` (`Username`, `Password`, `Name`, `Address`, `ZipCode`, `PhoneNumber`, `Email`) VALUES("' .  $username . '", "' . password_hash($password, PASSWORD_DEFAULT) . '", "' . $name . '", "' . $address . '", "' . $zipcode . '", "' . $phonenumber . '", "' . $email . '");');
		if ($STH->execute())
		{
			return True;
		}
		else
		{
  			return False;
		}
	}

	public function getProductsIDRangeForPage($category, $page) {
		$ids=$this->pdo->query("SELECT `ProductID` FROM `Products` WHERE `Category`='" . $category . "'");
    	$minProductID = 100;
    	foreach ($ids as $row): array_map('htmlentities', $row);
    	if ($minProductID > $row["ProductID"])
    	  $minProductID = $row["ProductID"];
    	endforeach;
    	$minProductID = $minProductID + $page * 4;
    	$maxProductID = $minProductID + 3;
		return [$minProductID, $maxProductID];
	}	

	public function selectProducts($category, $min, $max) {
        $stmt=$this->pdo->query("SELECT `ProductID`, `ProductName`, `ProductImage`, `Price`, `Category` FROM `Products` WHERE `Category`='" . $category . "' AND `ProductID` >= " . $min . " AND `ProductID` <= " . $max . " ORDER BY `ProductID` ASC");
        return $stmt->fetchAll(PDO::FETCH_ASSOC);
    }

	public function selectProduct($id) {
        $stmt=$this->pdo->query("SELECT * FROM `Products` WHERE `ProductID` = " . $id);
        return $stmt->fetchAll(PDO::FETCH_ASSOC)[0];
    }
}
 

?>

