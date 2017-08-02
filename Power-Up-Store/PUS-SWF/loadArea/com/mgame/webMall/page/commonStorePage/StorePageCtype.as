class com.mgame.webMall.page.commonStorePage.StorePageCtype
{
    var _parent, index;
    function StorePageCtype()
    {
    } // End of the function
    function setData(storePageData)
    {
        thisPageData = storePageData;
        storePageXml = storePageData.__get__storePageLoad().getStorePageXml();
        com.mgame.webMall.main.MainData.__set__storePageCtype(this);
        returnXmlData = new com.mgame.webMall.util.ReturnXmlData();
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        previewItemXml = new com.mgame.webMall.main.topMain.PreviewItemXml();
        this.listTableDefine();
    } // End of the function
    function listTableDefine()
    {
        listCount = thisPageData.__get__itemArr().length;
        thisPageData.__set__listTableTop(thisPageData.__get__main().listTableTop);
        thisPageData.__get__mainStage().mainBgMovieClip.useHandCursor = false;
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
        for (var _loc2 = 1; _loc2 <= 30; ++_loc2)
        {
            thisPageData.__get__main()["listTable_Ctype" + _loc2].removeMovieClip();
        } // end of for
        thisPageData.__get__main().pageMain.removeMovieClip();
        thisPageData.__get__main().listPrevButton.removeMovieClip();
        thisPageData.__get__main().listNextButton.removeMovieClip();
        thisPageData.__get__main().listTableBottom.removeMovieClip();
        thisPageData.__get__main().detail_content.removeMovieClip();
        thisPageData.__get__main().scrollbar.removeMovieClip();
        thisPageData.__get__main().detail_content.scrollbar.removeMovieClip();
        thisPageData.__get__main().listTable_Ctype_mask.removeMovieClip();
        thisPageData.__get__main().listTable_Ctype_main.removeMovieClip();
    } // End of the function
    function stageCheck()
    {
        if (thisPageData.__get__main().listTable_Ctype_main.listTable_Ctype1 != undefined)
        {
            for (var _loc2 = 1; _loc2 <= 30; ++_loc2)
            {
                thisPageData.__get__main()["listTable_Ctype" + _loc2].removeMovieClip();
            } // end of for
            thisPageData.__get__main().pageMain.removeMovieClip();
            thisPageData.__get__main().listPrevButton.removeMovieClip();
            thisPageData.__get__main().listNextButton.removeMovieClip();
            thisPageData.__get__main().listTableBottom.removeMovieClip();
            thisPageData.__get__main().detail_content.removeMovieClip();
            thisPageData.__get__main().scrollbar.removeMovieClip();
            thisPageData.__get__main().detail_content.scrollbar.removeMovieClip();
            thisPageData.__get__main().listTable_Ctype_mask.removeMovieClip();
            thisPageData.__get__main().listTable_Ctype_main.removeMovieClip();
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
        var _loc4 = 0;
        var _loc3 = null;
        thisPageData.__get__listTableTop()._y = 32;
        thisPageData.__get__main().attachMovie("listTable_Ctype_main", "listTable_Ctype_main", thisPageData.__get__main().getNextHighestDepth(), {_x: 0, _y: 0});
        for (var _loc2 = 1; _loc2 <= listCount; ++_loc2)
        {
            _loc5 = thisPageData.__get__listTableTop()._x;
            if (_loc2 == 1)
            {
                _loc4 = thisPageData.__get__listTableTop()._y + thisPageData.__get__listTableTop()._height + 1;
            }
            else
            {
                _loc4 = thisPageData.__get__main().listTable_Ctype_main["listTable_Ctype" + (_loc2 - 1)]._y + thisPageData.__get__main().listTable_Ctype_main["listTable_Ctype" + (_loc2 - 1)]._height + 1;
            } // end else if
            _loc3 = thisPageData.__get__main().listTable_Ctype_main.attachMovie("listTable_Ctype", "listTable_Ctype" + _loc2, thisPageData.__get__main().listTable_Ctype_main.getNextHighestDepth(), {_x: _loc5, _y: _loc4});
            _loc3.idx = _loc2;
            _loc3.selectArea.onRelease = function ()
            {
                _this.detailSetInfo(_parent.idx);
            };
            _loc3.selectArea.onRollOver = function ()
            {
                _this.scrollBar.setMouseWheelEvent(_this.thisPageData.main.listTable_Ctype_main);
            };
            this.setTextInfoData(_loc3, _loc2);
        } // end of for
        this.detailViewLoad();
        this.detailSetInfo(1);
        this.detailAreaScroll();
        this.buttonEvent();
        this.makePageListNumber(Number(thisPageData.__get__listcount()));
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
            target.money_txt.text = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageCtype_199;
        }
        else if (returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").limit_type != "0")
        {
            target.money_txt.html = true;
            target.money_txt.htmlText = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageCtype_205;
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
    function detailViewLoad()
    {
        var _loc3 = 387;
        var _loc2 = thisPageData.__get__main().listTableTop._y;
        thisPageData.__get__main().attachMovie("detail_content", "detail_content", thisPageData.__get__main().getNextHighestDepth(), {_x: _loc3, _y: _loc2});
    } // End of the function
    function detailContentScrollbarMake()
    {
        var _loc2 = 0;
        var _loc5 = 15;
        var _loc4 = 0;
        var _loc3 = 0;
        thisPageData.__get__main().detail_content.scrollbar.removeMovieClip();
        thisPageData.__get__main().detail_content.detailContentMask.removeMovieClip();
        if (thisPageData.__get__main().detail_content._currentframe == 1)
        {
            _loc2 = 242;
            _loc3 = 175;
            _loc4 = 210;
        }
        else
        {
            _loc2 = 268;
            _loc3 = 145;
            _loc4 = 236;
        } // end else if
        if (_loc2 < thisPageData.__get__main().detail_content.contentMovieClip._height)
        {
            this.contentScrollbarMakeStart(_loc2, _loc5, _loc4, _loc3);
        } // end if
    } // End of the function
    function contentScrollbarMakeStart(scrollOriginHeight, scrollOriginY, scrollbarOriginHeight, contentAreaOriginY)
    {
        var _this = this;
        if (thisPageData.__get__main().detail_content.scrollbar == undefined)
        {
            thisPageData.__get__main().detail_content.attachMovie("scrollbar", "scrollbar", thisPageData.__get__main().detail_content.getNextHighestDepth());
        } // end if
        if (thisPageData.__get__main().detail_content.detailContentMask == undefined)
        {
            thisPageData.__get__main().detail_content.attachMovie("detailContentMask", "detailContentMask", thisPageData.__get__main().detail_content.getNextHighestDepth());
        } // end if
        thisPageData.__get__main().detail_content.detailContentMask._x = thisPageData.__get__main().detail_content.contentMovieClip._x;
        thisPageData.__get__main().detail_content.detailContentMask._y = thisPageData.__get__main().detail_content.contentMovieClip._y;
        thisPageData.__get__main().detail_content.detailContentMask._width = thisPageData.__get__main().detail_content.contentMovieClip._width;
        thisPageData.__get__main().detail_content.detailContentMask._height = scrollOriginHeight;
        thisPageData.__get__main().detail_content.contentMovieClip.setMask(thisPageData.__get__main().detail_content.detailContentMask);
        thisPageData.__get__main().detail_content.scrollbar._x = 252;
        thisPageData.__get__main().detail_content.scrollbar._y = thisPageData.__get__main().detail_content.detailContentMask._y;
        thisPageData.__get__main().detail_content.scrollbar.bar._height = scrollOriginHeight - 32;
        thisPageData.__get__main().detail_content.scrollbar.bg._height = scrollOriginHeight - 2;
        thisPageData.__get__main().detail_content.scrollbar.scrollDownButton._y = scrollOriginHeight - 16;
        if (detailContentScrollBar == null)
        {
            detailContentScrollBar = new com.mgame.webMall.util.ScrollBar();
        } // end if
        thisPageData.__get__main().detail_content.contentMovieClip.useHandCursor = false;
        thisPageData.__get__main().detail_content.contentMovieClip.onRelease = function ()
        {
            _this.detailContentScrollBar.setMouseWheelEvent(_this.thisPageData.main.detail_content.contentMovieClip);
        };
        thisPageData.__get__mainStage().mainBgMovieClip.onRelease = function ()
        {
            _this.scrollBar.setMouseWheelEvent(_this.thisPageData.main.listTable_Ctype_main);
        };
        var _loc5 = contentAreaOriginY;
        var _loc3 = scrollOriginY;
        var _loc4 = scrollbarOriginHeight;
        detailContentScrollBar.setScrollTarget(thisPageData.__get__main().detail_content.contentMovieClip);
        detailContentScrollBar.setScrollUpButton(thisPageData.__get__main().detail_content.scrollbar.scrollUpButton);
        detailContentScrollBar.setScrollDownButton(thisPageData.__get__main().detail_content.scrollbar.scrollDownButton);
        detailContentScrollBar.setScrollBar(thisPageData.__get__main().detail_content.scrollbar.bar);
        detailContentScrollBar.setMouseWheelStyle(true);
        detailContentScrollBar.start(thisPageData.__get__main().detail_content.detailContentMask._height + 1, _loc5, _loc3, _loc4);
    } // End of the function
    function detailSetInfo(index)
    {
        var _this = this;
        var _loc8 = thisPageData.__get__itemImageURL();
        var _loc3 = returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").bigimage;
        _loc3 = _loc8 + _loc3;
        var _loc5 = 64;
        var _loc7 = 64;
        var _loc6 = returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").name;
        this.countStrType(returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop"), thisPageData.__get__main().detail_content);
        var _loc2 = null;
        if (returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").item_type == "1")
        {
            _loc2 = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageCtype_332;
        }
        else
        {
            _loc2 = numberSplit.split(returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").dc) + com.mgame.webMall.util.ReturnPriceType.getDtypeData(returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").dtype);
        } // end else if
        var _loc4 = com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_342() + returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").explain1 + "</font>";
        _loc4 = _loc4 + (com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_343() + returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").explain2 + "</font>");
        thisPageData.__get__main().detail_content.contentMovieClip.content_txt.html = true;
        thisPageData.__get__main().detail_content.contentMovieClip.content_txt.multiline = true;
        thisPageData.__get__main().detail_content.contentMovieClip.content_txt.wordWrap = true;
        thisPageData.__get__main().detail_content.title_txt.text = _loc6;
        thisPageData.__get__main().detail_content.money_txt.text = _loc2;
        thisPageData.__get__main().detail_content.contentMovieClip.content_txt.autoSize = true;
        thisPageData.__get__main().detail_content.contentMovieClip.content_txt.htmlText = _loc4;
        if (thisPageData.__get__main().detail_content._currentframe == 1)
        {
            thisPageData.__get__main().detail_content.contentMovieClip._y = 175;
        }
        else
        {
            thisPageData.__get__main().detail_content.contentMovieClip._y = 145;
        } // end else if
        thisPageData.__get__main().detail_content.contentMovieClip.content_txt._height = thisPageData.__get__main().detail_content.contentMovieClip.content_txt.textHeight;
        if (returnXmlData.setArrayData(thisPageData.__get__itemArr(), index - 1, "normalShop").char_sex != "0")
        {
            thisPageData.__get__main().detail_content.previewButton._visible = true;
        }
        else
        {
            thisPageData.__get__main().detail_content.previewButton._visible = false;
        } // end else if
        thisPageData.__get__main().detail_content.buyButton.onRelease = function ()
        {
            if (_this.itemDateChech == false)
            {
                com.mgame.webMall.util.CommonPopup.alert(com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_380());
            }
            else
            {
                com.mgame.webMall.util.CommonPopup.popupStart("buy_normal", _this.returnXmlData.setArrayData(_this.thisPageData.itemArr, index - 1, "normalShop"));
                _this.clearTimer();
            } // end else if
        };
        thisPageData.__get__main().detail_content.cartButton.onRelease = function ()
        {
            com.mgame.webMall.util.CommonPopup.popupStart("basket", _this.returnXmlData.setArrayData(_this.thisPageData.itemArr, index - 1, "normalShop"));
            _this.clearTimer();
        };
        thisPageData.__get__main().detail_content.requestButton.onRelease = function ()
        {
            trace ("쪼르기");
            com.mgame.webMall.util.CommonPopup.popupStart("jorgi_normal", _this.returnXmlData.setArrayData(_this.thisPageData.itemArr, index - 1, "normalShop"));
            _this.clearTimer();
        };
        thisPageData.__get__main().detail_content.giftButton.onRelease = function ()
        {
            trace ("선물");
            if (_this.itemDateChech == false)
            {
                com.mgame.webMall.util.CommonPopup.alert(com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_407());
            }
            else
            {
                com.mgame.webMall.util.CommonPopup.popupStart("gift_normal", _this.returnXmlData.setArrayData(_this.thisPageData.itemArr, index - 1, "normalShop"));
                _this.clearTimer();
            } // end else if
        };
        thisPageData.__get__main().detail_content.previewButton.onRelease = function ()
        {
            trace ("미리보기");
        };
        this.itemImageLoad(thisPageData.__get__main().detail_content.itemImage, _loc3, _loc5, _loc7);
        this.detailContentScrollbarMake();
    } // End of the function
    function countStrType(obj, target)
    {
        var _loc2 = obj;
        var _loc3 = null;
        if (String(_loc2.limit_type) == "0")
        {
            this.clearTimer();
            _loc3 = "";
            thisPageData.__get__main().detail_content.gotoAndStop(2);
        }
        else if (String(_loc2.limit_type) == "1")
        {
            this.clearTimer();
            thisPageData.__get__main().detail_content.gotoAndStop(1);
            thisPageData.__get__main().detail_content.countName_txt._x = 102;
            thisPageData.__get__main().detail_content.countName_txt._y = 120;
            thisPageData.__get__main().detail_content.countName_txt._width = 65;
            thisPageData.__get__main().detail_content.countName_txt._height = 18;
            thisPageData.__get__main().detail_content.count_txt._x = 140;
            thisPageData.__get__main().detail_content.count_txt._y = 119;
            thisPageData.__get__main().detail_content.count_txt._width = 103;
            thisPageData.__get__main().detail_content.count_txt._height = 48;
            thisPageData.__get__main().detail_content.countName_txt.text = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageCtype_447;
            _loc3 = String(_loc2.limit_remain) + " / " + String(_loc2.limit_total);
            thisPageData.__get__main().detail_content.count_txt.text = _loc3;
        }
        else if (String(_loc2.limit_type) == "2")
        {
            this.clearTimer();
            thisPageData.__get__main().detail_content.gotoAndStop(1);
            thisPageData.__get__main().detail_content.countName_txt._x = 20;
            thisPageData.__get__main().detail_content.countName_txt._width = 65;
            thisPageData.__get__main().detail_content.countName_txt._height = 18;
            thisPageData.__get__main().detail_content.count_txt._x = 75;
            thisPageData.__get__main().detail_content.count_txt._y = 134;
            thisPageData.__get__main().detail_content.count_txt._width = 220;
            thisPageData.__get__main().detail_content.count_txt._height = 36;
            thisPageData.__get__main().detail_content.countName_txt.text = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageCtype_462;
            _loc3 = String(_loc2.limit_sdate) + " ~ " + String(_loc2.limit_edate);
            this.limitTime(_loc2.limit_sdate, _loc2.limit_edate, "", "", target, _loc2.limit_type);
        }
        else
        {
            this.clearTimer();
            thisPageData.__get__main().detail_content.gotoAndStop(1);
            thisPageData.__get__main().detail_content.countName_txt._x = 20;
            thisPageData.__get__main().detail_content.countName_txt._y = 125;
            thisPageData.__get__main().detail_content.countName_txt._width = 65;
            thisPageData.__get__main().detail_content.countName_txt._height = 36;
            thisPageData.__get__main().detail_content.count_txt._x = 75;
            thisPageData.__get__main().detail_content.count_txt._y = 124;
            thisPageData.__get__main().detail_content.count_txt._width = 220;
            thisPageData.__get__main().detail_content.count_txt._height = 36;
            thisPageData.__get__main().detail_content.countName_txt.text = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageCtype_477;
            _loc3 = String(_loc2.limit_remain) + " / " + String(_loc2.limit_total) + "\n" + String(_loc2.limit_sdate) + " ~ " + String(_loc2.limit_edate);
            this.limitTime(_loc2.limit_sdate, _loc2.limit_edate, _loc2.limit_remain, _loc2.limit_total, target, _loc2.limit_type);
        } // end else if
    } // End of the function
    function limitTime(sdate, edate, limit_remain, limit_total, target, limit_type)
    {
        var _loc4 = sdate.split("-");
        var _loc2 = edate.split("-");
        var _loc17 = Number(String(_loc4[2]).split(" ")[0]);
        var _loc18 = Number(String(_loc2[2]).split(" ")[0]);
        var _loc19 = String(_loc4[2]).split(" ")[1];
        var _loc5 = _loc19.split(":");
        var _loc15 = String(_loc2[2]).split(" ")[1];
        var _loc8 = _loc15.split(":");
        var _loc9 = new Date();
        var _loc14 = new Date(_loc4[0], Number(_loc4[1] - 1), _loc17, _loc5[0], _loc5[1], _loc5[2]);
        var _loc16 = new Date(_loc2[0], Number(_loc2[1] - 1), _loc18, _loc8[0], _loc8[1], _loc8[2]);
        if (_loc14.getTime() > _loc9.getTime())
        {
            itemDateChech = false;
            target.count_txt.text = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageCtype_503;
            return;
        }
        else
        {
            itemDateChech = true;
        } // end else if
        var _loc3 = _loc16 - _loc9;
        _loc3 = _loc3 / 1000;
        var _loc10 = null;
        var _loc7 = null;
        var _loc13 = null;
        var _loc6 = null;
        var _loc12 = null;
        var _loc11 = null;
        _loc10 = Math.floor(_loc3 / 86400);
        _loc7 = _loc3 % 86400;
        _loc13 = Math.floor(_loc7 / 3600);
        _loc6 = _loc7 % 3600;
        _loc12 = Math.floor(_loc6 / 60);
        _loc11 = Math.floor(_loc6 % 60);
        this.timer(_loc10, _loc13, _loc12, _loc11, target, limit_type, limit_remain, limit_total);
    } // End of the function
    function timer(day, hour, min, sec, target, limit_type, limit_remain, limit_total)
    {
        clearInterval(timerNum);
        if (sec <= 0 && min <= 0 && hour <= 0 && day <= 0)
        {
            trace ("판매 종료");
            target.count_txt.text = com.mgame.webMall.text.PagePackageTextDefine.commonStorePage_StorePageCtype_537;
            return;
        }
        else if (limit_type == "3")
        {
            target.count_txt.text = limit_remain + " / " + limit_total + "\n";
            target.count_txt.text = target.count_txt.text + (day + com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_548_01() + hour + com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_548_02() + min + com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_548_03() + sec + com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_548_04());
        }
        else
        {
            target.count_txt.text = day + com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_548_01() + hour + com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_548_02() + min + com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_548_03() + sec + com.mgame.webMall.text.PagePackageTextDefine.__get__commonStorePage_StorePageCtype_548_04();
        } // end else if
        sec = sec - 1;
        if (sec == -1)
        {
            sec = 59;
            min = min - 1;
        } // end if
        if (min == -1)
        {
            min = 59;
            hour = hour - 1;
        } // end if
        if (hour == -1)
        {
            hour = 23;
            day = day - 1;
        } // end if
        timerNum = setInterval(this, "timer", 1000, day, hour, min, sec, target, limit_type, limit_remain, limit_total);
    } // End of the function
    function clearTimer()
    {
        clearInterval(timerNum);
    } // End of the function
    function detailAreaScroll()
    {
        var _loc10 = this;
        var _loc6 = thisPageData.__get__main().listTable_Ctype_main._x + thisPageData.__get__main().listTable_Ctype_main._width + 15;
        var _loc5 = thisPageData.__get__main().listTableTop._y;
        var _loc4 = 514;
        if (thisPageData.__get__main().scrollbar == undefined)
        {
            thisPageData.__get__main().attachMovie("scrollbar", "scrollbar", thisPageData.__get__main().getNextHighestDepth(), {_x: _loc6, _y: _loc5, _height: _loc4});
        } // end if
        thisPageData.__get__main().attachMovie("listTable_Ctype_mask", "listTable_Ctype_mask", thisPageData.__get__main().getNextHighestDepth(), {_x: thisPageData.__get__main().listTable_Ctype_main._x, _y: thisPageData.__get__main().listTable_Ctype_main._y});
        thisPageData.__get__main().listTable_Ctype_mask._x = thisPageData.__get__main().listTable_Ctype_main._x;
        thisPageData.__get__main().listTable_Ctype_mask._y = thisPageData.__get__listTableTop()._y + thisPageData.__get__listTableTop()._height;
        thisPageData.__get__main().listTable_Ctype_mask._width = thisPageData.__get__main().listTable_Ctype_main._width;
        thisPageData.__get__main().listTable_Ctype_mask._height = thisPageData.__get__main().listTable_Ctype_main._height + 32;
        thisPageData.__get__main().listTable_Ctype_main.setMask(thisPageData.__get__main().listTable_Ctype_mask);
        if (scrollBar == null)
        {
            scrollBar = new com.mgame.webMall.util.ScrollBar();
        } // end if
        var _loc7 = thisPageData.__get__main().listTable_Ctype_main._y;
        var _loc2 = thisPageData.__get__main().scrollbar.bar._y;
        var _loc3 = thisPageData.__get__main().scrollbar.bar._height;
        scrollBar.setScrollTarget(thisPageData.__get__main().listTable_Ctype_main);
        scrollBar.setScrollUpButton(thisPageData.__get__main().scrollbar.scrollUpButton);
        scrollBar.setScrollDownButton(thisPageData.__get__main().scrollbar.scrollDownButton);
        scrollBar.setScrollBar(thisPageData.__get__main().scrollbar.bar);
        scrollBar.setMouseWheelStyle(false);
        scrollBar.setMouseWheelEvent(thisPageData.__get__main().listTable_Ctype_main);
        scrollBar.start(514, _loc7, _loc2, _loc3);
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
        var _loc7 = thisPageData.__get__main().listTable_Ctype_main["listTable_Ctype" + listCount]._y + thisPageData.__get__main().listTable_Ctype_main["listTable_Ctype" + listCount]._height + 8;
        thisPageData.__get__main().listTable_Ctype_main.attachMovie("pageMain", "pageMain", thisPageData.__get__main().listTable_Ctype_main.getNextHighestDepth());
        thisPageData.__get__main().listTable_Ctype_main.pageMain._y = _loc7;
        thisPageData.__get__main().listTable_Ctype_main.pageMain.attachMovie("listPrevButton", "listPrevButton", thisPageData.__get__main().listTable_Ctype_main.pageMain.getNextHighestDepth());
        for (var _loc2 = _loc3; _loc2 <= _loc4; ++_loc2)
        {
            thisPageData.__get__main().listTable_Ctype_main.pageMain.attachMovie("pageNumber", "pageNumber" + _loc2, thisPageData.__get__main().listTable_Ctype_main.pageMain.getNextHighestDepth());
            thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2].number_txt.text = _loc2;
            thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2]._width = thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2].number_txt.textWidth + 2;
            if (thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + (_loc2 - 1)] == undefined)
            {
                thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2]._x = thisPageData.__get__main().listTable_Ctype_main.pageMain.listPrevButton._x + thisPageData.__get__main().listTable_Ctype_main.pageMain.listPrevButton._width + 6;
            }
            else
            {
                thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2]._x = thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + (_loc2 - 1)]._x + thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + (_loc2 - 1)]._width + 2;
            } // end else if
            thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2].index = _loc2;
            thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2].onRelease = function ()
            {
                _this.storePageXml.pageReload(index);
            };
            if (_loc2 == currentPage)
            {
                thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2].number_txt.textColor = "0xFFFFFF";
            } // end if
            if (_loc2 == recordSize)
            {
                ++_loc2;
                break;
            } // end if
        } // end of for
        var _loc5 = 6;
        thisPageData.__get__main().listTable_Ctype_main.pageMain.attachMovie("listNextButton", "listNextButton", thisPageData.__get__main().listTable_Ctype_main.pageMain.getNextHighestDepth());
        if (thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + (_loc2 - 1)] == undefined)
        {
            thisPageData.__get__main().listTable_Ctype_main.pageMain.listNextButton._x = thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2]._x + thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + _loc2]._width + _loc5;
        }
        else
        {
            thisPageData.__get__main().listTable_Ctype_main.pageMain.listNextButton._x = thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + (_loc2 - 1)]._x + thisPageData.__get__main().listTable_Ctype_main.pageMain["pageNumber" + (_loc2 - 1)]._width + _loc5;
        } // end else if
        thisPageData.__get__main().listTable_Ctype_main.pageMain.listPrevButton.onRelease = function ()
        {
            if (currentPage - 1 > 0)
            {
                _this.storePageXml.pageReload(currentPage - 1);
            } // end if
        };
        thisPageData.__get__main().listTable_Ctype_main.pageMain.listNextButton.onRelease = function ()
        {
            if (currentPage + 1 <= recordSize)
            {
                _this.storePageXml.pageReload(currentPage + 1);
            } // end if
        };
        thisPageData.__get__main().listTable_Ctype_main.pageMain._x = thisPageData.__get__main().listTable_Ctype_main._width / 2 - thisPageData.__get__main().listTable_Ctype_main.pageMain._width / 2;
    } // End of the function
    function jsCall_multi_viewItem()
    {
        var _loc3 = new Array();
        for (var _loc2 = 1; _loc2 <= listCount; ++_loc2)
        {
            if (thisPageData.__get__main().listTable_Ctype_main["listTable_Ctype" + _loc2].checkBox.checkBox.selected)
            {
                _loc3.push(returnXmlData.setArrayData(thisPageData.__get__itemArr(), _loc2 - 1, "normalShop"));
            } // end if
        } // end of for
        com.mgame.webMall.util.CommonPopup.popupStart("buy_select", _loc3);
        this.clearTimer();
    } // End of the function
    function jsCall_multi_basketIn()
    {
        var _loc3 = new Array();
        for (var _loc2 = 1; _loc2 <= listCount; ++_loc2)
        {
            if (thisPageData.__get__main().listTable_Ctype_main["listTable_Ctype" + _loc2].checkBox.checkBox.selected)
            {
                _loc3.push(returnXmlData.setArrayData(thisPageData.__get__itemArr(), _loc2 - 1, "normalShop"));
            } // end if
        } // end of for
        com.mgame.webMall.util.CommonPopup.popupStart("basket", _loc3);
        this.clearTimer();
    } // End of the function
    function checkCancel()
    {
        for (var _loc2 = 1; _loc2 <= listCount; ++_loc2)
        {
            thisPageData.__get__main().listTable_Ctype_main["listTable_Ctype" + _loc2].checkBox.checkBox.selected = false;
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
    var scrollBar = null;
    var returnXmlData = null;
    var numberSplit = null;
    var detailContentScrollBar = null;
    var previewItemXml = null;
    var listCount = 0;
    var timerNum = 0;
    var itemDateChech = true;
} // End of Class
