<?
session_start();
if( $_SESSION['login_successfull'] != "OK" )
exit();

include("antisql.php");
include("connect2Mysql.php");


$param = $_POST['param'];
$searchText = $_POST['searchText'];
$searchType = $_POST['searchType'];
$property = $_POST['property'];
$sortType = $_POST['sortType'];
$cmd = $_POST['cmd'];
$nowPage = $_POST['nowPage'];

echo '<?xml version="1.0" encoding="utf-8"?><param>';

if($nowPage == "" )
  $nowPage = 1;


$query = mysql_query("SELECT goodsno,name,smallimage,bigimage,mainicon,subicon,price,invencnt,explain1,explain2,item_type,limit_type,limit_total,limit_remain,limit_sdate,limit_edate,limit_age,char_sex,item_property FROM MALL_LIST where name like '%" . $searchText . "%' order by sIndex limit 10");
    
	
	
    if( !$query )
        exit( "sql problem" );
    echo "<retcode><![CDATA[1]]></retcode>\n\n";
    echo "<listcount><![CDATA[10]]></listcount>";
    echo "<totalcount><![CDATA[90]]></totalcount>";
    echo "<nowpage><![CDATA[".$nowPage."]]></nowpage>";
    echo "<totalpage><![CDATA[9]]></totalpage>";
echo "<items>";

	$i = 0;
	while( $array = mysql_fetch_array( $query ) )
	{
        $i = 0;
    	echo "<item>\n";
		writeTag( "goodsno",$array[$i++] );
		writeTag( "name",$array[$i++] );
		writeTag( "smallimage",$array[$i++] );
		writeTag( "bigimage",$array[$i++] );
		writeTag( "mainicon",$array[$i++] );
		writeTag( "subicon",$array[$i++] );
		writeTag( "price",$array[$i] );
		writeTag( "dc",$array[$i++] );
		writeTag( "event_price",0 );
		writeTag( "dtype",0 );
		writeTag( "buytype",0 );
		writeTag( "rank",1 );
		
		writeTag( "invencnt",$array[$i++] );
		
		writeTag( "explain1",$array[$i++] );
		writeTag( "explain2",$array[$i++] );
		writeTag( "item_type",$array[$i++] );
		writeTag( "limit_type",$array[$i++] );
		writeTag( "limit_total",$array[$i++] );
		writeTag( "limit_remain",$array[$i++] );
		writeTag( "limit_sdate",$array[$i++] );
		writeTag( "limit_edate",$array[$i++] );
		writeTag( "limit_age",$array[$i++] );
		writeTag( "char_sex",$array[$i++] );
		writeTag( "item_property",$array[$i++] );
		echo "</item>\n";	
	}
	echo "</items>\n</" .$category.">\n";
	

function writeTag( $tagName, $tagData )
{
	echo "<" .$tagName. "><![CDATA[".$tagData."]]></" .$tagName. ">\n";
}



echo "</param>";
?>