<?
session_start();
if( $_SESSION['login_successfull'] != "OK" )
exit();

include("antisql.php");
include("connect2Mysql.php");


echo '<?xml version="1.0" encoding="utf-8"?><param>';
function writeCategory( $category )
{
    
	if( $category == "BESTBUY")
		$query = mysql_query("SELECT * FROM MALL_LIST ORDER BY sellCount DESC LIMIT 5");
	else
		$query = mysql_query("SELECT * FROM MALL_LIST where view_type like '%" . $category . "%'");
    
	
	
    if( !$query )
        exit( "sql problem" );
    echo "<".$category.">\n<retcode><![CDATA[1]]></retcode>\n<items>\n";
	$i = 0;
	while( $array = mysql_fetch_array( $query ) )
	{
        $i = 2;
    	echo "<item>\n";

		writeTag( "view_type",$category );
		writeTag( "view_rank",$array[$i++] );
		writeTag( "goodsno",$array[$i++] );
		writeTag( "name",$array[$i++] );
		writeTag( "smallimage",$array[$i++] );
		writeTag( "bigimage",$array[$i++] );
		writeTag( "mainicon",$array[$i++] );
		writeTag( "subicon",$array[$i++] );
		writeTag( "price",$array[$i] );
		writeTag( "dc",$array[$i++] );
		
		writeTag( "event_price",$array[$i++] );
		writeTag( "dtype",$array[$i++] );
		writeTag( "buytype",$array[$i++] );
		writeTag( "invencnt",$array[$i++] );
		
		writeTag( "explain1",$array[$i++] );
		writeTag( "explain2",$array[$i++] );
		writeTag( "item_type",$array[$i++] );
		writeTag( "view_type",$array[$i++] );
		writeTag( "limit_total",$array[$i++] );
		writeTag( "limit_remain",$array[$i++] );
		writeTag( "limit_sdate",$array[$i++] );
		writeTag( "limit_edate",$array[$i++] );
		writeTag( "limit_age",$array[$i++] );
		writeTag( "issue_check",$array[$i++] );
		writeTag( "issue_image",$array[$i++] );
		writeTag( "char_sex",$array[$i++] );
		writeTag( "item_property",$array[$i++] );
		echo "</item>\n";	
	}
	echo "</items>\n</" .$category.">\n";
	
}
function writeTag( $tagName, $tagData )
{
	echo "<" .$tagName. "><![CDATA[".$tagData."]]></" .$tagName. ">\n";
}


writeCategory("ABILITY");
writeCategory("BESTBUY");
writeCategory("BESTGIFT");
writeCategory("CHARACTER");
writeCategory("ISSUE");
writeCategory("MYSTERY");
writeCategory("NEW");
writeCategory("RECOM");
echo "</param>";
?>