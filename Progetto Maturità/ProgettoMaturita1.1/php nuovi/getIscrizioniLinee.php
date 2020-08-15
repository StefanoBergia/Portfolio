<?php header("Access-Control-Allow-Origin:*");  
    if(isset($_POST["IDOrario"])){
        $Registration=$_GET["RegistrationID"];
        $fermate= array();
        $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
        if(!mysqli_errno($cnn)){          
            $fermateRes=mysqli_query($cnn,"SELECT IDFermata, IDOrario, Tempo FROM Notifiche");
            if(mysqli_num_rows($fermateRes))
            {
                while($fermata=mysqli_fetch_assoc($fermateRes)){
                    $fermate[]=$fermata; 
                }
                echo json_encode( array("fermate"=>$fermate));
            }else
            echo "KO";  
        }       
        mysqli_close($cnn);
    };
?>
