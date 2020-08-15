<?php header("Access-Control-Allow-Origin:*");  
    if(isset($_POST["IDOrario"])){
        $idOrario=$_POST["IDOrario"];
        $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
        if(!mysqli_errno($cnn)){     
		$res=mysqli_query($cnn,"SELECT Tratte.IDTratta AS ID,IDAutobus,Concat(Autisti.Nome,' ',Autisti.Cognome)AS Autista, (MAX(Tappe.Offset)+Tratte.Ritardo) AS Ritardo, Tappe.IDPrima AS Fermata FROM Tratte,Autisti,Tappe WHERE Tratte.IDAutista=Autisti.IDAutista AND Tappe.IDTratta=Tratte.IDTratta AND Tratte.Data=CURDATE() AND Tratte.InCorso=1 AND Tratte.IDOrario={$_POST['IDOrario']} GROUP BY Tratte.IDTratta,IDAutobus,Autisti.Nome,Autisti.Cognome,Tratte.Ritardo,Tappe.IDPrima ORDER BY (MAX(Tappe.Offset)+Tratte.Ritardo) DESC LIMIT 1");
            if(mysqli_num_rows($res))
            {   
                /*
                dati relativi all'ultima tappa della linea in corso
                ID idtratta
                Autista
                Tempo 
                Fermata fermata prima
                */

                $dati=mysqli_fetch_assoc($res);
                /*recupero offset dell'ultima tappa con idsucc=fermata
                ci sommo il ritardo alla partenza
                recupero offset dellafermata
                calcolo differenza*/

                
                $ritardo=mysqli_query($cnn,"SELECT Percorsi.Offset-(SELECT MAX(Offset)-Tratte.Ritardo*60000 FROM Tappe,Tratte WHERE Tratte.IDTratta=Tappe.IDTratta AND Tratte.IDTratta={$dati['ID']} AND Tappe.IDDopo={$dati['Fermata']}) FROM Percorsi,Linee,Orari,Tratte WHERE Percorsi.IDLinea=Linee.IDLinea AND Linee.IDlinea=Orari.IDLinea AND Orari.IDOrario=Tratte.IDOrario AND Tratte.IDTratta={$dati['ID']} AND Percorsi.IDFermata={$dati['Fermata']} ");
                
                $ritardoVet=mysqli_fetch_array($ritardo);
                
                $dati["Ritardo"]=$ritardoVet[0];
                echo "".json_encode($dati);
                
            }else
                echo "KO";
              
        }       
        mysqli_close($cnn);
    }; 
?>
