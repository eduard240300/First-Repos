<?php
$link = mysqli_connect("localhost", "root", "GameofThronesPhoenix24", "Repository");
$query2 = "
CREATE TABLE IF NOT EXISTS `user_details` (
  `user_id` int(11) NOT NULL,
  `user_username` varchar(200) NOT NULL,
  `user_password` varchar(200) NOT NULL,
  `user_name` varchar(200) NOT NULL,
  `user_security_hint` varchar(200) NOT NULL,
  `user_security_phrase` varchar(200) NOT NULL
);";
echo $query2;
// Attempt insert query execution
if(mysqli_query($link, $query2)){
 echo "Added successfully !";
} else{
 echo "Added no successfully !";
}
?>
