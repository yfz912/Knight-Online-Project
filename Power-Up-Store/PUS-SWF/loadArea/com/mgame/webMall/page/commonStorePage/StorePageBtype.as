class com.mgame.webMall.page.commonStorePage.StorePageBtype
{
    var _parent, index;
    function StorePageBtype()
    {
    } // End of the function
    function setData(storePageData)
    {
        thisPageData = storePageData;
        storePageXml = storePageData.__get__storePageLoad().getStorePageXml();
        returnXmlData = new com.mgame.webMall.util.ReturnXmlData();
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        previewItemXml = new com.mgame.webMall.main.topMain.PreviewItemXml();
        this.listTableDefine();
    } // End of the function
    function listTableDefine()
    {
        listCount = thisPageData.__get__itemArr().length;
        thisPageData.__set__listTableTop(thisPageData.__get__main().listTableTop);
        if (listCount == 0)
        {
            this.makeDefaultListTable();
        }
        else
        {
            this.stageCheck();
        } // end else if
    } // End of the function
    function removeList()
    {
        for (var _loc2 = 1; _loc2 <= 20; ++_loc2)
        {
            thisPageData.__get__main()["listTable_Btype" + _loc2].removeMovieClip();
        } // end of for
        thisPageData.__get__main().pageMain.removeMovieClip();
        thisPageData.__get__main().listPrevButton.removeMovieClip();
        thisPageData.__get__main().listNextButton.removeMovieClip();
        thisPageData.__get__main().listTableBottom.removeMovieClip();
    } // End of the function
    function stageCheck()
    {
        if (thisPageData.__get__main().listTable_Btype1 != undefined)
        {
            for (var _loc2 = 1; _loc2 <= 20; ++_loc2)
            {
                thisPageData.__get__main()["listTable_Btype" + _loc2].removeMovieClip();
            } // end of for
            thisPageData.__get__main().pageMain.removeMovieClip();
            thisPageData.__get__main().listPrevButton.removeMovieClip();
            thisPageData.__get__main().listNextButton.removeMovieClip();
            thisPageData.__get__main().listTableBottom.removeMovieClip();
            this.makeListTable();
        }
        else
        {
            this.makeListTable();
        } // end else if
    } // End of the function
    function makeDefaultListTable()
    {
        var _loc3 = 0;
        var _loc2 = 0;
        _loc3 = thisPageData.__get__listTableTop()._x;
        _loc2 = thisPageData.__get__listTableTop()._y + thisPageData.__get__listTableTop()._height + 1;
        thisPageData.__get__main().attachMovie("defaultListTable", "defaultListTable", thisPageData.__get__main().getNextHighestDepth(), {_x: _loc3, _y: _loc2});
    } // End of the function
    function makeListTable()
    {
        var _this = this;
        var _loc5 = 0;
        var _loc3 = 0;
        var _loc4 = null;
        for (var _loc2 = 1; _loc2 <= listCount; ++_loc2)
        {
            if (_loc2 <= 10)
            {
                _loc5 = thisPageData.__get__listTableTop()._x;
                if (_loc2 == 1)
                {
                    _loc3 = thisPageData.__get__listTableTop()._y + thisPageData.__get__listTableTop()._height + 1;
                }
                else
                {
                    _loc3 = thisPageData.__get__main()["listTable_Btype" + (_loc2 - 1)]._y + thisPageData.__get__main()["listTable_Btype" + (_loc2 - 1)]._height + 1;
                } // end else if
            }
            else
            {
                _loc5 = 348;
                if (_loc2 == 11)
                {
                    _loc3 = thisPageData.__get__listTableTop()._y + thisPageData.__get__listTableTop()._height + 1;
                }
                else
                {
                    _loc3 = thisPageData.__get__main()["listTable_Btype" + (_loc2 - 1)]._y + thisPageData.__get__main()["listTable_Btype" + (_loc2 - 1)]._height + 1;
                } // end else if
            } // end else if
            _loc4 = thisPageData.__get__main().attachMovie("listTable_Btype", "listTable_Btype" + _loc2, thisPageData.__get__main().getNextHighestDepth(), {_x: _loc5, _y: _loc3});
            _loc4.index = _loc2;
            _loc4.selectArea.onRelease = function ()
            {
                com.mgame.webMall.util.CommonPopup.popupStart("detail", _this.returnXmlData.setArrayData(_this.thisPageData.itemArr, _parent.index - 1, "normalShop"));
            };
            this.setTextInfoData(_loc4, _loc2);
        } // end of for
        this.buttonEvent();
        this.makePageListNumber(20);
    } // End of the function
    function buttonEvent()
    {
        var _this = this;
        thisPageData.__get__main().topTable.multiBuyButton.onRelease = function ()
        {
            _this.jsCall_multi_viewItem();
        };
        thisPageData.__get__main().topTable.multiCartButton.onRelease = function ()
        {
            _this.jsCall_multi_basketIn();
        };
        thisPageData.__get__main().topTable.multiCancelButton.onRelease = function ()
        {
            _this.checkCancel();
        };
    } // End of the function
    function setTextInfoData(target, index)
    {
        var _loc13 = thisPageData.__get__itemImageURL();
        var _loc4 = returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").subicon;
        var _loc9 = 32;
        var _loc12 = 32;
        var _loc5 = returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").limit_age;
        if (_loc4 == "")
        {
            target.subImageBox._visible = false;
        }
        else
        {
            _loc4 = _loc13 + _loc4;
            this.itemImageLoad(target.subImageBox, _loc4, _loc9, _loc12);
        } // end else if
        var _loc6 = target.imageBox._x + target.imageBox._width + 15;
        var _loc7 = target.name_txt._y;
        target.attachMovie("limit_age" + _loc5, "limit_age" + _loc5, thisPageData.__get__main().getNextHighestDepth(), {_x: _loc6, _y: _loc7});
        target.name_txt.text = returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").name;
        if (returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").item_type == "1")
        {
            target.money_txt.text = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageBtype_188;
        }
        else if (returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").limit_type != "0")
        {
            target.money_txt.html = true;
            target.money_txt.htmlText = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageBtype_194;
        }
        else
        {
            target.money_txt.text = numberSplit.split(returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").dc) + com.mgame.webMall.util.ReturnPriceType.getDtypeData(returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").dtype);
        } // end else if
        var _loc8 = 32;
        var _loc10 = 32;
        var _loc11 = thisPageData.__get__itemImageURL() + returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").smallimage;
        this.itemImageLoad(target.imageBox, _loc11, _loc8, _loc10);
    } // End of the function
    function itemImageLoad(targetMovieClip, imageURL, imageWidth, imageHeight)
    {
        var _loc1 = new Object();
        var _loc2 = new MovieClipLoader();
        _loc2.addListener(_loc1);
        _loc2.loadClip(imageURL, targetMovieClip);
        _loc1.onLoadInit = function (target)
        {
            target._width = imageWidth;
            target._height = imageHeight;
        };
        _loc1.onLoadError = function (target_mc, errorCode, httpStatus)
        {
            trace ("itemImageLoadError");
        };
    } // End of the function
    function makePageListNumber(blockSize)
    {
        var _this = this;
        var _loc8 = Number(thisPageData.__get__totalcount());
        var recordSize = Number(thisPageData.__get__totalpage());
        blockSize = 10;
        var currentPage = Number(thisPageData.__get__nowpage());
        var _loc3 = currentPage - (currentPage - 1) % blockSize;
        var _loc4 = _loc3 + 9;
        var _loc7 = 515;
        thisPageData.__get__main().attachMovie("pageMain", "pageMain", thisPageData.__get__main().getNextHighestDepth());
        thisPageData.__get__main().pageMain._y = _loc7;
        thisPageData.__get__main().pageMain.attachMovie("listPrevButton", "listPrevButton", thisPageData.__get__main().pageMain.getNextHighestDepth());
        for (var _loc2 = _loc3; _loc2 <= _loc4; ++_loc2)
        {
            thisPageData.__get__main().pageMain.attachMovie("pageNumber", "pageNumber" + _loc2, thisPageData.__get__main().pageMain.getNextHighestDepth());
            thisPageData.__get__main().pageMain["pageNumber" + _loc2].number_txt.text = _loc2;
            thisPageData.__get__main().pageMain["pageNumber" + _loc2]._width = thisPageData.__get__main().pageMain["pageNumber" + _loc2].number_txt.textWidth + 2;
            if (thisPageData.__get__main().pageMain["pageNumber" + (_loc2 - 1)] == undefined)
            {
                thisPageData.__get__main().pageMain["pageNumber" + _loc2]._x = thisPageData.__get__main().pageMain.listPrevButton._x + thisPageData.__get__main().pageMain.listPrevButton._width + 6;
            }
            else
            {
                thisPageData.__get__main().pageMain["pageNumber" + _loc2]._x = thisPageData.__get__main().pageMain["pageNumber" + (_loc2 - 1)]._x + thisPageData.__get__main().pageMain["pageNumber" + (_loc2 - 1)]._width + 2;
            } // end else if
            thisPageData.__get__main().pageMain["pageNumber" + _loc2].index = _loc2;
            thisPageData.__get__main().pageMain["pageNumber" + _loc2].onRelease = function ()
            {
                _this.thisPageData.listcount = "10";
                _this.storePageXml.pageReload(index);
            };
            if (_loc2 == currentPage)
            {
                thisPageData.__get__main().pageMain["pageNumber" + _loc2].number_txt.textColor = "0xFFFFFF";
            } // end if
            if (_loc2 == recordSize)
            {
                ++_loc2;
                break;
            } // end if
        } // end of for
        var _loc5 = 6;
        thisPageData.__get__main().pageMain.attachMovie("listNextButton", "listNextButton", thisPageData.__get__main().pageMain.getNextHighestDepth());
        if (thisPageData.__get__main().pageMain["pageNumber" + (_loc2 - 1)] == undefined)
        {
            thisPageData.__get__main().pageMain.listNextButton._x = thisPageData.__get__main().pageMain["pageNumber" + _loc2]._x + thisPageData.__get__main().pageMain["pageNumber" + _loc2]._width + _loc5;
        }
        else
        {
            thisPageData.__get__main().pageMain.listNextButton._x = thisPageData.__get__main().pageMain["pageNumber" + (_loc2 - 1)]._x + thisPageData.__get__main().pageMain["pageNumber" + (_loc2 - 1)]._width + _loc5;
        } // end else if
        thisPageData.__get__main().pageMain.listPrevButton.onRelease = function ()
        {
            _this.thisPageData.listcount = "10";
            if (currentPage - 1 > 0)
            {
                _this.storePageXml.pageReload(currentPage - 1);
            } // end if
        };
        thisPageData.__get__main().pageMain.listNextButton.onRelease = function ()
        {
            _this.thisPageData.listcount = "10";
            if (currentPage + 1 <= recordSize)
            {
                _this.storePageXml.pageReload(currentPage + 1);
            } // end if
        };
        thisPageData.__get__main().pageMain._x = thisPageData.__get__main()._width / 2 - thisPageData.__get__main().pageMain._width / 2;
    } // End of the function
    function jsCall_multi_viewItem()
    {
        var _loc3 = new Array();
        for (var _loc2 = 1; _loc2 <= listCount; ++_loc2)
        {
            if (thisPageData.__get__main()["listTable_Btype" + _loc2].checkBox.checkBox.selected)
            {
                _loc3.push(returnXmlData.setArrayData(thisPageData.__get__itemArr(), _loc2 - 1, "normalShop"));
            } // end if
        } // end of for
        com.mgame.webMall.util.CommonPopup.popupStart("buy_select", _loc3);
    } // End of the function
    function jsCall_multi_basketIn()
    {
        var _loc3 = new Array();
        for (var _loc2 = 1; _loc2 <= listCount; ++_loc2)
        {
            if (thisPageData.__get__main()["listTable_Btype" + _loc2].checkBox.checkBox.selected)
            {
                _loc3.push(returnXmlData.setArrayData(thisPageData.__get__itemArr(), _loc2 - 1, "normalShop"));
            } // end if
        } // end of for
        com.mgame.webMall.util.CommonPopup.popupStart("basket", _loc3);
    } // End of the function
    function checkCancel()
    {
        for (var _loc2 = 1; _loc2 <= listCount; ++_loc2)
        {
            thisPageData.__get__main()["listTable_Btype" + _loc2].checkBox.checkBox.selected = false;
        } // end of for
    } // End of the function
    function previewCheck(dataObj)
    {
        if (com.mgame.webMall.main.MainData.__get__previewPageType() == true)
        {
            previewItemXml.viewStart(dataObj.goodsno);
        } // end if
    } // End of the function
    var thisPageData = null;
    var storePageXml = null;
    var returnXmlData = null;
    var numberSplit = null;
    var previewItemXml = null;
    var listCount = 0;
} // End of Class
