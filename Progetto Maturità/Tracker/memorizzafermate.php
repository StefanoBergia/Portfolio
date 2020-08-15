<?php
if(isset($_POST['file_name']))
{
	$myfile = fopen("files/".$_POST['file_name'], "a") or die("Unable to open file!");
    if(isset($_POST["LAT"]) && isset($_POST["LON"]) && isset($_POST["NAME"]))
	fwrite($myfile, $_POST["LAT"].';'.$_POST["LON"].';'.$_POST["NAME"]."\n");
     else
   		echo "valori non inseriti";
	fclose($myfile);	
}else
	echo "nome del file non impostato";

?>
