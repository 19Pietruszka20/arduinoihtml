<html>
<body>

<?php

$dbname = 'itnew';
$dbuser = 'root';  
$dbpass = ''; 
$dbhost = 'localhost'; 

$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Error: " . mysqli_connect_error();
	exit();
}

echo "Connection Success!<br><br>";

$przebytadroga = $_GET["przebytadroga"];
$czas = $_GET["czas"]; 


/*$sql = "INSERT INTO rower (v2, przebytadroga) VALUES ('$v2', '$przebytadroga')";*/

$sql = "INSERT INTO rower1 (przebytadroga, czas) VALUES (0.06, 8)";
$result = mysqli_query($connect,$sql);

echo "Insertion Success!<br>";

?>
</body>
</html>