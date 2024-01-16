<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "database";

$from = "patientmonitor219@gmail.com";
$to = "minhnhat6501@gmail.com";
$subject = "Alarm: Patient is not in bed";
$message = "Patient is not in bed now.";
$headers = [ "From: $from" ];

try{
    if (isset($_GET["id"])){
        // Create connection
        $conn = mysqli_connect($servername, $username, $password, $dbname);

        // Check connection
        if (!$conn) {
            die("Connection failed: " . mysqli_connect_error());
        }

        mail( $to, $subject, $message, implode( '\r\n', $headers ) );
        $sql = "UPDATE sensor SET email=1 WHERE id=".$_GET["id"];
        $conn->query($sql);
    }

}catch (Exception $e) {
}