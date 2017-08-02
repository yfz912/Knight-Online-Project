class com.mgame.webMall.main.MainImagePopupXml
{
    function MainImagePopupXml()
    {
    } // End of the function
    function load(mainData)
    {
        this.mainData = mainData;
        var _this = this;
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        var _loc3 = new LoadVars();
        _loc2.onLoad = function ()
        {
            _this.onLoad(this);
        };
        _loc3.cmd = "checkPopup";
        _loc3.sendAndLoad(loadURL, _loc2, "post");
    } // End of the function
    function onLoad(xmlData)
    {
        var _loc6 = xmlData.firstChild.firstChild.firstChild.nodeValue;
        if (_loc6 == "1")
        {
            var _loc2 = xmlData.firstChild.firstChild.nextSibling.childNodes;
            var _loc3 = _loc2[3].firstChild.nodeValue;
            var _loc4 = _loc2[4].firstChild.nodeValue;
            var _loc5 = _loc2[5].firstChild.nodeValue;
            this.imageLoad(_loc3, _loc4, _loc5);
        }
        else
        {
            this.xmlLoadError();
        } // end else if
    } // End of the function
    function imageLoad(imageURL, width, height)
    {
        var _loc2 = mainData.__get__mainStage().attachMovie("popup_mainBanner", "popup_mainBanner", 1);
        _loc2.imageArea._width = Number(width);
        _loc2.imageArea._height = Number(height);
        this.setPopupPosition(_loc2);
        this.buttonEvent(_loc2);
        imageURL = com.mgame.webMall.main.CommonDataUrl.__get__mainImageURL() + imageURL;
        var _loc3 = new Object();
        var _loc4 = new MovieClipLoader();
        _loc4.addListener(_loc3);
        _loc4.loadClip(imageURL, _loc2.imageArea);
        _loc3.onLoadInit = function (target)
        {
            target._x = 1;
            target._y = 1;
            target._width = Number(width) - 4;
            target._height = Number(height) - 4;
        };
        _loc3.onLoadError = function (target_mc, errorCode, httpStatus)
        {
            trace ("mainPopupImage Load Error");
        };
    } // End of the function
    function setPopupPosition(popupMovieClip)
    {
        popupMovieClip.closeButton._x = popupMovieClip.imageArea._width - popupMovieClip.closeButton._width;
        popupMovieClip.closeButton._y = -20;
        popupMovieClip.todayCloseButton._x = popupMovieClip.imageArea._width - popupMovieClip.todayCloseButton._width;
        popupMovieClip.todayCloseButton._y = popupMovieClip.imageArea._height;
        popupMovieClip.bg._width = popupMovieClip.imageArea._width;
        popupMovieClip.bg._height = popupMovieClip.imageArea._height;
        popupMovieClip._x = stageWidth / 2 - popupMovieClip._width / 2;
        popupMovieClip._y = stageHeight / 2 - popupMovieClip._height / 2;
        mainData.__get__mainStage().mainClose._alpha = 30;
        mainData.__get__mainStage().mainClose._visible = true;
        mainData.__get__mainStage().mainClose.onRelease = function ()
        {
        };
    } // End of the function
    function buttonEvent(popupMovieClip)
    {
        var _this = this;
        popupMovieClip.todayCloseButton.onRelease = function ()
        {
            _this.mainData.mainStage.mainClose._alpha = 0;
            _this.mainData.mainStage.mainClose._visible = false;
            popupMovieClip.removeMovieClip();
            com.mgame.webMall.main.MainData.__get__mainTodayPopupImageCookie().data.viewCheck = "0";
        };
        popupMovieClip.closeButton.onRelease = function ()
        {
            _this.mainData.mainStage.mainClose._alpha = 0;
            _this.mainData.mainStage.mainClose._visible = false;
            popupMovieClip.removeMovieClip();
        };
    } // End of the function
    function xmlLoadError()
    {
        trace ("메인 팝업이미지 xml error");
    } // End of the function
    static var loadURL = com.mgame.webMall.main.CommonDataUrl.__get__mainImagePopupURL();
    var stageWidth = 1000;
    var stageHeight = 714;
    var mainData = null;
} // End of Class
