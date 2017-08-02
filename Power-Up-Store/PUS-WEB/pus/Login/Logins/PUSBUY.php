<?
session_start();
$_SESSION['pus_buy_logined'] = "";
$_SESSION['username_pus_buy'] = "";
if( $_GET['q'] == "returned" )
{
	include("../../../settings/connect2Mysql.php");
	$id = $_POST['id'];
	$password = md5($_POST['password']);
    
	$userresult = mysql_query( "select * from user where strUserID = '$id' and strPass='$password'" );
	$num=mysql_num_rows($userresult);
	if( $num )
	{
		$_SESSION['username_pus_buy'] = $id;
		$_SESSION['pus_buy_logined'] = "OK";
		echo header( 'Location: PUSBUY_PAYPAL.php' ) ;
	}
			
}

?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<link rel="stylesheet" type="text/css" href="../../css/style.css" />
<link rel="stylesheet" type="text/css" href="../../css/gamelogin.css" />
<link rel="stylesheet" type="text/css" href="../../css/popup.css" /> 
<title></title>


<script src="../../../ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
<script src="../../js/common.js"></script>
<script src="../../js/jquery.common.js"></script>
<script src="../../js/plugin/function.js"></script>
<script src="../../js/Login.js"></script>
</head> 
<body oncontextmenu="return false" onselectstart="return false" ondragstart="return false">
<form name="frm" id="frm" action="PUSBUY.php?q=returned" method="post">
<input type="hidden" name="rq" id="rq" value="aHR0cHM6Ly9iaWxsaW5nLm50dGdhbWUuY29tL3BheW1lbnQvU3RlcDEuYXNweA==">
<input type="hidden" name="lu" id="lu" value="/Login/Logins/GameLogin">

    <div id="wrap">
	<div id="gamelogin">
		<div class="table">
		<table border="0" cellspacing="0" cellpadding="0" align="center">
			<tr>
				<td width="60" height="30" class="text_idpw">ID</td>
				<td width="204" height="30">
                                    <input type="text" name="id" id="id" class="gameid_input" maxlength="20" title="ID" tabindex="1" accesskey="l" />
				</td>
                                <td width="77" rowspan="2" align="right"><img src="../../images/gamelogin/btn_loginok.gif" width="63" height="65" alt="LOGIN" tabindex="3" onClick="document.forms['frm'].submit();" style="cursor:pointer;" /></td>
			</tr>
			<tr>
				<td width="60" height="30" class="text_idpw">Password</td>
				<td width="204" height="30"><input type="password" name="password" id="password" class="gamepw_input" title="PASSWORD" tabindex="2" maxlength="20" accesskey="p" onKeyDown="util.enter_key('Login._Login');" /></td>
			</tr>
		</table>
		</div>
	</div>
</div>

</form>
</div>
<div id="dBlank" class="hidden"></div>
<div id="msgbox"></div>
</body>

</html>