class com.mgame.webMall.main.topMain.PreviewItemXml
{
    function PreviewItemXml()
    {
    } // End of the function
    function viewStart(goodsno)
    {
        this.xmlLoad(goodsno, "WIN_OPEN");
    } // End of the function
    function viewClose()
    {
        com.mgame.webMall.main.MainData.__set__previewPageType(false);
        this.xmlLoad("", "WIN_CLOSE");
    } // End of the function
    function xmlLoad(goodsno, cmd)
    {
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        _loc2.onLoad = function ()
        {
        };
        var _loc1 = new LoadVars();
        _loc1.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc1.cmd = cmd;
        _loc1.obj = goodsno;
        _loc1.sendAndLoad(com.mgame.webMall.main.CommonDataUrl.__get__previewAndInvenURL(), _loc2, "post");
    } // End of the function
} // End of Class
