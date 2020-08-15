<?php header("Access-Control-Allow-Origin:*");  
    if(isset($_POST["Partenza"])&&
       isset($_POST["Arrivo"])){
        $partenza= strtolower($_POST["Partenza"]);
        $arrivo=   strtolower($_POST["Arrivo"]);
        $linee=array();      
        $cnn=mysqli_connect("localhost","bustracker","","my_bustracker");
        if(!mysqli_errno($cnn)){
          $res=mysqli_query($cnn,"SELECT * FROM Linee");
          if(mysqli_num_rows($res))
          {
              while($linea=mysqli_fetch_assoc($res))
              {
                  $id=$linea["IDLinea"];
                  $val=mysqli_query($cnn,"SELECT Fermate.Nome AS Fermata,Localita.Nome AS Localita FROM Percorsi,Fermate,Localita WHERE Percorsi.IDLinea=".$id." AND Percorsi.IDFermata=Fermate.IDFermata AND Fermate.IDLocalita=Localita.IDLocalita");
                  if(mysqli_num_rows($val))
                  {
                      $order=0;
                      while($fermata=mysqli_fetch_assoc($val))
                      {
                          if($order==0 && (strtolower($fermata["Fermata"])==$partenza || strtolower($fermata["Localita"])==$partenza)){
                            $order=1;
                          }
                          elseif  ($order==1 && (strtolower($fermata["Fermata"])==$arrivo || strtolower($fermata["Localita"])==$arrivo))
                          {
                              $order=2;
                              break;
                          }
                            
                      }   
                      if($order==2)
                      {
                          $oreres=mysqli_query($cnn,"SELECT Linee.IDLinea AS IDLinea,Orari.IDorario AS IDOrario, Linee.Nome AS Nome, Orari.OraPartenza AS Ora, Ditte.RagSoc AS Ditta FROM Linee,Orari,Ditte WHERE Ditte.IDDitta=Linee.IDDitta AND Linee.IDLinea=Orari.IDlinea AND Linee.IDLinea=".$id);
                          if(mysqli_num_rows($oreres))
                          {
                               while($orelinea=mysqli_fetch_assoc($oreres)){
                                    $linee[]=$orelinea; 
                               }
                               echo json_encode( array("linee"=>$linee));
                          }else
                            echo "KO";
                      }
                  }
              }
              
          }
        }
        mysqli_close($cnn);
    };
?>
