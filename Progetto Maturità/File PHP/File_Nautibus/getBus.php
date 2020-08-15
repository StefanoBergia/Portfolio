<?php header("Access-Control-Allow-Origin:*");  
    if(isset($_POST["IDOrario"])){
        $idOrario=$_POST["IDOrario"];
        $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
        if(!mysqli_errno($cnn)){     
		$res=mysqli_query($cnn,"SELECT Tappe.Lat AS Latitude, Tappe.Lon AS Longitude FROM Tratte,Tappe WHERE Tappe.IDTratta=Tratte.IDTratta AND Tratte.InCorso=1 AND Tratte.IDOrario={$_POST['IDOrario']} ORDER BY Tappe.Offset DESC LIMIT 1");
            if(mysqli_num_rows($res))
            {   
                $dati=mysqli_fetch_assoc($res);
                echo "".json_encode($dati);
                
            }else
                echo "KO";
              
        }       
        mysqli_close($cnn);
    }; 
?>
