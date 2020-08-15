<?php

header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

$conn = new mysqli("localhost","bustracker","","my_bustracker");

$result = $conn->query("SELECT Fermate.Nome FROM Fermate");


$posts = array();
	if(mysqli_num_rows($result)){
		while($post = mysqli_fetch_assoc($result)) {
			$posts[] = array('fer'=>$post);
		}
	}
	
$conn->close();

echo json_encode(array('fe'=> $posts));
 ?>