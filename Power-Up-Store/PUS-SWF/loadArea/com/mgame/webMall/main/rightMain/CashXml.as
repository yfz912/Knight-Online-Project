class com.mgame.webMall.main.rightMain.CashXml
{
    function CashXml()
    {
    } // End of the function
    function xmlLoad(cashPage, rightMainData)
    {
        this.cashPage = cashPage;
        this.rightMainData = rightMainData;
        var _this = this;
        var _loc5 = com.mgame.webMall.main.CommonDataUrl.__get__cashURL();
        var _loc4 = "cashInfo";
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        _loc2.onLoad = function ()
        {
            _this.dataParser(this);
        };
        var _loc3 = new LoadVars();
        _loc3.cmd = _loc4;
        _loc3.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc3.sendAndLoad(_loc5, _loc2, "POST");
    } // End of the function
    function webPointXmlLoad()
    {
        var _this = this;
        var _loc4 = com.mgame.webMall.main.CommonDataUrl.__get__commonPopupCompleteURL();
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        _loc2.onLoad = function ()
        {
            _this.webPointXmlOnLoad(this);
        };
        var _loc3 = new LoadVars();
        _loc3.cmd = "WEBPOINT_BALANCE";
        _loc3.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc3.sendAndLoad(_loc4, _loc2, "POST");
    } // End of the function
    function dataParser(xmlData)
    {
        xmlData = xmlData;
        var _loc4 = Number(xmlData.firstChild.firstChild.firstChild.nodeValue);
        var _loc2 = xmlData.firstChild.firstChild.nextSibling.childNodes;
        if (_loc4)
        {
            rightMainData.__set__nMCash(_loc2[0].firstChild.nodeValue);
            rightMainData.__set__nPCash(_loc2[1].firstChild.nodeValue);
            rightMainData.__set__nSettle(_loc2[2].firstChild.nodeValue);
            rightMainData.__set__nPresent(_loc2[3].firstChild.nodeValue);
            rightMainData.__set__nJorgi(_loc2[4].firstChild.nodeValue);
            rightMainData.__set__gPoint(_loc2[5].firstChild.nodeValue);
            cashPage.xmlOnLoad();
        }
        else
        {
            this.xmlLoadError(xmlData);
        } // end else if
    } // End of the function
    function webPointXmlOnLoad(xmlData)
    {
        var _loc2 = xmlData.firstChild.firstChild.nextSibling.childNodes[0].firstChild.nodeValue;
        var _loc3 = xmlData.firstChild.firstChild.nextSibling.childNodes[3].firstChild.nodeValue;
        if (_loc2 == "1")
        {
            rightMainData.__set__webPoint(_loc3);
            cashPage.webPointXmlOnLoad();
        }
        else
        {
            trace ("cash_webPoint load error");
        } // end else if
    } // End of the function
    function xmlLoadError(e)
    {
        trace ("=========cash xml load error=========\n");
        trace (e);
    } // End of the function
    var cashPage = null;
    var rightMainData = null;
} // End of Class
