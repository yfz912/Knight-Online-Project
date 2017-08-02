class com.mgame.webMall.main.MainCommonPopup
{
    var _parent, __get__targetCharCheckValue, __get__targetChar, __set__targetChar, __set__targetCharCheckValue;
    function MainCommonPopup()
    {
    } // End of the function
    function setData(mainData)
    {
        this.mainData = mainData;
    } // End of the function
    function popupStart(type, dataObj, popupType, optValue)
    {
        mainData.__get__mainStage().mainClose._alpha = 30;
        mainData.__get__mainStage().mainClose._visible = true;
        mainData.__get__mainStage().mainClose.useHandCursor = false;
        mainData.__get__mainStage().mainClose.onRelease = function ()
        {
        };
        if (type == "ticket_register")
        {
            this.couponPopupLoad();
        }
        else if (type == "detail")
        {
            this.itemDetailPopupLoad(dataObj);
        }
        else if (type == "buy_normal")
        {
            this.buyPopupLoad(dataObj, 1);
        }
        else if (type == "jorgi_normal")
        {
            this.jorgiMsgTabPopupLoad(dataObj);
        }
        else if (type == "gift_normal")
        {
            this.giftPupopLoad(dataObj);
        }
        else if (type == "premium_close")
        {
            this.premiumClosePopUpLoad(dataObj);
        }
        else if (type == "gift_detail")
        {
            this.giftDetailPopupLoad(dataObj);
        }
        else if (type == "jorgi_detail")
        {
            this.jorgiDetailPopupLoad(dataObj);
        }
        else if (type == "premium_check")
        {
            this.premiumCheckPopupLoad(dataObj);
        }
        else if (type == "inven_check")
        {
            this.invenCheckPopupLoad();
        }
        else if (type == "buy_select")
        {
            this.buySelectPopupLoad(dataObj, popupType, optValue);
        }
        else if (type == "basket")
        {
            this.basketControlXmlLoad(dataObj);
        }
        else if (type == "basket_modify")
        {
            this.basketControlEditXml(dataObj);
        }
        else if (type == "basket_del")
        {
            this.basketControlDelXml(dataObj);
        }
        else if (type == "limit_detail")
        {
            this.limitItemDetailPopupLoad(dataObj);
        }
        else if (type == "cashItemCancel")
        {
            this.cashItemCancelPopupLoad(dataObj);
        }
        else if (type == "cashItemSubmit")
        {
            this.cashItemSubmitPopupLoad(dataObj);
        } // end else if
    } // End of the function
    function couponPopupLoad()
    {
        var _this = this;
        var popupMovieClip = this.popupLoad("popup_counpon");
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        for (var _loc2 = 1; _loc2 < 5; ++_loc2)
        {
            popupMovieClip["_txt0" + _loc2].maxChars = 5;
            popupMovieClip["_txt0" + _loc2].restrict = "A-Z0-9";
        } // end of for
        popupMovieClip.couponButton.onRelease = function ()
        {
            _this.couponSerialCheck(popupMovieClip);
        };
    } // End of the function
    function couponSerialCheck(popupMovieClip)
    {
        var _loc3 = "";
        var _loc5 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_128();
        var _loc4 = new Object();
        for (var _loc2 = 1; _loc2 < 5; ++_loc2)
        {
            _loc3 = popupMovieClip["_txt0" + _loc2].text;
            if (_loc3.length < 5)
            {
                this.errorMsgPopupLoad(_loc5, "open");
                return;
            } // end if
            _loc4["num" + _loc2] = _loc3;
        } // end of for
        this.couponSerialXmlLoad(popupMovieClip, _loc4);
    } // End of the function
    function couponSerialCompletePopupLoad(msg)
    {
        var _loc2 = this.popupLoad("confirmMsgPopup");
        _loc2.msg_txt.html = true;
        _loc2.msg_txt.multiline = true;
        _loc2.msg_txt.wordWrap = true;
        _loc2.msg_txt.htmlText = msg;
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
        this.popupConfirmButtonEvent(_loc2);
    } // End of the function
    function itemDetailPopupLoad(dataObj)
    {
        var _this = this;
        var selectCount = 1;
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var popupMovieClip = this.popupLoad("popup_itemDetailView");
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        this.itemImageLoad(popupMovieClip.imageArea, com.mgame.webMall.main.CommonDataUrl.__get__itemImageURL() + dataObj.bigimage, 64, 64);
        var _loc7 = dataObj.limit_age;
        var _loc8 = popupMovieClip.imageArea._x;
        var _loc9 = popupMovieClip.imageArea._y;
        popupMovieClip.attachMovie("limit_age" + _loc7, "limit_age" + _loc7, popupMovieClip.getNextHighestDepth(), {_x: _loc8, _y: _loc9});
        var _loc5 = this.comboBoxLoad(popupMovieClip, "countCombobox", 160, 85, 77, 20, 1);
        for (var _loc2 = 1; _loc2 <= 10; ++_loc2)
        {
            _loc5.addItem({label: _loc2, data: _loc2});
        } // end of for
        var _loc6 = new Object();
        _loc6.change = function (evt_obj)
        {
            selectCount = evt_obj.target.selectedItem.data;
        };
        _loc5.addEventListener("change", _loc6);
        popupMovieClip.name_txt.text = dataObj.name;
        popupMovieClip.price_txt.text = numberSplit.split(dataObj.dc) + _this.getDtypeData(dataObj.dtype);
        popupMovieClip.explain_txt.html = true;
        popupMovieClip.explain_txt.multiline = true;
        popupMovieClip.explain_txt.wordWrap = true;
        popupMovieClip.explain_txt.htmlText = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_197_01() + dataObj.explain1 + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_197_02() + dataObj.explain2;
        if (popupMovieClip.explain_txt.maxscroll > 1)
        {
            popupMovieClip.createClassObject(mx.controls.UIScrollBar, "scrollbar", 10);
            popupMovieClip.scrollbar.move(476, 148);
            popupMovieClip.scrollbar.setSize(16, 120);
            popupMovieClip.scrollbar.setScrollTarget(popupMovieClip.explain_txt);
            popupMovieClip.attachMovie("uiScroll", "uiScroll", 11, {_x: 476, _y: 148});
        } // end if
        if (com.mgame.webMall.main.MainData.__get__previewPageType() == false)
        {
            popupMovieClip.cancelButton._x = popupMovieClip.previewButton._x;
            popupMovieClip.previewButton._visible = false;
        } // end if
        popupMovieClip.buyButton.onRelease = function ()
        {
            _this.buyPopupLoad(dataObj, selectCount);
        };
        popupMovieClip.cartButton.onRelease = function ()
        {
            _this.basketControlXmlLoad(dataObj);
        };
        popupMovieClip.giftButton.onRelease = function ()
        {
            _this.giftItemCountCheck(popupMovieClip, dataObj, selectCount);
        };
        popupMovieClip.jorgiButton.onRelease = function ()
        {
            _this.jorgiMsgTabPopupLoad(dataObj);
        };
        popupMovieClip.previewButton.onRelease = function ()
        {
            _this.previewCheck(dataObj);
        };
    } // End of the function
    function limitItemDetailPopupLoad(dataObj)
    {
        var _this = this;
        var _loc2 = 1;
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var popupMovieClip = this.popupLoad("popup_limitItemDetailView");
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        this.itemImageLoad(popupMovieClip.imageArea, com.mgame.webMall.main.CommonDataUrl.__get__itemImageURL() + dataObj.bigimage, 64, 64);
        popupMovieClip.name_txt.text = dataObj.name;
        popupMovieClip.price_txt.text = numberSplit.split(dataObj.dc) + _this.getDtypeData(dataObj.dtype);
        popupMovieClip.count_txt.text = "1";
        if (dataObj.limit_type == "1")
        {
            popupMovieClip.limit_count.text = dataObj.limit_remain + " / " + dataObj.limit_total;
            popupMovieClip.limit_count.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_253;
        }
        else if (dataObj.limit_type == "2")
        {
            popupMovieClip.limit_count.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_257;
            this.limitTime(dataObj.limit_sdate, dataObj.limit_edate, popupMovieClip, dataObj.limit_type);
        }
        else
        {
            popupMovieClip.limit_count.text = dataObj.limit_remain + " / " + dataObj.limit_total;
            this.limitTime(dataObj.limit_sdate, dataObj.limit_edate, popupMovieClip, dataObj.limit_type);
        } // end else if
        popupMovieClip.explain_txt.html = true;
        popupMovieClip.explain_txt.multiline = true;
        popupMovieClip.explain_txt.wordWrap = true;
        popupMovieClip.explain_txt.htmlText = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_269_01() + dataObj.explain1 + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_269_02() + dataObj.explain2;
        if (popupMovieClip.explain_txt.maxscroll > 1)
        {
            popupMovieClip.createClassObject(mx.controls.UIScrollBar, "scrollbar", 10);
            popupMovieClip.scrollbar.move(476, 206);
            popupMovieClip.scrollbar.setSize(16, 120);
            popupMovieClip.scrollbar.setScrollTarget(popupMovieClip.explain_txt);
            popupMovieClip.attachMovie("uiScroll", "uiScroll", 11, {_x: 476, _y: 206});
        } // end if
        popupMovieClip.buyButton.onRelease = function ()
        {
            if (_this.itemDateChech == false)
            {
                _this.errorMsgPopupLoad(com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_296(), "close");
            }
            else
            {
                _this.buyPopupLoad(dataObj, "1");
            } // end else if
        };
        popupMovieClip.cartButton.onRelease = function ()
        {
            _this.basketControlXmlLoad(dataObj);
        };
        popupMovieClip.giftButton.onRelease = function ()
        {
            if (_this.itemDateChech == false)
            {
                _this.errorMsgPopupLoad(com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_309(), "close");
            }
            else
            {
                _this.giftItemCountCheck(popupMovieClip, dataObj, 1);
            } // end else if
        };
        popupMovieClip.jorgiButton.onRelease = function ()
        {
            _this.jorgiMsgTabPopupLoad(dataObj);
        };
        popupMovieClip.previewButton.onRelease = function ()
        {
            _this.previewCheck(dataObj);
        };
    } // End of the function
    function itemLimitCheck(dataObj)
    {
        if (dataObj.limit_type == "1" || dataObj.limit_type == "3")
        {
            if (Number(dataObj.limit_remain) < 1)
            {
                return (false);
            }
            else
            {
                return (true);
            } // end else if
        }
        else if (dataObj.limit_type == "2")
        {
            this.limitTime(dataObj.limit_sdate, dataObj.limit_edate, null, dataObj.limit_type);
            if (dateItemLimitCheck == true)
            {
                return (true);
            }
            else
            {
                dateItemLimitCheck = true;
                return (false);
            } // end else if
        } // end else if
    } // End of the function
    function buyPopupLoad(dataObj, count)
    {
        if (this.itemLimitCheck(dataObj) == false)
        {
            var _loc10 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_356();
            this.errorMsgPopupLoad(_loc10, "close");
            return;
        } // end if
        if (com.mgame.webMall.main.MainData.__get__commonStorePageType() == "gzone" && com.mgame.webMall.main.MainData.__get__pcRoomCheck() == "NONE")
        {
            this.pcRoomCheck();
            return;
        } // end if
        var _this = this;
        var shortOfCashCheck = false;
        var shortOfCashType = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_370();
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        if (dataObj.dc == undefined)
        {
            dataObj.dc = dataObj.price;
        } // end if
        var _loc5 = new Date();
        _loc5.setDate(_loc5.getDate() + 6);
        var _loc9 = _loc5.getFullYear();
        var _loc8 = _loc5.getMonth() + 1;
        var _loc7 = _loc5.getDate();
        var _loc11 = String(_loc9) + "/" + String(_loc8) + "/" + String(_loc7);
        var popupMovieClip = this.popupLoad("popup_buy");
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        this.userCashTypeByPopupName(popupMovieClip, dataObj, dataObj.dtype, count);
        shortOfCashCheck = this.userCashCheck(dataObj, dataObj.dtype, popupMovieClip, count).shortOfCashCheck;
        shortOfCashType = this.userCashCheck(dataObj, dataObj.dtype, popupMovieClip, count).shortOfCashType;
        popupMovieClip.buyButton.onRelease = function ()
        {
            if (shortOfCashCheck)
            {
                popupMovieClip.c_noticeButton.enabled = false;
                popupMovieClip.buyButton.enabled = false;
                popupMovieClip.closeButton.enabled = false;
                popupMovieClip.cancelButton.enabled = false;
                var _loc1 = "<br><p align=\'center\'>" + shortOfCashType + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_387();
                if (dataObj.dtype == "8")
                {
                    _this.errorMsgPopupLoad(_loc1, "open", popupMovieClip);
                }
                else
                {
                    _this.errorMsgPopupLoad(_loc1, "charging", popupMovieClip);
                } // end else if
            }
            else
            {
                _this.xmlLoad(popupMovieClip, dataObj, com.mgame.webMall.main.MainData.__get__mgmac(), "BUY_NORMAL", count, _this.returnCashType(dataObj.dtype), ticketCombobox.selectedItem.data, "", "", "", "", dataObj.dtype);
            } // end else if
        };
        popupMovieClip.giftButton.onRelease = function ()
        {
            if (shortOfCashCheck)
            {
                var _loc1 = "<br><p align=\'center\'>" + shortOfCashType + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_399();
                _this.errorMsgPopupLoad(_loc1, "open");
            }
            else
            {
                _this.giftItemCountCheck(popupMovieClip, dataObj, 1);
            } // end else if
        };
        popupMovieClip.jorgiButton.onRelease = function ()
        {
            _this.jorgiMsgTabPopupLoad(dataObj);
        };
        popupMovieClip.c_noticeButton.onRelease = function ()
        {
            _this.cashItemProvisionPopupLoad();
        };
        if (dataObj.dtype != "5" && dataObj.dtype != "8")
        {
            var ticketCombobox = this.comboBoxLoad(popupMovieClip, "ticketCombobox", 236, 283, 221, 20, 1);
            ticketCombobox.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_415(), data: ""});
            for (var _loc2 = 0; _loc2 < com.mgame.webMall.main.MainData.__get__TICKET_cause().length; ++_loc2)
            {
                ticketCombobox.addItem({label: com.mgame.webMall.main.MainData.__get__TICKET_cause()[_loc2], data: com.mgame.webMall.main.MainData.__get__TICKET_serial_no()[_loc2]});
            } // end of for
            var _loc6 = new Object();
            _loc6.change = function (evt_obj)
            {
            };
            ticketCombobox.addEventListener("change", _loc6);
        } // end if
    } // End of the function
    function buyCompletePopupLoad(itemName, itemCount, itemPrice, itemDate, dtype)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc2 = this.popupLoad("popup_buyComplete");
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
        this.popupConfirmButtonEvent(_loc2);
        _loc2.listTop.setMask(_loc2.maskMovieClip);
        var _loc4 = 0;
        var _loc3 = _loc2.listTop._height + 1;
        _loc2.listTop.attachMovie("buyListTable", "buyListTable", _loc2.listTop.getNextHighestDepth(), {_x: _loc4, _y: _loc3});
        _loc2.listTop.buyListTable.name_txt.text = itemName;
        _loc2.listTop.buyListTable.count_txt.text = itemCount + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_447();
        _loc2.listTop.buyListTable.price_txt.text = numberSplit.split(itemPrice) + this.getDtypeData(dtype);
        _loc2.listTop.buyListTable.regdate_txt.text = itemDate;
    } // End of the function
    function userCashCheck(dataObj, dtype, popupMovieClip, count)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc2 = dataObj.dc;
        if (_loc2 == undefined)
        {
            _loc2 = dataObj.price;
        } // end if
        if (count == undefined)
        {
            count = 1;
        } // end if
        _loc2 = String(Number(_loc2) * count);
        var _loc3 = new Object();
        if (dtype == "5")
        {
            if (Number(_loc2) > Number(mainData.__get__rightMainData().__get__gPoint()))
            {
                _loc3.shortOfCashCheck = true;
                _loc3.shortOfCashType = "GP";
                popupMovieClip.pay02_txt.text = numberSplit.split(String(Math.abs(_loc2 - mainData.__get__rightMainData().__get__gPoint()))) + " GP";
            }
            else
            {
                popupMovieClip.pay02_txt.text = "0 P";
            } // end else if
        }
        else if (dtype == "8")
        {
            if (Number(_loc2) > Number(mainData.__get__rightMainData().__get__gPoint()))
            {
                _loc3.shortOfCashCheck = true;
                _loc3.shortOfCashType = "Millage";
                popupMovieClip.pay02_txt.text = numberSplit.split(String(Math.abs(_loc2 - mainData.__get__rightMainData().__get__gPoint()))) + " P";
            }
            else
            {
                popupMovieClip.pay02_txt.text = "0 P";
            } // end else if
        }
        else if (Number(_loc2) > Number(mainData.__get__rightMainData().__get__nMCash()) + Number(mainData.__get__rightMainData().__get__nPCash()))
        {
            _loc3.shortOfCashCheck = true;
            _loc3.shortOfCashType = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_490;
            popupMovieClip.pay02_txt.text = numberSplit.split(String(Math.abs(Number(_loc2) - (Number(mainData.__get__rightMainData().__get__nMCash()) + Number(mainData.__get__rightMainData().__get__nPCash()))))) + " NPts";
        }
        else
        {
            popupMovieClip.pay02_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_495;
        } // end else if
        return (_loc3);
    } // End of the function
    function userCashTypeByPopupName(popupMovieClip, dataObj, dtype, count)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc4 = dataObj.dc;
        var _loc3 = dataObj.dc;
        var _loc11 = mainData.__get__rightMainData().__get__gPoint();
        var _loc12 = mainData.__get__rightMainData().__get__webPoint();
        var _loc7 = new Date();
        var _loc10 = _loc7.getFullYear();
        var _loc9 = _loc7.getMonth() + 1;
        var _loc8 = _loc7.getDate();
        if (_loc3 == undefined)
        {
            _loc3 = dataObj.price;
        } // end if
        if (_loc4 == undefined)
        {
            _loc4 = dataObj.price;
        } // end if
        if (count == undefined)
        {
            count = 1;
        } // end if
        _loc3 = String(Number(_loc3) * count);
        var _loc13 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_521();
        if (dtype == "5")
        {
            popupMovieClip.title01_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_526;
            popupMovieClip.title02_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_527;
            popupMovieClip.title03_txt.text = "";
            popupMovieClip.title04_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_529;
            popupMovieClip.name_txt.text = dataObj.name;
            popupMovieClip.count_txt.text = count + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_532();
            popupMovieClip.price_txt.text = numberSplit.split(_loc4) + " GP";
            popupMovieClip.regdate_txt.text = _loc10 + "-" + _loc9 + "-" + _loc8;
            popupMovieClip.pay_txt.text = numberSplit.split(_loc3) + " GP";
            popupMovieClip.gameCash_txt.text = numberSplit.split(_loc11) + " GP";
        }
        else if (dtype == "8")
        {
            popupMovieClip.title01_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_539;
            popupMovieClip.title02_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_540;
            popupMovieClip.title03_txt.text = "";
            popupMovieClip.title04_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_542;
            popupMovieClip.name_txt.text = dataObj.name;
            popupMovieClip.count_txt.text = count + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_545();
            popupMovieClip.price_txt.text = numberSplit.split(_loc4) + " P";
            popupMovieClip.regdate_txt.text = _loc10 + "-" + _loc9 + "-" + _loc8;
            popupMovieClip.pay_txt.text = numberSplit.split(_loc3) + " P";
            popupMovieClip.gameCash_txt.text = numberSplit.split(_loc11) + " P";
        }
        else
        {
            popupMovieClip.title01_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_552;
            popupMovieClip.title02_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_553;
            popupMovieClip.title03_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_554;
            popupMovieClip.title04_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_555;
            popupMovieClip.name_txt.text = dataObj.name;
            popupMovieClip.count_txt.text = count + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_558();
            popupMovieClip.price_txt.text = numberSplit.split(_loc4) + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_559();
            popupMovieClip.regdate_txt.text = _loc10 + "-" + _loc9 + "-" + _loc8;
            popupMovieClip.pay_txt.text = numberSplit.split(_loc3) + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_561();
            popupMovieClip.gameCash_txt.text = numberSplit.split(mainData.__get__rightMainData().__get__nMCash()) + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_562();
            popupMovieClip.giftCash_txt.text = numberSplit.split(mainData.__get__rightMainData().__get__nPCash()) + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_563();
        } // end else if
        popupMovieClip.title05_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_565;
        popupMovieClip.title06_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_566;
    } // End of the function
    function cashItemProvisionPopupLoad()
    {
        if (mainData.__get__mainStage().mainClose._alpha == 0)
        {
            mainData.__get__mainStage().mainClose._alpha = 30;
            mainData.__get__mainStage().mainClose._visible = true;
            mainData.__get__mainStage().mainClose.enabled = false;
            mainData.__get__mainStage().mainClose.onRelease = function ()
            {
            };
        } // end if
        var _loc2 = this.popupLoad("popup_cashItemProvision");
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
        this.popupConfirmButtonEvent(_loc2);
    } // End of the function
    function giftItemCountCheck(popupMovieClip, dataObj, count)
    {
        if (count > 1)
        {
            popupMovieClip.buyButton.enabled = false;
            popupMovieClip.giftButton.enabled = false;
            popupMovieClip.cartButton.enabled = false;
            popupMovieClip.closeButton.enabled = false;
            popupMovieClip.cancelButton.enabled = false;
            var _loc3 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_252();
            this.errorMsgPopupLoad(_loc3, "open", popupMovieClip);
            return;
        }
        else
        {
            this.giftPupopLoad(dataObj, count);
        } // end else if
    } // End of the function
    function giftPupopLoad(dataObj, count)
    {
        var _loc7 = null;
        if (this.itemLimitCheck(dataObj) == false)
        {
            _loc7 = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_576;
            this.errorMsgPopupLoad(_loc7, "close");
            return;
        } // end if
        var _this = this;
        var shortOfCashCheck = false;
        var shortOfCashType = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_583();
        var _loc8 = 1;
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        textLengthCheck = new com.mgame.webMall.util.TextLengthCheck();
        if (dataObj.dc == undefined)
        {
            dataObj.dc = dataObj.price;
			
        } // end if
        var popupMovieClip = this.popupLoad("popup_gift");
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        this.userCashTypeByPopupName(popupMovieClip, dataObj, dataObj.dtype, count);
        shortOfCashCheck = this.userCashCheck(dataObj, dataObj.dtype, popupMovieClip, count).shortOfCashCheck;
        shortOfCashType = this.userCashCheck(dataObj, dataObj.dtype, popupMovieClip, count).shortOfCashType;
        popupMovieClip.giftButton.onRelease = function ()
        {
            var _loc1 = popupMovieClip.msg_txt.text;
            if (shortOfCashCheck)
            {
                _loc1 = "<br><p align=\'center\'>" + shortOfCashType + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_618();
                _this.errorMsgPopupLoad(_loc1, "open");
            }
            else if (_this._targetCharCheckValue)
            {
                _this.xmlLoad(popupMovieClip, dataObj, com.mgame.webMall.main.MainData.__get__mgmac(), "GIFT_NORMAL", 1, _this.returnCashType(dataObj.dtype), ticketCombobox.selectedItem.data, "", _this.targetChar, _loc1, "", dataObj.dtype);
            }
            else
            {
                _loc1 = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_627;
                _this.errorMsgPopupLoad(_loc1, "open");
            } // end else if
        };
        popupMovieClip.userCheckButton.onRelease = function ()
        {
            var _loc1 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_716();
            popupMovieClip.userID_txt.text = _this.textLengthCheck.FFGetByteLength(popupMovieClip.userID_txt).strValue;
            if (popupMovieClip.userID_txt.text == "")
            {
                _this.errorMsgPopupLoad(_loc1, "open");
                return;
            } // end if
            _this.mainData.mainStage.mainClose.swapDepths(popupMovieClip);
            _this.userCheckStart(popupMovieClip.userID_txt.text, popupMovieClip);
        };
        if (dataObj.dtype != "5" && dataObj.dtype != "8")
        {
            var ticketCombobox = this.comboBoxLoad(popupMovieClip, "ticketCombobox", 175, 433, 221, 20, 1);
            ticketCombobox.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_640(), data: ""});
            for (var _loc2 = 0; _loc2 < com.mgame.webMall.main.MainData.__get__TICKET_cause().length; ++_loc2)
            {
                ticketCombobox.addItem({label: com.mgame.webMall.main.MainData.__get__TICKET_cause()[_loc2], data: com.mgame.webMall.main.MainData.__get__TICKET_serial_no()[_loc2]});
            } // end of for
            var _loc5 = new Object();
            _loc5.change = function (evt_obj)
            {
            };
            ticketCombobox.addEventListener("change", _loc5);
        } // end if
    } // End of the function
    function giftCompletePopupLoad(itemName, itemCount, itemPrice, itemDate, giftUser, msg, dtype)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc2 = this.popupLoad("popup_giftComplete");
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
        this.popupConfirmButtonEvent(_loc2);
        _loc2.name_txt.text = itemName;
        _loc2.count_txt.text = itemCount + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_665();
        _loc2.price_txt.text = numberSplit.split(itemPrice) + this.getDtypeData(dtype);
        _loc2.regdate_txt.text = itemDate;
        _loc2.giftDate_txt.text = itemDate;
        _loc2.giftUser_txt.text = giftUser;
        _loc2.msg_txt.text = msg;
    } // End of the function
    function jorgiMsgTabPopupLoad(dataObj)
    {
        var _this = this;
        var _loc3 = dataObj.dc;
        var _loc4 = 1;
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        if (_loc3 == undefined)
        {
            _loc3 = dataObj.price;
        } // end if
        var popupMovieClip = this.popupLoad("popup_jorgiMsgTab");
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        popupMovieClip.tab02.onRelease = function ()
        {
        };
        popupMovieClip.userCheckButton.onRelease = function ()
        {
            _this.userCheckStart(popupMovieClip.userID_txt.text);
        };
        popupMovieClip.jorgiButton.onRelease = function ()
        {
            var _loc1 = popupMovieClip.msg_txt.text;
            if (_this._targetCharCheckValue)
            {
                _this.jorgiStart(dataObj.goodsno, _this.targetChar, _loc1);
            }
            else
            {
                _loc1 = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_721;
                _this.errorMsgPopupLoad(_loc1, "open");
            } // end else if
        };
        popupMovieClip.name_txt.text = dataObj.name;
        popupMovieClip.count_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_727;
        popupMovieClip.price_txt.text = numberSplit.split(_loc3) + _this.getDtypeData(dataObj.dtype);
    } // End of the function
    function jorgiGiftTabPopup(dataObj)
    {
        var _this = this;
        var selectCount = 1;
        var _loc8 = "테스트서버";
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc6 = this.popupLoad("popup_jorgiPhoneTab");
        this.setPopupPosition(_loc6);
        this.popupCloseButtonEvent(_loc6);
        var _loc5 = this.comboBoxLoad(_loc6, "countCombobox", 267, 131, 50, 20, 1);
        for (var _loc2 = 1; _loc2 <= 10; ++_loc2)
        {
            _loc5.addItem({label: _loc2 + "개", data: _loc2});
        } // end of for
        var _loc7 = new Object();
        _loc7.change = function (evt_obj)
        {
            selectCount = evt_obj.target.selectedItem.data;
        };
        _loc5.addEventListener("change", _loc7);
        _loc6.tab01.onRelease = function ()
        {
            _this.jorgiMsgTabPopupLoad(dataObj);
        };
        _loc6.name_txt.text = dataObj.name;
        _loc6.price_txt.text = numberSplit.split(dataObj.dc) + " 원";
    } // End of the function
    function premiumCheckPopupLoad(dataObj)
    {
        var _this = this;
        var _loc3 = new Date();
        var _loc6 = _loc3.getFullYear();
        var _loc5 = _loc3.getMonth() + 1;
        var _loc4 = _loc3.getDate();
        var _loc8 = _loc5 < 10 ? (String("0" + _loc5)) : (String(_loc5));
        var _loc7 = _loc4 < 10 ? (String("0" + _loc4)) : (String(_loc4));
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var popupMovieClip = this.popupLoad("popup_settleCheck");
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        popupMovieClip.name_txt.text = dataObj.name;
        popupMovieClip.count_txt.text = "1";
        popupMovieClip.price_txt.text = numberSplit.split(dataObj.dc) + " 원";
        popupMovieClip.regdate_txt.text = String(_loc6 + "-" + _loc8 + "-" + _loc7);
        popupMovieClip.settleButton.onRelease = function ()
        {
            var _loc1 = "";
            popupMovieClip.settleButton.enabled = false;
            popupMovieClip.cancelButton.enabled = false;
            popupMovieClip.closeButton.enabled = false;
            if (popupMovieClip.check01.selected && popupMovieClip.check02.selected)
            {
                _loc1 = com.mgame.webMall.main.MainData.__get__LOGIN_uid() + "," + dataObj.goodsno + "," + dataObj.name + "," + dataObj.dc;
                getURL("FSCommand:settle", _loc1);
                _this.popupClose(popupMovieClip);
            }
            else if (!popupMovieClip.check01.selected)
            {
                _loc1 = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_802;
                _this.errorMsgPopupLoad(_loc1, "open", popupMovieClip);
            }
            else if (!popupMovieClip.check02.selected)
            {
                _loc1 = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_806;
                _this.errorMsgPopupLoad(_loc1, "open", popupMovieClip);
            } // end else if
        };
    } // End of the function
    function premiumClosePopUpLoad(dataObj)
    {
        var _this = this;
        var popupMovieClip = this.popupLoad("premium_close");
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        popupMovieClip.confirmButton.onRelease = function ()
        {
            _this.settleCloseXmlLoad(popupMovieClip, dataObj.num);
        };
    } // End of the function
    function premiumCloseCompletePopupLoad()
    {
        var _loc2 = this.popupLoad("premium_complete");
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
        this.popupConfirmButtonEvent(_loc2);
    } // End of the function
    function giftDetailPopupLoad(dataObj)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc2 = this.popupLoad("popup_giftDetail");
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
        this.itemImageLoad(_loc2.imageArea, com.mgame.webMall.main.CommonDataUrl.__get__itemImageURL() + dataObj.bigimage, 64, 64);
        _loc2.name_txt.text = dataObj.name;
        _loc2.count_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_849;
        _loc2.price_txt.text = numberSplit.split(dataObj.price) + this.getDtypeData(dataObj.dtype);
        _loc2.regdate_txt.text = dataObj.indate;
        _loc2.userchar_txt.text = dataObj.userchar;
        _loc2.message_txt.text = dataObj.message;
    } // End of the function
    function jorgiDetailPopupLoad(dataObj)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc2 = this.popupLoad("popup_jorgiDetail");
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
        this.itemImageLoad(_loc2.imageArea, com.mgame.webMall.main.CommonDataUrl.__get__itemImageURL() + dataObj.bigimage, 64, 64);
        _loc2.name_txt.text = dataObj.name;
        _loc2.count_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_869;
        _loc2.price_txt.text = numberSplit.split(dataObj.price) + this.getDtypeData(dataObj.dtype);
        _loc2.regdate_txt.text = dataObj.indate;
        _loc2.userchar_txt.text = dataObj.userchar;
        _loc2.message_txt.text = dataObj.message;
    } // End of the function
    function invenCheckPopupLoad()
    {
        var _loc2 = this.popupLoad("popup_inven");
        var _loc3 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc3.invenCheckStart(_loc2, this);
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
    } // End of the function
    function setInvenData(popupMovieClip, totalInven, inven, cashTotalInven, cashInven)
    {
        popupMovieClip.totalInven_txt.text = totalInven + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_892();
        popupMovieClip.inven_txt.text = inven + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_893();
        popupMovieClip.cashTotalInven_txt.text = cashTotalInven + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_892();
        popupMovieClip.cashInven_txt.text = cashInven + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_893();
    } // End of the function
    function buySelectPopupLoad(dataObj, popupType, optValue)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        if (popupType != "basket" && com.mgame.webMall.main.MainData.__get__commonStorePageType() == "gzone" && com.mgame.webMall.main.MainData.__get__pcRoomCheck() == "NONE")
        {
            this.pcRoomCheck();
            return;
        } // end if
        var _this = this;
        var cmd = "BUY_SELECT";
        var _loc4 = null;
        var priceTarget = null;
        var _loc16 = 0;
        var _loc9 = 0;
        var popupMovieClip = this.popupLoad("popup_buySelect");
        popupMovieClip.listTop.setMask(popupMovieClip.maskMovieClip);
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
        this.itemImageLoad(popupMovieClip.imageArea, com.mgame.webMall.main.CommonDataUrl.__get__itemImageURL() + this.returnItemData(popupType, dataObj[0], "bigimage"), 64, 64);
        if (popupType == "package")
        {
            cmd = "BUY_PACKAGE";
        } // end if
        this.setInfoData(popupMovieClip, dataObj[0]);
        var i = 1;
        while (i <= dataObj.length)
        {
            dataObj[i - 1].selectCount = 1;
            if (i == 1)
            {
                _loc9 = popupMovieClip.listTop._height + 1;
            }
            else
            {
                _loc9 = popupMovieClip.listTop["listTable" + (i - 1)]._y + popupMovieClip.listTop["listTable" + (i - 1)]._height + 1;
            } // end else if
            _loc4 = popupMovieClip.listTop.attachMovie("listTable", "listTable" + i, popupMovieClip.listTop.getNextHighestDepth(), {_x: _loc16, _y: _loc9});
            _loc4.idx = i;
            _loc4.name_txt.text = this.returnItemData(popupType, dataObj[i - 1], "name");
            _loc4.price_txt.text = numberSplit.split(this.returnItemData(popupType, dataObj[i - 1], "dc")) + _this.getDtypeData(dataObj[i - 1].dtype);
            var _loc3 = this.comboBoxLoad(_loc4, "countCombobox", 185, 6, 50, 20, i);
            if (popupType == "package")
            {
                _loc3.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_952(), data: "1"});
            }
            else if (popupType == "basket")
            {
                _loc3.addItem({label: dataObj[i - 1].item_count, data: dataObj[i - 1].item_count});
            }
            else if (dataObj[i - 1].limit_type != "0")
            {
                _loc3.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_958(), data: "1"});
            }
            else
            {
                for (var _loc2 = 1; _loc2 <= 10; ++_loc2)
                {
                    _loc3.addItem({label: _loc2 + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_963(), data: _loc2});
                } // end of for
            } // end else if
            var _loc7 = new Object();
            _loc7.change = function (evt_obj)
            {
                var _loc1 = evt_obj.target._parent._name;
                var _loc2 = Number(_loc1.substr(_loc1.length - 1));
                dataObj[_loc2 - 1].selectCount = evt_obj.target.selectedItem.data;
                _this.priceByCount(dataObj, priceTarget);
            };
            _loc3.addEventListener("change", _loc7);
            _loc4.selectArea.onRelease = function ()
            {
                _this.itemImageLoad(popupMovieClip.imageArea, com.mgame.webMall.main.CommonDataUrl.__get__itemImageURL() + _this.returnItemData(popupType, dataObj[_parent.idx - 1], "bigimage"), 64, 64);
                _this.setInfoData(popupMovieClip, dataObj[_parent.idx - 1]);
            };
            ++i;
        } // end while
        _loc9 = popupMovieClip.listTop["listTable" + (i - 1)]._y + popupMovieClip.listTop["listTable" + (i - 1)]._height + 1;
        priceTarget = popupMovieClip.listTop.attachMovie("listTable_price", "listTable_price", popupMovieClip.listTop.getNextHighestDepth(), {_x: _loc16, _y: _loc9});
        popupMovieClip.buyButton.onRelease = function ()
        {
            var _loc1 = "";
            var _loc4 = "";
            var _loc3 = "";
            var _loc5 = "";
            var _loc2 = 0;
            for (i = 0; i < dataObj.length; i++)
            {
                if (i < dataObj.length - 1)
                {
                    _loc1 = _loc1 + (_this.returnItemData(popupType, dataObj[i], "goodsno") + "|");
                    _loc4 = _loc4 + (_this.returnItemData(popupType, dataObj[i], "selectCount") + "|");
                    _loc3 = _loc3 + (_this.returnItemData(popupType, dataObj[i], "dc") + "|");
                    _loc5 = _loc5 + (_this.returnCashType(_this.returnItemData(popupType, dataObj[i], "dtype")) + "|");
                    _loc2 = _loc2 + Number(_this.returnItemData(popupType, dataObj[i], "dc")) * Number(_this.returnItemData(popupType, dataObj[i], "selectCount"));
                    continue;
                } // end if
                _loc1 = _loc1 + _this.returnItemData(popupType, dataObj[i], "goodsno");
                _loc4 = _loc4 + _this.returnItemData(popupType, dataObj[i], "selectCount");
                _loc3 = _loc3 + _this.returnItemData(popupType, dataObj[i], "dc");
                _loc5 = _loc5 + _this.returnCashType(_this.returnItemData(popupType, dataObj[i], "dtype"));
                _loc2 = _loc2 + Number(_this.returnItemData(popupType, dataObj[i], "dc")) * Number(_this.returnItemData(popupType, dataObj[i], "selectCount"));
            } // end of for
            if (popupType == "package")
            {
                _loc1 = optValue + "," + _loc1;
            } // end if
            var _loc6 = Number(_this.mainData.rightMainData.nMCash) + Number(_this.mainData.rightMainData.nPCash);
            if (_loc6 < _loc2)
            {
                popupMovieClip.buyButton.enabled = false;
                popupMovieClip.closeButton.enabled = false;
                popupMovieClip.cancelButton.enabled = false;
                var _loc7 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1020();
                _this.errorMsgPopupLoad(_loc7, "charging", popupMovieClip);
            }
            else
            {
                _this.xmlLoad(popupMovieClip, _loc1, com.mgame.webMall.main.MainData.__get__mgmac(), cmd, _loc4, _this.returnCashType(dataObj[0].dtype), "", "", "", "", _loc3, dataObj[0].dtype);
            } // end else if
        };
        this.priceByCount(dataObj, priceTarget, popupType, optValue);
        this.scroll(popupMovieClip);
    } // End of the function
    function setInfoData(popupMovieClip, dataObj)
    {
        var _loc2 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1034() + dataObj.explain1;
        _loc2 = _loc2 + (com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1035() + dataObj.explain2);
        popupMovieClip.explain_txt.html = true;
        popupMovieClip.explain_txt.multiline = true;
        popupMovieClip.explain_txt.wordWrap = true;
        popupMovieClip.explain_txt.htmlText = _loc2;
    } // End of the function
    function returnItemData(type, dataObj, param)
    {
        if (type == "basket")
        {
            if (param == "goodsno")
            {
                param = "item_code";
            } // end if
            if (param == "selectCount")
            {
                param = "item_count";
            } // end if
            if (param == "dc")
            {
                param = "item_price";
            } // end if
            if (param == "name")
            {
                param = "item_name";
            } // end if
            if (param == "bigimage")
            {
                param = "item_image";
            } // end if
            return (dataObj[param]);
        }
        else
        {
            return (dataObj[param]);
        } // end else if
    } // End of the function
    function priceByCount(dataObj, target, popupType, optValue)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc5 = 0;
        var _loc6 = "";
        if (popupType == "package")
        {
            _loc5 = optValue.split(",")[3];
        }
        else
        {
            for (var _loc2 = 0; _loc2 < dataObj.length; ++_loc2)
            {
                _loc5 = _loc5 + Number(this.returnItemData(popupType, dataObj[_loc2], "dc")) * Number(this.returnItemData(popupType, dataObj[_loc2], "selectCount"));
            } // end of for
        } // end else if
        _loc6 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1076() + numberSplit.split(String(_loc5)) + this.getDtypeData(dataObj[0].dtype);
        target.price_txt.text = _loc6;
    } // End of the function
    function scroll(popupMovieClip)
    {
        popupMovieClip.scrollbar._visible = true;
        var _loc3 = 15;
        var _loc4 = 140;
        var _loc5 = 56;
        scrollBar = new com.mgame.webMall.util.ScrollBar();
        scrollBar.setScrollTarget(popupMovieClip.listTop);
        scrollBar.setScrollUpButton(popupMovieClip.scrollbar.scrollUpButton);
        scrollBar.setScrollDownButton(popupMovieClip.scrollbar.scrollDownButton);
        scrollBar.setScrollBar(popupMovieClip.scrollbar.bar);
        scrollBar.setMouseWheelStyle(false);
        scrollBar.setMouseWheelEvent(popupMovieClip.listTop);
        scrollBar.start(popupMovieClip.maskMovieClip._height, _loc5, _loc3, _loc4);
    } // End of the function
    function bySelectCompletePopupLoad(itemName, itemCount, itemPrice, itemDate, dtype)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        var _loc3 = this.popupLoad("popup_buyComplete");
        this.setPopupPosition(_loc3);
        this.popupCloseButtonEvent(_loc3);
        this.popupConfirmButtonEvent(_loc3);
        _loc3.listTop.setMask(_loc3.maskMovieClip);
        var _loc8 = 0;
        var _loc4 = 0;
        for (var _loc2 = 0; _loc2 < itemName.length; ++_loc2)
        {
            if (_loc2 == 0)
            {
                _loc4 = _loc3.listTop._height + 1;
            }
            else
            {
                _loc4 = _loc3.listTop["buyListTable" + (_loc2 - 1)]._y + _loc3.listTop["buyListTable" + (_loc2 - 1)]._height + 1;
            } // end else if
            _loc3.listTop.attachMovie("buyListTable", "buyListTable" + _loc2, _loc3.listTop.getNextHighestDepth(), {_x: _loc8, _y: _loc4});
            _loc3.listTop["buyListTable" + _loc2].name_txt.text = itemName[_loc2];
            _loc3.listTop["buyListTable" + _loc2].count_txt.text = itemCount[_loc2] + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1121();
            _loc3.listTop["buyListTable" + _loc2].price_txt.text = numberSplit.split(itemPrice[_loc2]) + this.getDtypeData(dtype);
            _loc3.listTop["buyListTable" + _loc2].regdate_txt.text = itemDate[_loc2];
        } // end of for
        this.scroll(_loc3);
    } // End of the function
    function basketControlPopupLoad(msg)
    {
        var _this = this;
        var popupMovieClip = this.popupLoad("popup_basketControl");
        popupMovieClip.msg_txt.multiline = true;
        popupMovieClip.msg_txt.wordWrap = true;
        popupMovieClip.msg_txt.html = true;
        popupMovieClip.msg_txt.htmlText = msg;
        this.setPopupPosition(popupMovieClip);
        popupMovieClip.basketPageButton.onRelease = function ()
        {
            _this.mainData.mainLoad.deletePage();
            _this.mainData.typeStr = "myBasketPage";
            _this.mainData.mainLoad.pageCheck();
            _this.popupClose(popupMovieClip);
        };
    } // End of the function
    function cashItemCancelPopupLoad(dataObj)
    {
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        textLengthCheck = new com.mgame.webMall.util.TextLengthCheck();
        var _this = this;
        var selectReason = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1238();
        var popupMovieClip = this.popupLoad("popup_cashItemCancel");
        popupMovieClip.message_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_1225;
        popupMovieClip.message_txt.selectable = false;
        var itemNum = dataObj.num;
        var _loc5 = dataObj.dc;
        var _loc13 = mainData.__get__rightMainData().__get__gPoint();
        var _loc14 = mainData.__get__rightMainData().__get__webPoint();
        var _loc4 = dataObj.itemCount;
        var _loc3 = new Date();
        var _loc12 = _loc3.getFullYear();
        var _loc11 = _loc3.getMonth() + 1;
        var _loc10 = _loc3.getDate();
        if (_loc5 == undefined)
        {
            _loc5 = dataObj.price;
        } // end if
        if (_loc4 == undefined)
        {
            _loc4 = "1";
        } // end if
        popupMovieClip.name_txt.text = dataObj.name;
        popupMovieClip.count_txt.text = _loc4 + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_558();
        popupMovieClip.price_txt.text = numberSplit.split(_loc5) + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_559();
        popupMovieClip.regdate_txt.text = _loc12 + "-" + _loc11 + "-" + _loc10;
        popupMovieClip.myMail_txt.text = com.mgame.webMall.main.MainData.__get__LOGIN_uid() + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1236_01() + "(" + com.mgame.webMall.main.MainData.__get__LOGIN_email() + ")" + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1236_02();
        popupMovieClip.confirmButton.onRelease = function ()
        {
            var _loc1 = selectReason;
            if (selectReason == com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1241())
            {
                _loc1 = popupMovieClip.message_txt.text;
            } // end if
            _this.cashItemCancelXml(popupMovieClip, itemNum, _loc1);
        };
        popupMovieClip.emailEditButton.onRelease = function ()
        {
            _this.emailEditPopupLoad(popupMovieClip);
        };
        var _loc2 = this.comboBoxLoad(popupMovieClip, "reasonComboBox", 235, 115, 240, 20, 1);
        _loc2.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1238(), data: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1238()});
        _loc2.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1239(), data: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1239()});
        _loc2.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1240(), data: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1240()});
        _loc2.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1241(), data: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1241()});
        var _loc8 = new Object();
        _loc8.change = function (evt_obj)
        {
            selectReason = evt_obj.target.selectedItem.data;
            if (selectReason == com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1241())
            {
                popupMovieClip.message_txt.text = "";
                Selection.setFocus("popupMovieClip.message_txt");
                popupMovieClip.message_txt.selectable = true;
            }
            else
            {
                popupMovieClip.message_txt.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_1225;
                popupMovieClip.message_txt.selectable = false;
            } // end else if
        };
        _loc2.addEventListener("change", _loc8);
        var byteCheck = null;
        popupMovieClip.message_txt.onChanged = function (my_tf)
        {
            byteCheck = _this.textLengthCheck.FFGetByteLength(my_tf);
            var _loc2 = my_tf.text;
            if (Number(byteCheck.count) >= 100)
            {
                my_tf.text = _loc2.substr(0, Number(byteCheck.strLen) + 1);
            }
            else
            {
                my_tf.text = _loc2;
            } // end else if
            popupMovieClip.byteCheck_txt.text = byteCheck.count + " byte";
        };
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
    } // End of the function
    function emailEditPopupLoad(parentPopup)
    {
        var _this = this;
        var _loc9 = "false";
        mainData.__get__mainStage().mainClose._alpha = 30;
        mainData.__get__mainStage().mainClose._visible = true;
        mainData.__get__mainStage().mainClose.enabled = false;
        mainData.__get__mainStage().mainClose.swapDepths(parentPopup);
        var popupMovieClip = mainData.__get__mainStage().attachMovie("popup_emailEdit", "popup_emailEdit", 2);
        popupMovieClip.closeButton.tabEnabled = false;
        popupMovieClip.id_txt.tabEnabled = false;
        popupMovieClip.editButton.tabEnabled = false;
        popupMovieClip.cancelButton.tabEnabled = false;
        popupMovieClip.id_txt.text = com.mgame.webMall.main.MainData.LOGIN_uid;
        popupMovieClip.editButton.onRelease = function ()
        {
            var _loc1 = popupMovieClip.id_txt.text;
            var _loc4 = popupMovieClip.password_txt.text;
            var _loc3 = popupMovieClip.emailInput01.text;
            var _loc2 = popupMovieClip.emailInput02.text;
            _this.emailFormCheck(_loc1, _loc4, _loc3, _loc2, popupMovieClip, parentPopup);
        };
        var _loc2 = this.comboBoxLoad(popupMovieClip, "emailSelect", 358, 154, 116, 22, 1);
        _loc2.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1293(), data: ""});
        _loc2.addItem({label: "naver.com", data: "naver.com"});
        _loc2.addItem({label: "hanmail.net", data: "hanmail.net"});
        _loc2.addItem({label: "daum.net", data: "daum.net"});
        _loc2.addItem({label: "nate.com", data: "nate.com"});
        _loc2.addItem({label: "empal.com", data: "empal.com"});
        _loc2.addItem({label: "paran.com", data: "paran.com"});
        _loc2.addItem({label: "freechal.com", data: "freechal.com"});
        _loc2.addItem({label: "dreamwiz.com", data: "dreamwiz.com"});
        _loc2.addItem({label: "chol.com", data: "chol.com"});
        _loc2.addItem({label: "chollian.net", data: "chollian.net"});
        _loc2.addItem({label: "hanmir.com", data: "hanmir.com"});
        _loc2.addItem({label: "netian.com", data: "netian.com"});
        _loc2.addItem({label: "lycos.co.kr", data: "lycos.co.kr"});
        _loc2.addItem({label: "paran.com", data: "paran.com"});
        _loc2.addItem({label: com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1308(), data: "true"});
        var _loc3 = new Object();
        _loc3.change = function (evt_obj)
        {
            if (evt_obj.target.selectedItem.data == "true")
            {
                popupMovieClip.emailInput02.enabled = true;
                popupMovieClip.emailInput02.text = "";
            }
            else
            {
                popupMovieClip.emailInput02.enabled = false;
                popupMovieClip.emailInput02.text = evt_obj.target.selectedItem.data;
            } // end else if
        };
        _loc2.addEventListener("change", _loc3);
        this.setPopupPosition(popupMovieClip);
        this.emailPopupClose(popupMovieClip, parentPopup);
    } // End of the function
    function emailFormCheck(id, password, email01, email02, childPopup01, childPopup02)
    {
        if (password == "")
        {
            this.errorMsgPopupLoad(com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1345(), "2depth", childPopup01);
            return;
        } // end if
        if (email01 == "")
        {
            this.errorMsgPopupLoad(com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1350(), "2depth", childPopup01);
            return;
        } // end if
        if (email02 == "")
        {
            this.errorMsgPopupLoad(com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1355(), "2depth", childPopup01);
            return;
        } // end if
        childPopup02.swapDepths(mainData.__get__mainStage().mainClose);
        var _loc3 = email01 + "@" + email02;
        this.emailEditXml(com.mgame.webMall.main.MainData.__get__LOGIN_nid(), id, password, _loc3, childPopup01, childPopup02);
    } // End of the function
    function emailEditComplete(ret, msg, childPopup01, childPopup02)
    {
        var _this = this;
        childPopup01.removeMovieClip();
        childPopup02.removeMovieClip();
        var popupMovieClip = this.popupLoad("confirmMsgPopup");
        popupMovieClip.msg_txt.html = true;
        popupMovieClip.msg_txt.multiline = true;
        popupMovieClip.msg_txt.wordWrap = true;
        popupMovieClip.msg_txt.htmlText = msg;
        popupMovieClip.confirmButton.onRelease = function ()
        {
            _this.popupClose(popupMovieClip);
            _this.mainData.mainLoad.login();
        };
        popupMovieClip.closeButton.onRelease = function ()
        {
            _this.popupClose(popupMovieClip);
            _this.mainData.mainLoad.login();
        };
        this.setPopupPosition(popupMovieClip);
    } // End of the function
    function emailPopupClose(popupMovieClip, parentPopup)
    {
        var _this = this;
        popupMovieClip.cancelButton.onRelease = popupMovieClip.closeButton.onRelease = function ()
        {
            popupMovieClip.removeMovieClip();
            parentPopup.swapDepths(_this.mainData.mainStage.mainClose);
        };
    } // End of the function
    function cashItemCancelComplete(deletePopup, ret, msg)
    {
        var _this = this;
        deletePopup.removeMovieClip();
        var popupMovieClip = this.popupLoad("confirmMsgPopup");
        popupMovieClip.msg_txt.html = true;
        popupMovieClip.msg_txt.multiline = true;
        popupMovieClip.msg_txt.wordWrap = true;
        popupMovieClip.msg_txt.htmlText = msg;
        popupMovieClip.confirmButton.onRelease = function ()
        {
            _this.popupClose(popupMovieClip);
            _this.mainData.mainLoad.reLoad("myStorePage");
        };
        popupMovieClip.closeButton.onRelease = function ()
        {
            _this.popupClose(popupMovieClip);
            _this.mainData.mainLoad.reLoad("myStorePage");
        };
        this.setPopupPosition(popupMovieClip);
    } // End of the function
    function cashItemSubmitPopupLoad(dataObj)
    {
        var _this = this;
        var popupMovieClip = this.popupLoad("cashItemCheckPopup");
        popupMovieClip.msg_txt.html = true;
        popupMovieClip.msg_txt.multiline = true;
        popupMovieClip.msg_txt.htmlText = "<p align=\'center\'>" + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1211() + "</p>";
        popupMovieClip.confirmButton.onRelease = function ()
        {
            _this.cashItemSubmitXml(popupMovieClip, String(dataObj));
        };
        this.setPopupPosition(popupMovieClip);
        this.popupCloseButtonEvent(popupMovieClip);
    } // End of the function
    function cashItemSubmitComplete(deletePopup)
    {
    } // End of the function
    function errorMsgPopupLoad(errorMsg, type, childPopup)
    {
        var _this = this;
        var popupMovieClip;
        if (type == "open")
        {
            if (mainData.__get__mainStage().mainClose.getDepth() > childPopup.getDepth())
            {
                mainData.__get__mainStage().mainClose.swapDepths(childPopup);
            } // end if
            popupMovieClip = mainData.__get__mainStage().attachMovie("errorMsgPopup", "errorMsgPopup", 2);
            popupMovieClip.closeButton.onRelease = popupMovieClip.cancelButton.onRelease = function ()
            {
                _this.msgPopupButtonEventCheck(type, popupMovieClip, childPopup);
            };
        }
        else if (type == "charging")
        {
            popupMovieClip = mainData.__get__mainStage().attachMovie("chargeMsgPopup", "errorMsgPopup", 2);
            popupMovieClip.chargeButton.onRelease = function ()
            {
                fscommand("gameCash");
                _this.msgPopupButtonEventCheck(type, popupMovieClip, childPopup);
            };
            popupMovieClip.closeButton.onRelease = popupMovieClip.cancelButton.onRelease = function ()
            {
                _this.msgPopupButtonEventCheck(type, popupMovieClip, childPopup);
            };
        }
        else if (type == "2depth")
        {
            popupMovieClip = mainData.__get__mainStage().attachMovie("errorMsgPopup", "errorMsgPopup", 3);
            mainData.__get__mainStage().mainClose.swapDepths(childPopup);
            popupMovieClip.cancelButton.onRelease = popupMovieClip.closeButton.onRelease = function ()
            {
                childPopup.settleButton.enabled = true;
                childPopup.cancelButton.enabled = true;
                childPopup.closeButton.enabled = true;
                childPopup.swapDepths(_this.mainData.mainStage.mainClose);
                popupMovieClip.removeMovieClip();
            };
        }
        else
        {
            mainData.__get__mainStage().mainClose._alpha = 30;
            mainData.__get__mainStage().mainClose._visible = true;
            mainData.__get__mainStage().mainClose.enabled = false;
            mainData.__get__mainStage().mainClose.onRelease = function ()
            {
            };
            popupMovieClip = this.popupLoad("errorMsgPopup");
            this.popupCloseButtonEvent(popupMovieClip);
        } // end else if
        this.setPopupPosition(popupMovieClip);
        popupMovieClip.msg_txt.html = true;
        popupMovieClip.msg_txt.multiline = true;
        popupMovieClip.msg_txt.wordWrap = true;
        popupMovieClip.msg_txt.htmlText = errorMsg;
    } // End of the function
    function msgPopupButtonEventCheck(type, popupMovieClip, childPopup)
    {
        if (childPopup.c_noticeButton != undefined)
        {
            childPopup.c_noticeButton.enabled = true;
        } // end if
        if (childPopup.buyButton != undefined)
        {
            childPopup.buyButton.enabled = true;
        } // end if
        if (childPopup.giftButton != undefined)
        {
            childPopup.giftButton.enabled = true;
        } // end if
        if (childPopup.cartButton != undefined)
        {
            childPopup.cartButton.enabled = true;
        } // end if
        childPopup.settleButton.enabled = true;
        childPopup.cancelButton.enabled = true;
        childPopup.closeButton.enabled = true;
        popupMovieClip.removeMovieClip();
    } // End of the function
    function loginErrorPopupLoad(msg)
    {
        var _loc2 = this.popupLoad("confirmMsgPopup");
        _loc2.msg_txt.html = true;
        _loc2.msg_txt.multiline = true;
        _loc2.msg_txt.wordWrap = true;
        _loc2.msg_txt.htmlText = msg;
        this.setPopupPosition(_loc2);
        this.popupCloseButtonEvent(_loc2);
        this.popupConfirmButtonEvent(_loc2, "loginError");
    } // End of the function
    function itemPageLoginError(msg, mainStage)
    {
        var _loc2 = mainStage.attachMovie("errorMsgPopup", "errorMsgPopup", 1);
        this.popupCloseButtonEvent(_loc2);
        this.setPopupPosition(_loc2);
        _loc2.msg_txt.html = true;
        _loc2.msg_txt.multiline = true;
        _loc2.msg_txt.wordWrap = true;
        _loc2.msg_txt.htmlText = msg;
    } // End of the function
    function eventCashPopup(mainStage)
    {
        mainData.__get__mainStage().mainClose._alpha = 30;
        mainData.__get__mainStage().mainClose._visible = true;
        mainData.__get__mainStage().mainClose.enabled = false;
        mainData.__get__mainStage().mainClose.onRelease = function ()
        {
        };
        var _loc2 = mainStage.attachMovie("eventGiftCash", "eventGiftCash", 1);
        this.popupCloseButtonEvent(_loc2);
        this.setPopupPosition(_loc2);
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
            trace ("popupItemImageError");
        };
    } // End of the function
    function popupConfirmButtonEvent(popupMovieClip, errorType)
    {
        var _this = this;
        popupMovieClip.confirmButton.onRelease = function ()
        {
            _this.goMainPage(popupMovieClip, errorType);
        };
    } // End of the function
    function popupCloseButtonEvent(popupMovieClip)
    {
        var _this = this;
        popupMovieClip.closeButton.onRelease = function ()
        {
            _this.popupClose(popupMovieClip);
        };
        popupMovieClip.cancelButton.onRelease = function ()
        {
            _this.popupClose(popupMovieClip);
        };
    } // End of the function
    function setPopupPosition(popupMovieClip)
    {
        popupMovieClip._x = stageWidth / 2 - popupMovieClip._width / 2;
        popupMovieClip._y = stageHeight / 2 - popupMovieClip._height / 2;
    } // End of the function
    function popupLoad(popupName)
    {
        var _loc2 = mainData.__get__mainStage().attachMovie(popupName, popupName, 1);
        return (_loc2);
    } // End of the function
    function popupClose(popupMovieClip)
    {
        delete this.scrollBar;
        com.mgame.webMall.main.MainData.__set__wheelValue(true);
        com.mgame.webMall.main.MainData.__get__currentScrollBarFunc().setMouseWheelStyle(true);
        com.mgame.webMall.main.MainData.__get__currentScrollBarFunc().setMouseWheelEvent(com.mgame.webMall.main.MainData.__get__currentScrollTarget());
        popupMovieClip.removeMovieClip();
        mainData.__get__mainStage().mainClose._alpha = 0;
        mainData.__get__mainStage().mainClose._visible = false;
        if (com.mgame.webMall.main.MainData.__get__PARAMETER_cmd() != "settleShop")
        {
            com.mgame.webMall.main.MainData.__set__PARAMETER_cmd(null);
        } // end if
        this.clearTimer();
    } // End of the function
    function comboBoxLoad(target, name, x, y, width, height, depth)
    {
        target.createClassObject(mx.controls.ComboBox, name, depth);
        target[name].move(x, y);
        target[name].setSize(width, height);
        return (target[name]);
    } // End of the function
    function xmlLoad(popupMovieClip, obj, param, cmd, itemCount, cashType, serialNo, targetServer, targetID, message, price, dtype)
    {
        popupMovieClip.removeMovieClip();
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.setData(this, obj, param, cmd, itemCount, cashType, serialNo, targetServer, targetID, message, price, dtype);
    } // End of the function
    function settleCloseXmlLoad(popupMovieClip, num)
    {
        popupMovieClip.removeMovieClip();
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.settleCloseStart(num, this);
    } // End of the function
    function couponSerialXmlLoad(popupMovieClip, serialObj)
    {
        popupMovieClip.removeMovieClip();
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.couponRegisterStart(serialObj, this);
    } // End of the function
    function basketControlXmlLoad(dataObj)
    {
        var _loc2 = 1;
        var _loc3 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc3.basketControlStart(dataObj, _loc2, this);
    } // End of the function
    function basketControlEditXml(dataObj)
    {
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.basketControlEdit(dataObj.goodsno, dataObj.count, this);
    } // End of the function
    function basketControlDelXml(dataObj)
    {
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.basketControlDelete(dataObj, this);
    } // End of the function
    function userCheckStart(userID, popupMovieClip)
    {
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.userCheck(userID, this, popupMovieClip);
    } // End of the function
    function jorgiStart(goodsno, targetChar, msg)
    {
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.jorgiStart(goodsno, targetChar, msg, this);
    } // End of the function
    function cashItemCancelXml(popupMovieClip, itemNum, msg)
    {
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.cashItemCancelStart(itemNum, msg, this, popupMovieClip);
    } // End of the function
    function cashItemSubmitXml(popupMovieClip, itemNum)
    {
        var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
        _loc2.cashItemSubmitStart(itemNum, this, popupMovieClip);
    } // End of the function


function emailEditXml(nid, id, password, newEmail, childPopup01, childPopup02)
{
    var _loc2 = new com.mgame.webMall.main.MainCommonPopupXml();
    _loc2.myEmailEditStart(nid, id, password, newEmail, this, childPopup01, childPopup02);
} // End of the function
function goMainPage(popupMovieClip, errorType)
{
    this.popupClose(popupMovieClip);
    if (errorType == "loginError")
    {
        mainData.__get__mainLoad().loginReLoad();
    }
    else
    {
        mainData.__get__mainLoad().reLoad();
    } // end else if
} // End of the function
function previewCheck(dataObj)
{
    if (com.mgame.webMall.main.MainData.__get__previewPageType() == true)
    {
        previewItemXml = new com.mgame.webMall.main.topMain.PreviewItemXml();
        previewItemXml.viewStart(dataObj.goodsno);
    } // end if
} // End of the function
function pcRoomCheck()
{
    var _loc2 = com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1405();
    this.errorMsgPopupLoad(_loc2, "close");
} // End of the function
function getDtypeData(dtype)
{
	var _ret = "";
	if( dtype == 3 || dtype == 4 )
		_ret = "NPts";
	return (_ret);
	
}
function returnCashType(dtype)
{
    var _loc1 = "";
    if (dtype == "6")
    {
        _loc1 = "GIFTCARD";
    }
    else if (dtype == "8")
    {
        _loc1 = "MILAGE";
    }
    else
    {
        _loc1 = "MCASH";
    } // end else if
    return (_loc1);
} // End of the function
function limitTime(sdate, edate, target, limit_type)
{
    var _loc4 = sdate.split("-");
    var _loc2 = edate.split("-");
    var _loc18 = Number(String(_loc4[2]).split(" ")[0]);
    var _loc19 = Number(String(_loc2[2]).split(" ")[0]);
    var _loc20 = String(_loc4[2]).split(" ")[1];
    var _loc7 = _loc20.split(":");
    var _loc16 = String(_loc2[2]).split(" ")[1];
    var _loc10 = _loc16.split(":");
    var _loc13 = new Date();
    var _loc15 = new Date(_loc4[0], Number(_loc4[1] - 1), _loc18, _loc7[0], _loc7[1], _loc7[2]);
    var _loc17 = new Date(_loc2[0], Number(_loc2[1] - 1), _loc19, _loc10[0], _loc10[1], _loc10[2]);
    if (_loc15.getTime() > _loc13.getTime())
    {
        itemDateChech = false;
        target.limit_date.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_1454;
        return;
    } // end if
    var _loc3 = _loc17 - _loc13;
    _loc3 = _loc3 / 1000;
    var _loc5 = null;
    var _loc9 = null;
    var _loc12 = null;
    var _loc8 = null;
    var _loc11 = null;
    var _loc6 = null;
    _loc5 = Math.floor(_loc3 / 86400);
    _loc9 = _loc3 % 86400;
    _loc12 = Math.floor(_loc9 / 3600);
    _loc8 = _loc9 % 3600;
    _loc11 = Math.floor(_loc8 / 60);
    _loc6 = Math.floor(_loc8 % 60);
    if (target == null)
    {
        this.timer(_loc5, _loc12, _loc11, _loc6, target, limit_type);
    }
    else
    {
        timerNum = setInterval(this, "timer", 150, _loc5, _loc12, _loc11, _loc6, target, limit_type);
    } // end else if
} // End of the function
function timer(day, hour, min, sec, target, limit_type)
{
    clearInterval(timerNum);
    if (sec <= 0 && min <= 0 && hour <= 0 && day <= 0)
    {
        dateItemLimitCheck = false;
        target.limit_date.text = com.mgame.webMall.text.MainPackageTextDefine.MainCommonPopup_1490;
        return;
    }
    else
    {
        target.limit_date.text = day + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1497_01() + hour + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1497_02() + min + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1497_03() + sec + com.mgame.webMall.text.MainPackageTextDefine.__get__MainCommonPopup_1497_04();
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
    timerNum = setInterval(this, "timer", 1000, day, hour, min, sec, target, limit_type);
} // End of the function
function clearTimer()
{
    clearInterval(timerNum);
} // End of the function
function get targetCharCheckValue()
{
    return (_targetCharCheckValue);
} // End of the function
function set targetCharCheckValue(value)
{
    _targetCharCheckValue = value;
    //return (this.targetCharCheckValue());
    null;
} // End of the function
function get targetChar()
{
    return (_targetChar);
} // End of the function
function set targetChar(value)
{
    _targetChar = value;
    //return (this.targetChar());
    null;
} // End of the function
var mainData = null;
var numberSplit = null;
var textLengthCheck = null;
var previewItemXml = null;
var scrollBar = null;
var stageWidth = 1000;
var stageHeight = 714;
var _targetCharCheckValue = false;
var _targetChar = null;
var timerNum = 0;
var itemDateChech = true;
var dateItemLimitCheck = true;
}