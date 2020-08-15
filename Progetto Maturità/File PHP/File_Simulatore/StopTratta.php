<?php header("Access-Control-Allow-Origin:*");    
    if(isset($_POST["IDTratta"])){
                             
        $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
        if(!mysqli_errno($cnn)){
          if(mysqli_query($cnn,"UPDATE Tratte SET InCorso=0 WHERE IDTratta=".$_POST["IDTratta"]));
             echo "OK";
        }else
            echo "KO";
    }else
      echo "KO";
?>
