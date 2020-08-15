<?php header("Access-Control-Allow-Origin:*");
if(isset($_GET["file_name"]))
{
	
	$fh = fopen("../files/".$_GET["file_name"],'r');
  	while ($line = fgets($fh)) {
    	echo $line;
  	}
   fclose($fh);
}else
echo "KO";

?>
