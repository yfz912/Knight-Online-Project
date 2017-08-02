class com.mgame.webMall.page.commonStorePage.StorePageMakeType
{
    var gotoAndStop, idx;
    function StorePageMakeType()
    {
    } // End of the function
    function type(value, storePageData)
    {
        this.storePageData = storePageData;
        storePageXml = storePageData.__get__storePageLoad().getStorePageXml();
        if (aType == null)
        {
            aType = new com.mgame.webMall.page.commonStorePage.StorePageAtype();
        } // end if
        if (bType == null)
        {
            bType = new com.mgame.webMall.page.commonStorePage.StorePageBtype();
        } // end if
        if (cType == null)
        {
            cType = new com.mgame.webMall.page.commonStorePage.StorePageCtype();
        } // end if
        this.listTableTopType(value);
        this.topMakeTable();
        cType.clearTimer();
        if (value == "1")
        {
            bType.removeList();
            cType.removeList();
            aType.setData(storePageData);
        }
        else if (value == "2")
        {
            aType.removeList();
            cType.removeList();
            bType.setData(storePageData);
        }
        else if (value == "3")
        {
            aType.removeList();
            bType.removeList();
            cType.setData(storePageData);
        } // end else if
    } // End of the function
    function listTableTopType(type)
    {
        if (type == "1")
        {
            topTable.countSortSelect.countSortSelect.enabled = true;
            storePageData.__get__main().listTableTop.gotoAndStop(1);
        }
        else if (type == "2")
        {
            topTable.countSortSelect.countSortSelect.selectedIndex = 0;
            topTable.countSortSelect.countSortSelect.enabled = false;
            storePageData.__get__main().listTableTop.gotoAndStop(2);
        }
        else
        {
            topTable.countSortSelect.countSortSelect.enabled = true;
            storePageData.__get__main().listTableTop.gotoAndStop(3);
        } // end else if
    } // End of the function
    function topMakeTable()
    {
        if (storePageData.__get__movieClipMakeCheck() == false)
        {
            storePageData.__set__movieClipMakeCheck(true);
            topTable = storePageData.__get__main().topTable;
            this.selectBox(topTable);
            this.listViewBox(topTable);
        } // end if
    } // End of the function
    function selectBox(topTable)
    {
        var _this = this;
        var countSortSelect = topTable.countSortSelect.countSortSelect;
        var typeSortSelect = topTable.typeSortSelect.typeSortSelect;
        countSortSelect.addItem({label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_100(), data: "10"});
        countSortSelect.addItem({label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_101(), data: "10"});
        countSortSelect.addItem({label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_102(), data: "20"});
        countSortSelect.addItem({label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_103(), data: "30"});
        var _loc3 = new Object();
        _loc3.change = function (evt_obj)
        {
            _this.storePageData.listcount = countSortSelect.selectedItem.data;
            _this.storePageXml.sortTypeReload();
        };
        countSortSelect.addEventListener("change", _loc3);
        typeSortSelect.addItem({data: "id", label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_112()});
        typeSortSelect.addItem({data: "name", label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_113()});
        typeSortSelect.addItem({data: "rank", label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_114()});
        typeSortSelect.addItem({data: "priceHigh", label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_115()});
        typeSortSelect.addItem({data: "priceLow", label: com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageMakeType_116()});
        var _loc2 = new Object();
        _loc2.change = function (evt_obj)
        {
            _this.storePageXml.sortType = typeSortSelect.selectedItem.data;
            _this.storePageXml.sortTypeReload();
        };
        typeSortSelect.addEventListener("change", _loc2);
    } // End of the function
    function listViewBox(topTable)
    {
        var _this = this;
        topTable.listViewType["view0" + storePageData.__get__layoutType()].gotoAndStop(2);
        for (var _loc2 = 1; _loc2 <= 3; ++_loc2)
        {
            topTable.listViewType["view0" + _loc2].idx = _loc2;
            topTable.listViewType["view0" + _loc2].onRollOver = function ()
            {
                _this.mouseOverEvent();
                this.gotoAndStop(2);
            };
            topTable.listViewType["view0" + _loc2].onRollOut = function ()
            {
                _this.mouseOutEvent();
                this.gotoAndStop(1);
            };
            topTable.listViewType["view0" + _loc2].onRelease = function ()
            {
                _this.releaseEvnet(idx);
            };
        } // end of for
    } // End of the function
    function mouseOverEvent()
    {
        for (var _loc2 = 1; _loc2 <= 3; ++_loc2)
        {
            topTable.listViewType["view0" + _loc2].gotoAndStop(1);
        } // end of for
    } // End of the function
    function mouseOutEvent()
    {
        var _this = this;
        topTable.listViewType.bg.onRollOut = function ()
        {
            _this.topTable.listViewType["view0" + _this.storePageData.layoutType].gotoAndStop(2);
        };
    } // End of the function
    function releaseEvnet(idx)
    {
        var _loc2 = storePageData.__get__layoutType();
        storePageData.__set__layoutType(String(idx));
        storePageData.__set__listcount("10");
        storePageXml.reLoad(_loc2);
    } // End of the function
    var aType = null;
    var bType = null;
    var cType = null;
    var storePageData = null;
    var storePageXml = null;
    var topTable = null;
} // End of Class
