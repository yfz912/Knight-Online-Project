<? 
if( $_SESSION['login_successfull'] != "OK" )
    exit(); ?>
<form action="https://www.paypal.com/cgi-bin/webscr" method="post" target="_top">
<input type="hidden" name="cmd" value="_s-xclick">
<input type="hidden" name="hosted_button_id" value="3YUALXSWEX96U">
<table>
<tr><td><input type="hidden" name="on0" value="<? echo $_SESSION['username']; ?>"></td></tr><tr><td><select name="os0">
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
<input type="image" src="https://www.paypalobjects.com/tr_TR/TR/i/btn/btn_buynowCC_LG.gif" border="0" name="submit" alt="PayPal - Online ödeme yapmanın daha güvenli ve kolay yolu!">
<img alt="" border="0" src="https://www.paypalobjects.com/tr_TR/i/scr/pixel.gif" width="1" height="1">
</form>
