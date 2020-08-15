<?php header("Access-Control-Allow-Origin:*");  
    if(isset($_POST["IDOrario"])){
        $idOrario=$_POST["IDOrario"];
        $fermate= array();
        $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
        if(!mysqli_errno($cnn)){          
            $fermateRes=mysqli_query($cnn,"SELECT Fermate.IDFermata AS ID,Fermate.Lat AS Lat,Fermate.Lon AS Lon,Localita.Nome AS NomeLocalita,Fermate.Nome AS NomeFermata, ADDTIME(Orari.OraPartenza,SEC_TO_TIME(Percorsi.Offset/1000))AS Ora FROM Fermate,Localita,Percorsi,Linee,Orari WHERE Fermate.IDFermata=Percorsi.IDFermata AND Fermate.IDLocalita=Localita.IDLocalita AND Percorsi.IDLinea=Linee.IDLinea AND Linee.IDLinea=Orari.IDLinea AND Orari.IDOrario=".$idOrario);
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
