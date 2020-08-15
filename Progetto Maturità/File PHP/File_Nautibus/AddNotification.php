<?php header("Access-Control-Allow-Origin:*"); 
	
    if(isset($_POST["RegID"])&&
    isset($_POST["IDOrario"]) &&
    isset($_POST["IDFermata"]) &&
    isset($_POST["Tempo"]))
    {              
        if(!mysqli_errno($cnn)){
           
          $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
          if(mysqli_query($cnn,"INSERT INTO Notifiche (REGISTRATION_ID,IDOrario,IDFermata,Tempo) VALUES ('{$_POST["RegID"]}',{$_POST["IDOrario"]},{$_POST["IDFermata"]},{$_POST["Tempo"]})"))
            {
                echo "OK";
            }
            else
                echo "KO";
          
        }else
        	echo "KO";
     } else
     	echo "KO";
?>