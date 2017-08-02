class com.mgame.webMall.page.commonStorePage.StorePageXml
{
    var __get__sortType, __set__sortType;
    function StorePageXml()
    {
    } // End of the function
    function load(storePageLoad, storePageData)
    {
        this.storePageLoad = storePageLoad;
        this.storePageData = storePageData;
        this.xmlLoad();
    } // End of the function
    function reLoad(tempLayoutType)
    {
        if (tempLayoutType == storePageData.__get__layoutType())
        {
            this.callMain();
        }
        else if (tempLayoutType == "2")
        {
            this.xmlLoad();
        }
        else if (storePageData.__get__layoutType() == "2")
        {
            this.xmlLoad();
        }
        else
        {
            this.callMain();
        } // end else if
    } // End of the function
    function sortTypeReload()
    {
        if (storePageData.__get__layoutType() == "2")
        {
            storePageData.__set__listcount("10");
        } // end if
        this.xmlLoad("1");
    } // End of the function
    function pageReload(pageNumber)
    {
        this.pageNumber = String(pageNumber);
        this.xmlLoad(this.pageNumber);
    } // End of the function
    function xmlLoad(pageNumber)
    {
        var _this = this;
        if (pageNumber == undefined)
        {
            pageNumber = "1";
        } // end if
        this.pageNumber = pageNumber;
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
                trace ("xml load error");
                _this.storePageData.main.attachMovie("noData", "noData", _this.storePageData.main.getNextHighestDepth(), {_x: 240, _y: 270});
                com.mgame.webMall.main.MainLoad.getMainData().__get__mainStage().mainClose._alpha = 0;
                com.mgame.webMall.main.MainLoad.getMainData().__get__mainStage().mainClose._visible = false;
            } // end else if
        };
        var _loc2 = new LoadVars();
        if (com.mgame.webMall.main.MainData.__get__PARAMETER_cmd() == null)
        {
            _loc2.cmd = "normalShop";
        }
        else
        {
            _loc2.cmd = com.mgame.webMall.main.MainData.PARAMETER_cmd;
        } // end else if
        _loc2.shopNum = com.mgame.webMall.main.MainData.PARAMETER_shopNum;
        _loc2.layoutType = storePageData.layoutType;
        _loc2.nowPage = pageNumber;
        _loc2.listCount = storePageData.listcount;
        _loc2.sortType = sortType;
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.sendAndLoad(loadURL, xmlLoader, "POST");
    } // End of the function
    function onLoad(xmlData)
    {
        var _loc2 = xmlData.firstChild.childNodes;
        storePageData.__set__listcount(_loc2[1].firstChild.nodeValue);
        storePageData.__set__totalcount(_loc2[2].firstChild.nodeValue);
        storePageData.__set__nowpage(_loc2[3].firstChild.nodeValue);
        storePageData.__set__totalpage(_loc2[4].firstChild.nodeValue);
        var _loc3 = _loc2[5].childNodes;
        this.saveData(_loc3);
    } // End of the function
    function saveData(data)
    {
        storePageData.__set__itemArr(data);
        this.callMain();
    } // End of the function
    function callMain()
    {
        storePageLoad.init();
    } // End of the function
    function get sortType()
    {
        return (_sortType);
    } // End of the function
    function set sortType(value)
    {
        _sortType = value;
        //return (this.sortType());
        null;
    } // End of the function
    var storePageData = null;
    var storePageLoad = null;
    var loadURL = com.mgame.webMall.main.CommonDataUrl.__get__commonStorePageURL();
    var _sortType = "id";
    var pageNumber = null;
} // End of Class
