<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "hladina";

$api_key_value = "tPmAT5Ab3j7F9";
$api_key = $value1 = $value2 = $value3 = $value4 = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $value1 = test_input($_POST["value1"]);
        $value2 = test_input($_POST["value2"]);
        $value3 = test_input($_POST["value3"]);
        $value4 = test_input($_POST["value4"]);
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        }
        $sql = "INSERT INTO SensorData (value1, value2, value3, value4)
        VALUES ('" . $value1 . "', '" . $value2 . "', '" . $value3 . "',  '" . $value4 . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }
}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data); // hello world -> trim(he) = llo world;
    $data = stripslashes($data); // hello\\world -> stripslashes() = helloworld
    $data = htmlspecialchars($data); // &value1 -> &ampvalue1
    return $data;
}