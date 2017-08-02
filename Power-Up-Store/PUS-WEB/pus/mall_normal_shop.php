<?
include("antisql.php");
include("connect2Mysql.php");


session_start();
echo '<?xml version="1.0" encoding="utf-8"?><param>';
$command = $_POST['cmd'];
$shopNum = $_POST['shopNum'];
$nowPage = $_POST['nowPage'];



if( $command == "normalShop" )
{
	if( !is_numeric( $shopNum ) 
	|| !is_numeric( $nowPage ) 
	|| $nowPage <= 0)
		exit();

$query_category = mysql_query("select * from MALL_MAIN_CATEGORY where main_type =" . $shopNum);
if( !$query_category )
    exit();
$array_category = mysql_fetch_array( $query_category );


$query_mall = mysql_query("select count(*) from MALL_LIST where item_property ='" . $array_category["name"] . "'");

if( !$query_mall )
    exit();
$array_mall = mysql_fetch_array( $query_mall );

$mall_count = $array_mall[0];

$query_mall = mysql_query("select * from MALL_LIST where item_property ='" . $array_category["name"] ."'");
if( !$query_mall )
    exit();

$per_page_mall_count = $_POST['listCount'];
if( $per_page_mall_count == '' )
$per_page_mall_count = 10;

$max_page = $mall_count / $per_page_mall_count;
if( is_float($max_page) )
    $max_page = (int)$max_page + 1;
    
if( $nowPage > $max_page )    
    exit();

$req_min_count = $per_page_mall_count * ($nowPage - 1); //0
$req_max_count = ($nowPage * $per_page_mall_count) -1 ; // 4
$count = 0;

echo "<retcode><![CDATA[1]]></retcode>\n";
echo "<listcount><![CDATA[".$per_page_mall_count."]]></listcount>\n";
echo "<totalcount><![CDATA[" .$mall_count. "]]></totalcount>\n";
echo "<nowpage><![CDATA[".$nowPage."]]></nowpage>\n";
echo "<totalpage><![CDATA[".$max_page."]]></totalpage>\n";
echo "<items>\n";

while( $array = mysql_fetch_array( $query_mall ) )
{
    
	if( $count >= $req_min_count
	&& $count <= $req_max_count )
	{
        echo "<item>\n";
    	$i = 3;
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
        writeTag( "rank","0" );
		writeTag( "invencnt",$array[$i++] );
		
		writeTag( "explain1",$array[$i++] );
		writeTag( "explain2",$array[$i++] );
		writeTag( "item_type",$array[$i++] );

		writeTag( "limit_total",$array[$i++] );
		writeTag( "limit_remain",$array[$i++] );
		writeTag( "limit_sdate",$array[$i++] );
		writeTag( "limit_edate",$array[$i++] );
		writeTag( "limit_age",$array[$i++] );

		writeTag( "char_sex",$array[$i++] );
		writeTag( "item_property",$array[$i++] );
        
        
        echo "</item>\n";
	}
	$count++;
	if( $count > $req_max_count )
	break;
}
echo "</items></param>";
}
function writeTag( $tagName, $tagData )
{
    echo "<" .$tagName. "><![CDATA[".$tagData."]]></" .$tagName. ">\n";
}
?>

