class com.mgame.webMall.main.rightMain.TodayItemXml
{
    function TodayItemXml()
    {
    } // End of the function
    function load(todayItemPage, rightMainData)
    {
        this.todayItemPage = todayItemPage;
        this.rightMainData = rightMainData;
        this.xmlLoad();
    } // End of the function
    function xmlLoad()
    {
        var _this = this;
        var xmlLoader = new XML();
        xmlLoader.ignoreWhite = true;
        xmlLoader.onLoad = function ()
        {
            var _loc2 = Number(xmlLoader.firstChild.firstChild.firstChild.nodeValue);
            if (_loc2)
            {
                _this.onLoad(this);
            }
            else
            {
                _this.rightMainData.rightMain.itemName_txt.text = com.mgame.webMall.text.MainPackageTextDefine.TodayItemXml_44;
                if (_this.rightMainData.rightMain.itemName_txt.maxscroll > 1)
                {
                    _this.rightMainData.rightMain.itemName_txt._y = 279;
                    _this.rightMainData.rightMain.itemName_txt._height = 40;
                } // end if
                trace ("xml load error");
            } // end else if
        };
        var _loc2 = new LoadVars();
        _loc2.cmd = "todayItems";
        _loc2.nowPage = "1";
        _loc2.listCount = "100";
        _loc2.sortType = "id";
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        var _loc5 = SharedObject.getLocal("mgame_today");
        var _loc3 = com.mgame.webMall.main.MainData.__get__todayItemCookie().data.idx;
        _loc3 = _loc3.substr(0, _loc3.length - 1);
        if (_loc3 == undefined)
        {
            _loc3 = "";
        } // end if
        _loc2.todayItems = _loc3;
        _loc2.sendAndLoad(loadURL, xmlLoader, "post");
    } // End of the function
    function onLoad(xmlData)
    {
        var _loc2 = xmlData.firstChild.childNodes;
        var _loc3 = _loc2[6].childNodes;
        rightMainData.__set__todayItemTotalCount(_loc2[3].firstChild.nodeValue);
        rightMainData.__set__todayItemData(_loc3);
        todayItemPage.init();
    } // End of the function
    var todayItemPage = null;
    var rightMainData = null;
    static var loadURL = com.mgame.webMall.main.CommonDataUrl.__get__todayItemPageURL();
} // End of Class
