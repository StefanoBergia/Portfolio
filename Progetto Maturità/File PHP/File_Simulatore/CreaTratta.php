<?php header("Access-Control-Allow-Origin:*");    
    if(isset($_POST["IDAutobus"]) &&
       isset($_POST["IDAutista"]) &&
       isset($_POST["IDOrario"]) &&
       isset($_POST["Ritardo"])){
                             
        $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
        if(!mysqli_errno($cnn)){
           $res=mysqli_query($cnn,"INSERT INTO `my_bustracker`.`Tratte` ( `Data`, `InCorso`, `IDAutobus`, `IDAutista`, `IDOrario`, `Ritardo`) VALUES
                             ('".date("Y-m-d")."', 1, '".$_POST["IDAutobus"]."', '".$_POST["IDAutista"]."', '".$_POST["IDOrario"]."', '".$_POST["Ritardo"]."')");
            echo mysqli_insert_id($cnn);
           
        }else
            echo "-1";
    }else
      echo "-1";
?>