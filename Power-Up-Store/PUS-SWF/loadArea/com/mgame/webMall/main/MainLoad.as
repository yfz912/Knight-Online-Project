class com.mgame.webMall.main.MainLoad
{
    function MainLoad()
    {
    } // End of the function
    function login()
    {
        var _loc2 = new com.mgame.webMall.main.LoginXml();
        _loc2.load(mainData);
    } // End of the function
    function loadType(mainStage, typeStr)
    {
        var _loc2 = this;
        mainData = new com.mgame.webMall.main.MainData();
        returnMainData = mainData;
        mainData.__set__mainLoad(this);
        mainData.__set__mainStage(mainStage);
        mainData.__set__typeStr(typeStr);
        mainData.__set__mainLoadArea(mainStage.mainLoadArea);
    } // End of the function
    function stageLoadStart()
    {
        this.mainTodayPopupCookie();
        this.todayItemCookie();
        this.optionItemLoad();
        this.ticketListLoad();
        this.loadAreaDefaultPosition();
        this.rightMainLoad();
        this.topMainLoad();
        this.pageCheck();
    } // End of the function
    function reLoad()
    {
        mainData.__set__typeStr("mainPage");
        this.rightMainLoad();
        this.pageCheck();
    } // End of the function
    function loginReLoad()
    {
        watchObject.webMall = com.mgame.webMall.main.MainData.LOGIN_auckey;
    } // End of the function
    function serviceCheck()
    {
        var _this = this;
        var xmlLoader = new XML();
        xmlLoader.ignoreWhite = true;
        xmlLoader.onLoad = function ()
        {
            if (xmlLoader.firstChild.firstChild.firstChild.nodeValue == "error")
            {
                var _loc2 = xmlLoader.firstChild.firstChild.nextSibling.firstChild.nodeValue;
                var _loc1 = new com.mgame.webMall.main.MainCommonPopup();
                _loc1.setData(_this.mainData);
                _loc1.itemPageLoginError(_loc2, _this.mainData.mainStage);
            }
            else if (xmlLoader.firstChild.firstChild.firstChild.nodeValue == "1")
            {
                _this.stageLoadStart();
            }
            else if (xmlLoader.firstChild.firstChild.firstChild.nodeValue == "2")
            {
                _loc1 = new com.mgame.webMall.main.MainCommonPopup();
                _loc1.setData(_this.mainData);
                _loc1.eventCashPopup(_this.mainData.mainStage);
                _this.stageLoadStart();
            }
            else
            {
                _this.mainData.mainStage.attachMovie("checkPage", "checkPage", 1);
            } // end else if
        };
        var _loc2 = new LoadVars();
        _loc2.cmd = "checking";
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.sendAndLoad(com.mgame.webMall.main.CommonDataUrl.__get__serviceCheckURL(), xmlLoader, "post");
    } // End of the function
    function setWatch(obj)
    {
        var _this = this;
        watchObject = obj;
        watchObject.webMall = "";
        var _loc2 = function (prop, oldval, newval, userData)
        {
            com.mgame.webMall.main.MainData.__set__mgmac(newval);
            _this.mgmacSplit();
            _this.login();
        };
        watchObject.watch("webMall", _loc2);
        flash.external.ExternalInterface.addCallback("watchEventCall", null, webVersionCall);
    } // End of the function
    function webVersionCall(value)
    {
        _root.myObject.webMall = value;
    } // End of the function
    function mgmacSplit()
    {
        var _loc1 = com.mgame.webMall.main.MainData.__get__mgmac().split("\x0b");
        _loc1 = String(_loc1[5]).split(",");
        com.mgame.webMall.main.MainData.__set__pcRoomCheck(_loc1[7]);
        com.mgame.webMall.main.MainData.__set__mgChar(_loc1[11]);
        com.mgame.webMall.main.MainData.__set__mgLevel(_loc1[12]);
    } // End of the function
    function loadAreaDefaultPosition()
    {
        var _loc2 = "default";
        if (_loc2 == "default")
        {
            mainData.__get__mainLoadArea()._x = mainData.mainLoadAreaDefaultTypeX;
            mainData.__get__mainLoadArea()._y = mainData.mainLoadAreaDefaultTypeY;
            mainData.__get__mainStage().rightMain._x = mainData.rightMainDefaultTypeX;
            mainData.__get__mainStage().rightMain._y = mainData.rightMainDefaultTypeY;
            mainData.__get__mainStage().searchMenu._x = mainData.searchMenuDefaultTypeX;
            mainData.__get__mainStage().searchMenu._y = mainData.searchMenuDefaultTypeY;
            mainData.__get__mainStage().mainLogo._x = mainData.mainLogoDefaultTypeX;
            mainData.__get__mainStage().mainLogo._y = mainData.mainLogoDefaultTypeY;
        }
        else
        {
            mainData.__get__mainLoadArea()._x = mainData.mainLoadAreaChangeTypeX;
            mainData.__get__mainLoadArea()._y = mainData.mainLoadAreaChangeTypeY;
            mainData.__get__mainStage().rightMain._x = mainData.rightMainChangeTypeX;
            mainData.__get__mainStage().rightMain._y = mainData.rightMainChangeTypeY;
            mainData.__get__mainStage().searchMenu._x = mainData.searchMenuChangeTypeX;
            mainData.__get__mainStage().searchMenu._y = mainData.searchMenuChangeTypeY;
            mainData.__get__mainStage().mainLogo._x = mainData.mainLogoChangeTypeX;
            mainData.__get__mainStage().mainLogo._y = mainData.mainLogoChangeTypeY;
        } // end else if
    } // End of the function
    function mainImagePopupLoad()
    {
        var _loc2 = new com.mgame.webMall.main.MainImagePopupXml();
        _loc2.load(mainData);
    } // End of the function
    function optionItemLoad()
    {
        var _loc1 = new com.mgame.webMall.main.OptionItemXml();
        _loc1.load();
    } // End of the function
    function ticketListLoad()
    {
        var _loc1 = new com.mgame.webMall.main.TicketListXml();
        _loc1.load();
    } // End of the function
    function rightMainLoad()
    {
        var _loc3 = new com.mgame.webMall.main.rightMain.CashPage();
        var _loc4 = new com.mgame.webMall.main.rightMain.RightMenu();
        var _loc2 = new com.mgame.webMall.main.rightMain.TodayItemPage();
        _loc3.cashPageLoad(mainData);
        _loc4.load(mainData);
        _loc2.todayItemPageLoad(mainData);
    } // End of the function
    function topMainLoad()
    {
        var _loc2 = new com.mgame.webMall.main.topMain.TopMenu();
        var _loc3 = new com.mgame.webMall.main.topMain.SearchMenu();
        _loc2.load(this, mainData);
        _loc3.load(this, mainData);
    } // End of the function
    function pageCheck()
    {
        this.loadPage(mainData.__get__typeStr());
    } // End of the function
    function mainTodayPopupCookie()
    {
        var _loc3 = new Date();
        var _loc2 = _loc3.getDate();
        if (com.mgame.webMall.main.MainData.__get__mainTodayPopupImageCookie() == null)
        {
            com.mgame.webMall.main.MainData.__set__mainTodayPopupImageCookie(SharedObject.getLocal("mgame_mainTodayPopupImage_" + com.mgame.webMall.main.MainData.__get__LOGIN_nid()));
        } // end if
        if (com.mgame.webMall.main.MainData.__get__mainTodayPopupImageCookie().data.myDate == undefined)
        {
            com.mgame.webMall.main.MainData.__get__mainTodayPopupImageCookie().data.myDate = _loc2;
        } // end if
        if (com.mgame.webMall.main.MainData.__get__mainTodayPopupImageCookie().data.myDate != _loc2)
        {
            com.mgame.webMall.main.MainData.__get__mainTodayPopupImageCookie().clear();
            com.mgame.webMall.main.MainData.__get__mainTodayPopupImageCookie().data.myDate = _loc2;
        } // end if
        if (com.mgame.webMall.main.MainData.__get__mainTodayPopupImageCookie().data.viewCheck != "0")
        {
            this.mainImagePopupLoad();
        } // end if
    } // End of the function
    function todayItemCookie()
    {
        var _loc2 = new Date();
        var _loc1 = _loc2.getDate();
        if (com.mgame.webMall.main.MainData.__get__todayItemCookie() == null)
        {
            com.mgame.webMall.main.MainData.__set__todayItemCookie(SharedObject.getLocal("mgame_today_" + com.mgame.webMall.main.MainData.__get__LOGIN_nid()));
        } // end if
        if (com.mgame.webMall.main.MainData.__get__todayItemCookie().data.myDate == undefined)
        {
            com.mgame.webMall.main.MainData.__get__todayItemCookie().data.myDate = _loc1;
        } // end if
        if (com.mgame.webMall.main.MainData.__get__todayItemCookie().data.myDate != _loc1)
        {
            com.mgame.webMall.main.MainData.__get__todayItemCookie().clear();
            com.mgame.webMall.main.MainData.__get__todayItemCookie().data.myDate = _loc1;
        } // end if
    } // End of the function
    function loadPage(setName)
    {
        var _loc6 = this;
        this.topCategoryMenuReset();
        var _loc4 = mainData.returnPageURL(setName);
        var _loc2 = new MovieClipLoader();
        mainData.__set__pageLoader(_loc2);
        if (setName == "mainPage" || setName == "commonStore")
        {
            mainData.__get__mainStage().mainClose._alpha = 30;
            mainData.__get__mainStage().mainClose._visible = true;
            mainData.__get__mainStage().mainClose.useHandCursor = false;
            mainData.__get__mainStage().mainClose.onRelease = function ()
            {
            };
        } // end if
        var _loc3 = new Object();
        _loc2.addListener(_loc3);
        _loc2.loadClip(_loc4, mainData.__get__mainLoadArea());
    } // End of the function
    function topCategoryMenuReset()
    {
        if (mainData.__get__selectMenuType() != "category")
        {
            for (var _loc2 = 0; _loc2 < 8; ++_loc2)
            {
                mainData.__get__mainStage().searchMenu["categoryMovieClip" + _loc2].bg._alpha = 0;
                mainData.__get__mainStage().searchMenu["categoryMovieClip" + _loc2].name_txt.textColor = "0xFFFFFF";
            } // end of for
        } // end if
        mainData.__set__selectMenuType(null);
        mainData.__get__mainStage().searchMenu.searchInput.text = "";
    } // End of the function
    function deletePage()
    {
        mainData.__get__pageLoader().unloadClip(mainData.__get__mainLoadArea());
    } // End of the function
    static function getMainData()
    {
        return (com.mgame.webMall.main.MainLoad.returnMainData);
    } // End of the function
    var mainData = null;
    static var returnMainData = null;
    var watchObject = null;
} // End of Class
