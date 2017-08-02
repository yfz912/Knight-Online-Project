<?
include("antisql.php");
include("connect2Mysql.php");

$query = mysql_query("SELECT main_type,name,menu_type FROM MALL_MAIN_CATEGORY ORDER BY sIndex");
    
    if( !$query )
        exit( "sql problem" );
        
echo '<?xml version="1.0" encoding="utf-8"?><param>';
echo "<retcode><![CDATA[1]]></retcode>\n";
echo "<items>\n";

while( $array = mysql_fetch_array( $query ) )
{
    echo "<item>\n";
    echo "<main_type><![CDATA[".$array[0]."]]></main_type>\n";
    echo "<name><![CDATA[".$array[1]."]]></name>\n";
    echo "<menu_type><![CDATA[".$array[2]."]]></menu_type>\n";
    echo "</item>\n";
}
echo "</items>\n</param>"

?>
