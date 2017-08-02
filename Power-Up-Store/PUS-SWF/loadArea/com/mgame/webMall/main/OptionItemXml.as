class com.mgame.webMall.main.OptionItemXml
{
    function OptionItemXml()
    {
    } // End of the function
    function load()
    {
        var _this = this;
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        _loc2.onLoad = function ()
        {
            _this.onLoad(this);
        };
        var _loc3 = new LoadVars();
        _loc3.cmd = "optionShop";
        _loc3.sendAndLoad(loadURL, _loc2, "post");
    } // End of the function
    function onLoad(xmlData)
    {
        var _loc6 = xmlData.firstChild.childNodes;
        var _loc5 = new Array();
        var _loc4 = new Array();
        this.deleteArrayData();
        for (var _loc2 = 0; _loc2 < _loc6.length; ++_loc2)
        {
            _loc5.push(_loc6[_loc2].firstChild.nextSibling);
        } // end of for
        for (var _loc2 = 0; _loc2 < _loc5.length; ++_loc2)
        {
            _loc4 = _loc5[_loc2].childNodes;
            for (var _loc3 = 0; _loc3 < _loc4.length; ++_loc3)
            {
                com.mgame.webMall.main.MainData["OPTION" + (_loc2 + 1) + "_category"].push(_loc4[_loc3].firstChild.nextSibling.firstChild.nodeValue);
                com.mgame.webMall.main.MainData["OPTION" + (_loc2 + 1) + "_id"].push(_loc4[_loc3].firstChild.nextSibling.nextSibling.firstChild.nodeValue);
                com.mgame.webMall.main.MainData["OPTION" + (_loc2 + 1) + "_name"].push(_loc4[_loc3].firstChild.nextSibling.nextSibling.nextSibling.firstChild.nodeValue);
                com.mgame.webMall.main.MainData["OPTION" + (_loc2 + 1) + "_price"].push(_loc4[_loc3].firstChild.nextSibling.nextSibling.nextSibling.nextSibling.firstChild.nodeValue);
            } // end of for
        } // end of for
    } // End of the function
    function deleteArrayData()
    {
        for (var _loc1 = 0; _loc1 < 4; ++_loc1)
        {
            com.mgame.webMall.main.MainData["OPTION" + (_loc1 + 1) + "_category"] = [];
            com.mgame.webMall.main.MainData["OPTION" + (_loc1 + 1) + "_id"] = [];
            com.mgame.webMall.main.MainData["OPTION" + (_loc1 + 1) + "_name"] = [];
            com.mgame.webMall.main.MainData["OPTION" + (_loc1 + 1) + "_price"] = [];
        } // end of for
    } // End of the function
    static var loadURL = com.mgame.webMall.main.CommonDataUrl.__get__optionItemURL();
} // End of Class
