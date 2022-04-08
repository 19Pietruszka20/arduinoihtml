<html>
<body>

<?php

$dbname = 'itnew';
$dbuser = 'root';  
$dbpass = ''; 
$dbhost = 'localhost:3307'; 

$connect = @mysqli_connect($dbhost,$dbuser,$dbpass,$dbname);

if(!$connect){
	echo "Error: " . mysqli_connect_error();
	exit();
}

echo "Connection Success!<br><br>";

$v2 = $_GET["v2"];
$przebytadroga = $_GET["przebytadroga"]; 


/*$sql = "INSERT INTO it_proj (v2, przebytadroga) VALUES ('$v2', '$przebytadroga')";*/

$sql = "INSERT INTO rower (v2, przebytadroga) VALUES (7.57, 8)";
$result = mysqli_query($connect,$sql);

echo "Insertion Success!<br>";

?>
</body>
</html>