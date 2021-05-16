<?php
include 'config.php';
 
// Escape user inputs for security
    $manufacturer = mysqli_real_escape_string($link, $_REQUEST['manufacturer']);
    $Model = mysqli_real_escape_string($link, $_REQUEST['Model']);
    $licenceplate = mysqli_real_escape_string($link, $_REQUEST['licenceplate']);
    $insurance = 1;

            
            // Attempt insert query execution
    $sql = "INSERT INTO car (manufacturer, Model, licenceplate, insurance) VALUES ('$manufacturer', '$Model', '$licenceplate', '$insurance')";
        if(mysqli_query($link, $sql)){
            echo "Records added successfully.";
        } else{
            echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
        }

    header("location: index.php");
?>