<?
session_start();
include("KO100DB.php");
include("connect2Mysql.php");
include("antisql.php");

if( $_SESSION['login_successfull'] != "OK" )
    exit();

echo '<?xml version="1.0" encoding="utf-8"?>';
echo '<param>';
echo '<retcode><![CDATA[1]]></retcode>';

$cmd = $_POST['cmd'];
$itemID = $_POST['itemID'];
$itemCount = $_POST['itemCount'];
$itemCount = 1;
$ret = 0;
$totalInven = 0;


if( $cmd == "BUY_NORMAL" )
{
    

    $query = mysql_query("select * from MALL_LIST where goodsno = ".$itemID);
    $numRes = mysql_num_rows($query);
    if( $numRes )
    {
        $_SESSION['BUY_ITEM_ID'] = $itemID;
        $_SESSION['BUY_ITEM_CO'] = $itemCount;
        $array = mysql_fetch_array( $query );
        $ret = 1;        
        $msg = $array["name"] .chr(hexdec("0B")). $itemCount .chr(hexdec("0B")).$itemCount * $array["price"].chr(hexdec("0B")).date("m.d.y H:i");
        
    }
}else if ( $cmd == "CASH_INVEN_CHECK" )
{
     $query = mysql_query("select * from MALL_LIST where goodsno = ".$_SESSION['BUY_ITEM_ID']);
     $numRes = mysql_num_rows($query);

     if( $numRes )
     {
    	
		$cash2 = GetCash( $_SESSION['username'] );

		if( !$cash2 || $cash2 == -1 )
		{
			$_SESSION['BUY_ITEM_ID'] = 0;
			$_SESSION['BUY_ITEM_CO'] = 0;        
			exit();
		}

		$array_item = mysql_fetch_array( $query );
		
		if(  $array_item["price"] == 0 || $cash2 == 0 || $cash2 < $array_item["price"] /*|| $_SESSION['slot'] <= 0*/		)
		{
			$_SESSION['BUY_ITEM_ID'] = 0;
			$_SESSION['BUY_ITEM_CO'] = 0; 			
			exit();
		}
        

			
		$cmd = "INVEN_CHECK";
     		$ret = "1";
        

		BuyItem($_SESSION['username'],$_SESSION['BUY_ITEM_ID'],$_SESSION['BUY_ITEM_CO']);
		$_SESSION['BUY_ITEM_ID'] = 0;
        $_SESSION['BUY_ITEM_CO'] = 0;   
        if( $ret == 1 )
        {
            $_SESSION['cash__count'] -= $array_item["price"];
            $_SESSION['slot'] -= 1;
			//mysql_query("update USER_INFO set nCash = nCash - " .$array_item["price"]." where strAccountID='" . $_SESSION['username'] . "'");
            UpdateCash( $_SESSION['username'],$array_item["price"]);
            //$date = date('Y-m-d H:i:s');
          
            
           // mysql_query("insert into PUS_PURCHASE_HISTORY values (0,".$itemID.",'".$array_item['name']."',".$array_item['price'].",".$_SESSION['cash__count'].",'' )");
            
            
        }
        
        
     }
    

}
    
    echo "<items>";
    echo "<ret><![CDATA[$ret]]></ret>";
    echo "<cmd><![CDATA[$cmd]]></cmd>";
    echo "<msg><![CDATA[$msg]]></msg>";
    echo "<totalInven><![CDATA[$totalInven]]></totalInven>";
    echo "<inven><![CDATA[]]></inven>";
    echo "</items>";
echo '</param>';
?>