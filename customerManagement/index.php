<?php
// Initialize the session
session_start();
 
// Check if the user is logged in, if not then redirect him to login page
if(!isset($_SESSION["loggedin"]) || $_SESSION["loggedin"] !== true){
    header("location: login.php");
    exit;
}

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Welcome</title>
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css">
    <link rel="stylesheet" href="styleVlad.css">
    <style>
        body{ font: 14px sans-serif; text-align: center; }
    </style>
</head>
<body>
    <h1 class="my-5">Hi, <b><?php echo htmlspecialchars($_SESSION["username"]); ?></b>. Welcome to our site.</h1>
    <div class="hero-div">
        <img class="hero-img" src="img.jpg">
    </div>
    <h2>Your cars fleet can be found below</h2>
    <table class="car-table" border="2">
    <tr class="table-data table-header">
        <!--<td class="table-info">ID</td>-->
        <td class="table-info">Manufacturer</td>
        <td class="table-info">Model</td>
        <td class="table-info">Licence plate</td>
        <td class="table-info">Has insurance?</td>
    </tr>

    <?php

    include "config.php"; 

    $car_records = mysqli_query($link,"select * from car"); 

    while($data = mysqli_fetch_array($car_records))
    {
    ?>
    <tr class="table-data">
        <td class="table-info"><?php echo $data['manufacturer']; ?></td>
        <td class="table-info"><?php echo $data['Model']; ?></td>
        <td class="table-info"><?php echo $data['licenceplate']; ?></td>
        <td class="table-info"><?php echo $data['insurance']; ?></td>
    </tr>	
    <?php
    }
    ?>
    </table>

    <?php mysqli_close($link); // Close connection ?>

    <div class="buttons-section">
        <a id="myBtn" class="button add-btn">Add a new car</a>
        <a href="logout.php" class="button logout-btn">Sign Out</a>
    </div>


    <!-- The Modal -->
    <div id="myModal" class="modal">

    <!-- Modal content -->
    <div class="modal-content">
        <span class="close">&times;</span>
        <div class="form-info">
            <form action="insert.php" method="post">
                <p>
                    <label for="manufacturer">Manufacturer:</label>
                    <input type="text" name="manufacturer" id="manufacturer">
                </p>
                <p>
                    <label for="Model">Model:</label>
                    <input type="text" name="Model" id="Model">
                </p>
                <p>
                    <label for="licenceplate">Licence Plate:</label>
                    <input type="text" name="licenceplate" id="licenceplate">
                </p>
                <input class="button add-btn" type="submit" value="Submit">
            </form>
        </div>
    </div>

    </div>

    

    

</body>
<script src="scriptVlad.js"></script>
</html>