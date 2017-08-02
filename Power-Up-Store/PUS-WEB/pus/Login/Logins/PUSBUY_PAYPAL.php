<? 
session_start();
if( $_SESSION['pus_buy_logined'] != "OK" )
    exit();
    
include("../../../pus/connect2Mysql.php");
$esn = $_GET['esn'];
if( $esn == "okey" )
{
	$esn_t = $_POST['esn_t'];
	$esn_t2 = $_POST['esn_t2'];
	$esn_t3 = $_POST['esn_t3'];
	$esn_t4 = $_POST['esn_t4'];
	$esn_t5 = $_POST['esn_t5'];
	$esn_t6 = $_POST['esn_t6'];
	$esn_t7 = $_POST['esn_t7'];
	$all_esn = "$esn_t-$esn_t2-$esn_t3-$esn_t4-$esn_t5-$esn_t6-$esn_t7";
	$sql = "select * from ESN_LIST where ESN = '$all_esn' and Used = 0";
	$query_esn = mysql_query($sql);
	$count=mysql_num_rows($query_esn);
	
	if( !$count )
		echo "ESN kodu hatali.<br><br><br>";
	else
	{
		$array = mysql_fetch_array($query_esn);
		mysql_query("update ESN_LIST SET Used = 1 where sIndex = $array[0]");
		mysql_query("update USER_INFO SET nCash = nCash + $array[4] where strAccountID = '".$_SESSION['username_pus_buy']."'");
		$sql = "INSERT INTO PURCHASE_HISTORY VALUES (0,'".$_SESSION['username_pus_buy']."','$payment_amount','$payer_id','$address_street','$payment_date','$payment_status','$address_zip','$first_name','$last_name','$business','$all_esn','$payer_email','$mc_currency','$array[4]')";
        mysql_query($sql);
		echo $array[4] . " cash hesabiniza yuklendi.<br><br><br>";
	}
	
}	
	
	
	?>
<form action="https://www.paypal.com/cgi-bin/webscr" method="post" target="_top">
<input type="hidden" name="cmd" value="_xclick">
<input type="hidden" name="business" value="buyko100@mail.com">
<input type="hidden" name="lc" value="TR">
<input type="hidden" name="item_name" value="KO100 PUS">
<input type="hidden" name="button_subtype" value="services">
<input type="hidden" name="no_note" value="0">
<input type="hidden" name="currency_code" value="USD">
<input type="hidden" name="bn" value="PP-BuyNowBF:btn_buynowCC_LG.gif:NonHostedGuest">
<table>
<tr><td><input type="hidden" name="on0" value="<? echo $_SESSION['username_pus_buy']; ?>"></td></tr><tr><td><select name="os0">
    <option value="500 Cash">500 Cash $5,00 USD</option>
	<option value="1000 Cash">1000 Cash $10,00 USD</option>
	<option value="1500 Cash">1500 Cash $15,00 USD</option>
	<option value="2000 Cash">2000 Cash $20,00 USD</option>
	<option value="2500 Cash">2500 Cash $25,00 USD</option>
	<option value="3000 Cash">3000 Cash $30,00 USD</option>
	<option value="3500 Cash">3500 Cash $35,00 USD</option>
	<option value="4000 Cash">4000 Cash $40,00 USD</option>
	<option value="4500 Cash">4500 Cash $45,00 USD</option>
	<option value="5000 Cash">5000 Cash $50,00 USD</option>
</select> </td></tr>
</table>
<input type="hidden" name="currency_code" value="USD">
<input type="hidden" name="option_select0" value="500 Cash">
<input type="hidden" name="option_amount0" value="5.00">
<input type="hidden" name="option_select1" value="1000 Cash">
<input type="hidden" name="option_amount1" value="10.00">
<input type="hidden" name="option_select2" value="1500 Cash">
<input type="hidden" name="option_amount2" value="15.00">
<input type="hidden" name="option_select3" value="2000 Cash">
<input type="hidden" name="option_amount3" value="20.00">
<input type="hidden" name="option_select4" value="2500 Cash">
<input type="hidden" name="option_amount4" value="25.00">
<input type="hidden" name="option_select5" value="3000 Cash">
<input type="hidden" name="option_amount5" value="30.00">
<input type="hidden" name="option_select6" value="3500 Cash">
<input type="hidden" name="option_amount6" value="35.00">
<input type="hidden" name="option_select7" value="4000 Cash">
<input type="hidden" name="option_amount7" value="40.00">
<input type="hidden" name="option_select8" value="4500 Cash">
<input type="hidden" name="option_amount8" value="45.00">
<input type="hidden" name="option_select9" value="5000 Cash">
<input type="hidden" name="option_amount9" value="50.00">
<input type="hidden" name="option_index" value="0">
<input type="image" src="https://www.paypalobjects.com/en_US/TR/i/btn/btn_buynowCC_LG.gif" border="0" name="submit" alt="PayPal - The safer, easier way to pay online!">
<img alt="" border="0" src="https://www.paypalobjects.com/en_US/i/scr/pixel.gif" width="1" height="1">
</form>



<p>&nbsp;</p>
<p>Zaten bir ESN'ye sahipseniz,
</p>
<form name="form1" method="post" action="?esn=okey">
  ESN: 
  <label>
  <input name="esn_t" type="text" id="esn_t" size="10">
  </label> 
  - 
  <input name="esn_t2" type="text" id="esn_t2" size="10"> 
  - 
  <input name="esn_t3" type="text" id="esn_t3" size="10"> 
  -
  <input name="esn_t4" type="text" id="esn_t4" size="10">
  - 
  <input name="esn_t5" type="text" id="esn_t5" size="10">
   - 
   <input name="esn_t6" type="text" id="esn_t6" size="10">
    - 
    <input name="esn_t7" type="text" id="esn_t7" size="10">
    <br>
  &ouml;rn.(9999999-u2m0-9tzzk-etux-0l3x-k4rr-fx87)
  <br>
  <label>
  <input type="submit" name="Submit" value="Kaydet">
  </label>
</form>
<p>&nbsp;</p>
