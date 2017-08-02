<?
session_start();
?>
<? echo "<?"; ?>xml version="1.0" encoding="utf-8"<? echo "?>"; ?>
<param>
<?

include("KO100DB.php");
include("antisql.php");
include("connect2Mysql.php");

$post_data = $_POST['mgmac'];


$exp1 = explode(",",$post_data);
$exp2 = explode(chr(hexdec("0B")),$exp1[0]);

$i = 1;
$username = $exp2[$i++];
$password = $exp2[$i++];
$unk1 = $exp2[$i++];
$char = $exp2[$i++];
$unk2 = $exp2[$i++];
$unk3 = $exp2[$i++];
$unk4 = $exp2[$i++];
$mall_type = $exp2[$i++];
$unk5 = $exp2[$i++];
$unk6 = $exp2[$i++];
$unk7 = $exp2[$i++];
$unk8 = $exp2[$i++];
$class = $exp2[$i++];
$level = $exp2[$i++];



//$responseObj = new KO100DB();
//$responseObj->Signature = "LOGIN_PUS";
//$responseObj->AddParameter($username);
//$responseObj->AddParameter($password);
//$response = $responseObj->GetResponse();
//$args = $responseObj->GetArray();



if( Login( $username, $password ) == "1" )
{



	$slot = GetSlot( $username );
        $cash = GetCash( $username );
	if( $cash == -1 )
		echo "<retcode>0</retcode>";
	else
	{
        $_SESSION['inventory_empty_slot'] = 1;
        $_SESSION['login_successfull'] = "OK";
        $_SESSION['cash__count'] = $cash;
	$_SESSION['p__count'] = 0;
	$_SESSION['g___count'] = 0;
        $_SESSION['username'] = $username;
        $_SESSION['password'] = $password;
	$_SESSION['slot'] = $slot;
        $_SESSION['p__count'] = 0;
        echo "<retcode>1</retcode>";
    }
    
}else
    echo "<retcode>0</retcode>";


?>
<nid>0</nid>
<uid></uid>
<gcode>MMALL_KNIGHT</gcode>
<utype>1000</utype>
<otpcode>0</otpcode>
<site>mg</site>
<auckey>0</auckey>
<game_code>knight</game_code>
</param>