<?
$mysql = mysql_connect("127.0.0.1","root","sessiz123");
if( !$mysql  )
exit("zz");

mysql_select_db("pus_db");


		
function Login( $username, $password)
{
	$mssql = odbc_connect("kn_online","myko","myko"); 
	if( !$mssql )
		return -1;
	$q = odbc_exec($mssql,"select count(*) from tb_user where strAccountID ='$username' and strPasswd ='$password'");
	$a = odbc_fetch_row( $q );
	$r = odbc_result($q,1);
	odbc_close( $mssql );

	return $r;
	
}

function BuyItem( $username, $item, $count)
{
	$mssql = odbc_connect("kn_online","myko","myko"); 
	if( !$mssql )
		return -1;
	$q = odbc_exec($mssql,"exec INSERT_WEBITEM '$username','$item',1");
	odbc_close( $mssql );
}



function GetCash( $accountid )
{
	$mssql = odbc_connect("kn_online","myko","myko"); 
	if( !$mssql )
		return -1;
	$q = odbc_exec($mssql,"select CashPoint from TB_USER where strAccountID='$accountid'");
	$a = odbc_fetch_array( $q );
	odbc_close( $mssql );
	return  $a["CashPoint"];
	
}	
function GetSlot( $accountid )
{

	$mssql = odbc_connect("kn_online","myko","myko"); 
	if( !$mssql )
		return -1;
	$q = odbc_exec($mssql,"select slot from CURRENTUSER where strAccountID='$accountid'");
	$a = odbc_fetch_array( $q );
	odbc_close( $mssql );
	return  $a["slot"];
	
}	
function UpdateCash( $accountid,$cash )
{
	$mssql = odbc_connect("kn_online","myko","myko");
	if( !$mssql )
		return -1;
	$q = odbc_exec($mssql,"update tb_user set CashPoint = CashPoint - $cash where strAccountID='$accountid'");
	odbc_close( $mssql );
	
}	
?>