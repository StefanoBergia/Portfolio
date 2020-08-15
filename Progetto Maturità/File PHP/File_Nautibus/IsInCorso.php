<?php header("Access-Control-Allow-Origin:*");  
    if(isset($_POST["IDOrario"])){
        $idOrario=$_POST["IDOrario"];
        $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
        if(!mysqli_errno($cnn)){     
		$res=mysqli_query($cnn,"SELECT IDOrario FROM Tratte WHERE IDOrario=$idOrario AND InCorso=1");
            if(mysqli_num_rows($res)==1)
            {   
                echo "OK";
                
            }else
                echo "KO";
              
        }  
        else
        	echo "KO";
        mysqli_close($cnn);
    }else
    	echo "KO";
?>
