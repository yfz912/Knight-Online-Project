<?
if (!function_exists('sql_inject_chec')) {
function sql_inject_chec(){
		// Anti-SQL Injection 
	    $badwords = array("--","'","DROP", "SELECT", "UPDATE", "DELETE", "drop", "select", "update", "delete", "WHERE", "where","exec","EXEC","procedure","PROCEDURE"); 
		foreach($_REQUEST as $key => $value)  {
		  if($key=="w") //system
			  continue;
		  foreach($badwords as $word) 
		    if(substr_count(strtolower($value), strtolower($word)) > 0) {			
				ErrorMsg("#sql_i","anti");  
                exit();
			 		}
				}
	}
}

function ErrorMsg($i,$j)
{
    echo "source:".$i.",from:".$j;
}
	sql_inject_chec();
?>