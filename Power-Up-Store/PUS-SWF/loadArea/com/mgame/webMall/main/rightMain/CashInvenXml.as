class com.mgame.webMall.main.rightMain.CashInvenXml
{
    function CashInvenXml()
    {
    } // End of the function
    function load(rightMenu)
    {
        this.rightMenu = rightMenu;
        var _this = this;
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        var _loc3 = new LoadVars();
        _loc2.onLoad = function ()
        {
            _this.onLoad(this);
        };
        _loc3.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc3.cmd = "CASH_INVEN_CHECK";
        _loc3.sendAndLoad(invenCheckURL, _loc2, "post");
    } // End of the function
    function onLoad(xmlData)
    {
        var _loc5 = xmlData.firstChild.childNodes[1];
        _loc5 = xmlData.firstChild.childNodes[1];
        var _loc2 = _loc5.childNodes;
        var _loc3 = Number(_loc2[1].firstChild.firstChild.nodeValue);
        var _loc4 = Number(_loc2[1].firstChild.nextSibling.nextSibling.nextSibling.firstChild.nodeValue);
        var _loc6 = Number(_loc2[1].firstChild.nextSibling.nextSibling.nextSibling.nextSibling.firstChild.nodeValue);
        if (_loc3 < 0)
        {
            this.xmlLoadError();
        }
        else
        {
            this.invenCheck(_loc4, _loc6);
        } // end else if
    } // End of the function
    function invenCheck(totalInven, inven)
    {
        if (inven < totalInven)
        {
            rightMenu.cashInvenButtonStyle("flashMode");
        }
        else
        {
            rightMenu.cashInvenButtonStyle("default");
        } // end else if
    } // End of the function
    function xmlLoadError()
    {
        trace ("cashInven load error");
    } // End of the function
    var rightMenu = null;
    static var invenCheckURL = com.mgame.webMall.main.CommonDataUrl.__get__previewAndInvenURL();
} // End of Class
