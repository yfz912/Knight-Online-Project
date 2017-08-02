<?
include("antisql.php");
include("connect2Mysql.php");


$req = 'cmd=_notify-validate';
foreach ($_POST as $key => $value) {
$value = urlencode(stripslashes($value));
$req .= "&$key=$value";
}

$header .= "POST /cgi-bin/webscr HTTP/1.0\r\n";
$header .= "Host: www.paypal.com\r\n";
$header .= "Content-Type: application/x-www-form-urlencoded\r\n";
$header .= "Content-Length: " . strlen($req) . "\r\n\r\n";
$fp = fsockopen ('ssl://www.paypal.com', 443, $errno, $errstr, 30);


$errnote = "NO_NOTE";

$accountID = $_POST['option_name1'];
$txn_id = $_POST['txn_id'];
$payment_amount = $_POST['mc_gross'];
$payer_id = $_POST['payer_id'];
$address_street = $_POST['address_street'];
$payment_date = $_POST['payment_date'];
$payment_status = $_POST['payment_status'];
$address_zip = $_POST['address_zip'];
$first_name = $_POST['first_name'];
$last_name = $_POST['last_name'];
$business = $_POST['business'];
$payer_email = $_POST['payer_email'];
$mc_currency = $_POST['mc_currency'];


if(!$fp)
{
    $errnote = "fsockopen failed." ; 
    WriteError($accountID,$errnote,$txn_id,$payment_amount,$req);
}
fputs ($fp, $header . $req);

$isVerified = false;

while (!feof($fp)) 
{
    $res = fgets ($fp, 1024);
    if (strcmp ($res, "VERIFIED") == 0) 
    {
        $isVerified = true;
    }else if (strcmp ($res, "INVALID") == 0) 
    {
        $errnote = "INVALID_TXN_ID.\n";
        WriteError($accountID,$errnote,$txn_id,$payment_amount,$req);
    }
}

fclose ($fp);

if( $isVerified == true )
{
    if( $payment_status != "Completed" )
    {
        $errnote = "Payment_Status = " . $payment_status;
		WriteError($accountID,$errnote,$txn_id,$payment_amount,$req);
	}else
	{
        
        switch( $payment_amount )
        {
            case "5.00":
                $cash = 500;
                break;
            case "10.00":
                $cash = 1000;                
                break;
            case "15.00":
                $cash = 1500;                
                break;
            case "20.00":
                $cash = 2000;                
                break;
            case "25.00":
                $cash = 2500;                
                break;
            case "30.00":
                $cash = 3000;                
                break;  
            case "35.00":
                $cash = 3500;                
                break;  
            case "40.00":
                $cash = 4000;                
                break;  
            case "45.00":
                $cash = 4500;                
                break; 
            case "50.00":
                $cash = 5000;                
                break;                  
            default:
                $errnote = "Unknown payment amount ($payment_amount)";
                WriteError($accountID,$errnote,$txn_id,$payment_amount,$req);
                break;
        }
        $sql = "SELECT COUNT(*) FROM PURCHASE_HISTORY WHERE txn_id = '$txn_id'";
    	$query = mysql_query($sql);
        
        
	    if( !$query )
        {
         	$errnote = " DUPLICATED_TXN_ID ERROR 1 ;  " . $sql;
    		WriteError($accountID,$errnote,$txn_id,$payment_amount,$req);                       
        }   
		$txn_count = mysql_fetch_array( $query );
		
		if( $txn_count[0] > 0 )
		{
	       	$errnote = " DUPLICATED_TXN_ID ERROR 2 ;  " . $sql;
    		WriteError($accountID,$errnote,$txn_id,$payment_amount,$req);      	
		}
		
        $sql = "UPDATE USER_INFO SET nCash = nCash + $cash where strAccountID = '$accountID'";
        
    	$query = mysql_query($sql);
	    if( !$query )
        {
         	$errnote = " USER_INFO_QUERY ERROR ;  " . $sql;
    		WriteError($accountID,$errnote,$txn_id,$payment_amount,$req);                       
        }        
        
                    
            
        $sql = "INSERT INTO PURCHASE_HISTORY VALUES (0,'$accountID','$payment_amount','$payer_id','$address_street','$payment_date','$payment_status','$address_zip','$first_name','$last_name','$business','$txn_id','$payer_email','$mc_currency','$cash')";
        
        
		$query = mysql_query($sql);
	    if( !$query )
        {
         	$errnote = " LOG_MYSQL_QUERY ERROR ;  " . $sql;
    		WriteError($accountID,$errnote,$txn_id,$payment_amount,$req);                       
        }
        
    }
}

function WriteError($accountID,$errnote,$txn_id,$payment_amount,$req)
{
    $ErrFile = fopen ("PAYPAL_VERIF_ERRORS.html" , 'aw');
    $error = "<b>NewError--------------------</b><br>";
    $error .= "accountID = " . $accountID . "<br>";
    $error .= "errorNote = " . $errnote . "<br>";
    $error .= "txn_id = " . $txn_id . "<br>";
    $error .= "payment_amount = " . $payment_amount . "<br>";
    $error .= "Request = " . $req . "<br>";
    $error .= "<b>EndError--------------------</b><br><br><br>";
    fwrite ( $ErrFile , $error ) ;
    exit();
}

?>
