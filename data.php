<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "database";

// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);

// Check connection
if (!$conn) {
  die("Connection failed: " . mysqli_connect_error());
}

if (isset($_GET["v"])){
  $limit = $_GET["v"];
  $sql = "SELECT * FROM (SELECT * FROM sensor ORDER BY createddate DESC LIMIT ".$limit.") AS sub ORDER BY createddate ASC";
}else{
  $sql = "SELECT * FROM sensor ORDER BY createddate DESC LIMIT 1";
}

$result = $conn->query($sql);

$finalArr = array();
$i=0;

if ($result->num_rows > 0) {
  // output data of each row
  while($row = $result->fetch_assoc()) {
    $messageDecode = json_decode($row["message"]);
    $finalArr[$i] = array();
    if (isset($messageDecode->weight) && isset($messageDecode->bmi)){
      $finalArr[$i]["id"] = $row["id"];
      $finalArr[$i]["topic"] = $row["topic"];
      $finalArr[$i]["weight"] = $messageDecode->weight; //rand(10,100); // 
      $finalArr[$i]["bmi"] = $messageDecode->bmi; //add bmi
      $finalArr[$i]["scale0"] = $messageDecode->Scale0; 
      $finalArr[$i]["scale1"] = $messageDecode->Scale1; 
      $finalArr[$i]["scale2"] = $messageDecode->Scale2; 
      $finalArr[$i]["scale3"] = $messageDecode->Scale3; 
      $finalArr[$i]["datetime"] = $row["createddate"];
      $finalArr[$i]["email"] = $row["email"];

      $i++;
    }
  }

} else {
  echo "empty";
}

echo json_encode($finalArr);
$conn->close();

?>