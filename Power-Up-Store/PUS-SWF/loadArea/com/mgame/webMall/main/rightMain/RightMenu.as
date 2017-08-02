class com.mgame.webMall.main.rightMain.RightMenu
{
    var index;
    function RightMenu()
    {
    } // End of the function
    function load(mainData)
    {
        this.mainData = mainData;
        rightMainData = mainData.rightMainData;
        previewItemXml = new com.mgame.webMall.main.topMain.PreviewItemXml();
        this.cashInvenCheckStart();
        this.buttonEvent();
    } // End of the function
    function buttonEvent()
    {
        var _this = this;
        for (var _loc2 = 1; _loc2 < 5; ++_loc2)
        {
            rightMainData.__get__rightMain()["over0" + _loc2].index = _loc2;
            rightMainData.__get__rightMain()["over0" + _loc2].onRollOver = function ()
            {
                _this.buttonOverEvent(index);
            };
            rightMainData.__get__rightMain()["over0" + _loc2].onRollOut = function ()
            {
                _this.buttonOutEvent();
            };
            rightMainData.__get__rightMain()["over0" + _loc2].onRelease = function ()
            {
                _this.buttonAction(index);
            };
        } // end of for
        rightMainData.__get__rightMain().gameCashButton.onRelease = function ()
        {
            fscommand("gameCash");
        };
        rightMainData.__get__rightMain().couponButton.onRelease = function ()
        {
            _this.mainData.typeStr = "couponPage";
            _this.selectPageMove();
        };
        rightMainData.__get__rightMain().settleShopPageMove.onRelease = function ()
        {
            var _loc1 = com.mgame.webMall.text.MainPackageTextDefine.__get__RightMenu_69();
            com.mgame.webMall.util.CommonPopup.alert(_loc1);
        };
        rightMainData.__get__rightMain().packagePageMove.onRelease = function ()
        {
            _this.mainData.typeStr = "packagePage";
            _this.selectPageMove();
        };
        rightMainData.__get__rightMain().eventShopPageMove.onRelease = function ()
        {
            _this.mainData.typeStr = "eventShopPage";
            _this.selectPageMove();
        };
        rightMainData.__get__rightMain().cNoticeMove.onRelease = function ()
        {
            com.mgame.webMall.util.CommonPopup.popupStart("cNotice");
        };
    } // End of the function
    function buttonAction(index)
    {
        if (index == 1)
        {
            mainData.__set__typeStr("myStorePage");
            this.selectPageMove();
            if (cashInvenButtonType != "default")
            {
                this.cashInvenButtonStyle("default");
                com.mgame.webMall.util.CommonPopup.rightMenu = this;
            } // end if
        }
        else if (index == 2)
        {
            mainData.__set__typeStr("recomShopPage");
            this.selectPageMove();
        }
        else if (index == 3)
        {
            mainData.__set__typeStr("myBasketPage");
            this.selectPageMove();
        }
        else if (index == 4)
        {
            com.mgame.webMall.util.CommonPopup.popupStart("inven_check", "");
        } // end else if
    } // End of the function
    function selectPageMove()
    {
        previewItemXml.viewClose();
        mainData.__get__mainLoad().deletePage();
        mainData.__get__mainLoad().pageCheck();
    } // End of the function
    function buttonOverEvent(index)
    {
        for (var _loc2 = 1; _loc2 < 5; ++_loc2)
        {
            rightMainData.__get__rightMain()["over0" + _loc2]._alpha = 0;
        } // end of for
        rightMainData.__get__rightMain()["over0" + index]._alpha = 30;
    } // End of the function
    function buttonOutEvent()
    {
        for (var _loc2 = 1; _loc2 < 5; ++_loc2)
        {
            rightMainData.__get__rightMain()["over0" + _loc2]._alpha = 0;
        } // end of for
    } // End of the function
    function cashInvenCheckStart()
    {
        cashInvenXml = new com.mgame.webMall.main.rightMain.CashInvenXml();
        cashInvenXml.load(this);
    } // End of the function
    function cashInvenButtonStyle(type)
    {
        cashInvenButtonType = type;
        if (type == "flashMode")
        {
            this.cashInvenButtonFlashMode();
        }
        else
        {
            this.intervalClear();
            rightMainData.__get__rightMain().cashInvenButton.gotoAndStop(1);
            rightMainData.__get__rightMain().cashInvenButton.enabled = false;
        } // end else if
    } // End of the function
    function cashInvenButtonFlashMode()
    {
        intervalNum = setInterval(intervalStart, 700, rightMainData);
    } // End of the function
    function intervalStart(rightMainData)
    {
        this.intervalClear();
        if (rightMainData.__get__rightMain().cashInvenButton._currentframe == 1)
        {
            rightMainData.__get__rightMain().cashInvenButton.gotoAndStop(2);
        }
        else
        {
            rightMainData.__get__rightMain().cashInvenButton.gotoAndStop(1);
        } // end else if
        this.cashInvenButtonFlashMode();
    } // End of the function
    function intervalClear()
    {
        clearInterval(intervalNum);
    } // End of the function
    var rightMainData = null;
    var mainData = null;
    var previewItemXml = null;
    var cashInvenXml = null;
    var intervalNum = 0;
    var cashInvenButtonType = "default";
} // End of Class
