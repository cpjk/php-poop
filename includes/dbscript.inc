<?php

function launchDbScript($sqlFileToExecute, $selectDb, $reportError)
{
	$link = mysqli_connect(DB_SERVER, DB_USER, DB_PWD);
	if (!$link && $reportError) {
	  echo "Error : MySQL Connection error";
	}
	 
	if ($selectDb)
		mysqli_select_db($link, DB_NAME);
	 
	// read the sql file
	$f = fopen($sqlFileToExecute,"r+");
	$sqlFile = fread($f, filesize($sqlFileToExecute));
	$sqlArray = explode(';',$sqlFile);
	$sqlErrorCode = 0;
	foreach ($sqlArray as $stmt) {
	  if (strlen($stmt)>3 && substr(ltrim($stmt),0,2)!='/*') {
		$result = mysqli_query($link, $stmt);
		if (!$result) {
		  $sqlErrorCode = mysqli_errno($link);
		  $sqlErrorText = mysqli_error($link);
		  $sqlStmt = $stmt;
		  break;
		}
	  }
	}
	if ($sqlErrorCode == 0) {
	  echo "Script is executed succesfully!<br />";
	} else if ($reportError) {
	  echo "An error occured during script!<br/>";
	  echo "Error code: $sqlErrorCode<br/>";
	  echo "Error text: $sqlErrorText<br/>";
	  echo "Statement:<br/> $sqlStmt<br/>";
	}
}
 
?>
