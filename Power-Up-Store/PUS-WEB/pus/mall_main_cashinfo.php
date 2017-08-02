<?
session_start();
echo '<?xml version="1.0" encoding="utf-8"?>';
?>
<param>
<retcode><![CDATA[<? echo $_SESSION['login_successfull'] == "OK" ? "1" : "0";  ?>]]></retcode>
<? if ($_SESSION['login_successfull'] == "OK")
{ 

?>
<items>
<nMCash><![CDATA[<? echo $_SESSION['cash__count']; ?>]]></nMCash>
<nPCash><![CDATA[<? echo $_SESSION['p__count']; ?>]]></nPCash>
<nSettle><![CDATA[<? echo $_SESSION['s__count']; ?>]]></nSettle>
<nPresent><![CDATA[<? echo $_SESSION['p___count']; ?>]]></nPresent>
<nJorgi><![CDATA[<? echo $_SESSION['j___count']; ?>]]></nJorgi>
<gPoint><![CDATA[<? echo $_SESSION['g___count']; ?>]]></gPoint>
</items>
<? } ?>
</param>