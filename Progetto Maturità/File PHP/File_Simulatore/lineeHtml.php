<?php header("Access-Control-Allow-Origin:*");
    $cnn=mysqli_connect("127.0.0.1","bustracker","","my_bustracker");
    $count=0;
    if(mysqli_connect_errno($cnn)){
		echo (mysqli_connect_error());
	}else{
		$autisti=array();
        $autobus=array(); 
        $linee=array();  
        
        /*selezione autobus*/
		$autobusQuery=mysqli_query($cnn,"SELECT Targa FROM Autobus");
		if(mysqli_num_rows($autobusQuery))
		{
			while($supp=mysqli_fetch_assoc($autobusQuery))
                $autobus[]="<option value='".$supp["Targa"]."'>".$supp["Targa"]."</option>";	
		}
        
        /*Selezione autisti*/    
        $autistiQuery=mysqli_query($cnn,"SELECT IDAutista,Nome,Cognome FROM Autisti");
        if(mysqli_num_rows($autistiQuery))
        {
            while($supp=mysqli_fetch_assoc($autistiQuery))
                $autisti[]= "<option value='".$supp["IDAutista"]."'>".$supp["Nome"]." ".$supp["Cognome"]."</option>";
                
        }
        
        $lineeQuery=mysqli_query($cnn,"SELECT IDLinea,Nome FROM Linee");
        if(mysqli_num_rows($lineeQuery))
        {
            while($supp=mysqli_fetch_assoc($lineeQuery))
            {
                $orari=array();
                $orariQuery=mysqli_query($cnn,"SELECT IDOrario,OraPartenza FROM Orari WHERE IDLinea=".$supp["IDLinea"]);
                
                /*selezione orari*/ 
                if(mysqli_num_rows($orariQuery))
                {
                    while($suppora=mysqli_fetch_assoc($orariQuery)){
                        $orari[]="<option value='".$suppora["IDOrario"]."'>".$suppora["OraPartenza"]."</option>";
                    }
                        
                     
                     /*costruzione elementi*/
                     echo "<tr>";
                     echo "<td><label class='checkbox-inline'><input type='checkbox' >Seleziona</label></td>";
                     echo "<td><span>".$supp["IDLinea"]."</span></td>";
                     echo "<td><span>".$supp["Nome"]."</span></td>";
                     echo "<td>";
                     echo "<select class='form-control'>";
                     foreach($orari as $orario)
                                echo $orario;
                     echo "</select>";
                     echo "</td>";
                     echo "<td>";
                     echo "<input type='number' class='form-control'>";
                     echo "</td>";
                     echo "<td>";
                     echo "<select class='form-control'>";
                      foreach($autisti as $autista)
                                echo $autista;
                     echo "</select>";
                     echo "</td>";
                     echo "<td>";
                     echo "<select class='form-control'>";
                     foreach($autobus as $pulman)
                           echo $pulman;
                     echo  "</select>";
                     echo  "</td>";
                     echo  "<td>";
                     echo  "<input type='text' class='form-control'>";
                     echo  "</td>";
                     echo   "</tr>"; 
                    
                }  
            } 
                
                
        }
       
        
	}
	mysqli_close($cnn);
       
?>
