class com.mgame.webMall.main.rightMain.CashPage
{
    function CashPage()
    {
    } // End of the function
    function cashPageLoad(mainData)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        rightMainData = new com.mgame.webMall.main.rightMain.RightMainData();
        rightMainData.__set__rightMain(mainData.__get__mainStage().rightMain);
        mainData.__set__rightMainData(rightMainData);
        this.buttonLoad();
        this.cashXmlLoad();
    } // End of the function
    function cashXmlLoad()
    {
        var _loc2 = new com.mgame.webMall.main.rightMain.CashXml();
        _loc2.xmlLoad(this, rightMainData);
    } // End of the function
    function xmlOnLoad()
    {
        nPresent_txt.text = rightMainData.nPresent;
        nJorgi_txt.text = rightMainData.nJorgi;
        nMCash_txt.text = numberSplit.split(rightMainData.__get__nMCash());
        nPCash_txt.text = numberSplit.split(rightMainData.__get__nPCash());
        nSettle_txt.text = rightMainData.nSettle;
        gPoint_txt.text = numberSplit.split(rightMainData.__get__gPoint());
    } // End of the function
    function webPointXmlOnLoad()
    {
        webPoint_txt.text = numberSplit.split(rightMainData.__get__webPoint());
    } // End of the function
    function buttonLoad()
    {
        nPresent_txt = rightMainData.__get__rightMain().nPresent_txt;
        nJorgi_txt = rightMainData.__get__rightMain().nJorgi_txt;
        nMCash_txt = rightMainData.__get__rightMain().nMCash_txt;
        nPCash_txt = rightMainData.__get__rightMain().nPCash_txt;
        nSettle_txt = rightMainData.__get__rightMain().nSettle_txt;
        gPoint_txt = rightMainData.__get__rightMain().gPoint_txt;
        webPoint_txt = rightMainData.__get__rightMain().webPoint_txt;
    } // End of the function
    function getRightMainData()
    {
        return (rightMainData);
    } // End of the function
    var rightMainData = null;
    var numberSplit = null;
    var nPresent_txt = null;
    var nJorgi_txt = null;
    var nMCash_txt = null;
    var nPCash_txt = null;
    var nSettle_txt = null;
    var webPoint_txt = null;
    var gPoint_txt = null;
} // End of Class
