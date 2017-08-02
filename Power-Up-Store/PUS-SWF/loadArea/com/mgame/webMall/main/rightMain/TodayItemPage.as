class com.mgame.webMall.main.rightMain.TodayItemPage
{
    function TodayItemPage()
    {
    } // End of the function
    function todayItemPageLoad(mainData)
    {
        rightMainData = mainData.rightMainData;
        this.xmlLoad();
    } // End of the function
    function xmlLoad()
    {
        var _loc2 = new com.mgame.webMall.main.rightMain.TodayItemXml();
        _loc2.load(this, rightMainData);
    } // End of the function
    function init()
    {
        returnXmlData = new com.mgame.webMall.util.ReturnXmlData();
        numberSplit = new com.mgame.webMall.util.NumberSplit();
        textLengthCheck = new com.mgame.webMall.util.TextLengthCheck();
        this.makeList(0);
        this.buttonEvent();
    } // End of the function
	function getDtypeData(dtype)
	{
		var _ret = "";
		if( dtype == 3 || dtype == 4 )
			_ret = "NPts";
		return (_ret);
		
	}
    function makeList(idx)
    {
        rightMainData.__get__rightMain().itemName_txt.text = textLengthCheck.checkTextValue(returnXmlData.setArrayData(rightMainData.__get__todayItemData(), idx, "todayItem").name, 17);
        if (rightMainData.__get__rightMain().itemName_txt.maxscroll > 1)
        {
            rightMainData.__get__rightMain().itemName_txt._y = 279;
            rightMainData.__get__rightMain().itemName_txt._height = 40;
        } // end if
        if (returnXmlData.setArrayData(rightMainData.__get__todayItemData(), idx, "todayItem").item_type == "1")
        {
            rightMainData.__get__rightMain().itemPrice_txt.text = com.mgame.webMall.text.MainPackageTextDefine.TodayItemPage_56;
        }
        else
        {
            rightMainData.__get__rightMain().itemPrice_txt.text = numberSplit.split(returnXmlData.setArrayData(rightMainData.__get__todayItemData(), idx, "todayItem").dc) + this.getDtypeData(returnXmlData.setArrayData(rightMainData.__get__todayItemData(), idx, "todayItem").dtype);
        } // end else if
        var _loc3 = com.mgame.webMall.main.CommonDataUrl.__get__itemImageURL() + returnXmlData.setArrayData(rightMainData.__get__todayItemData(), idx, "todayItem").bigimage;
        this.itemImageLoad(rightMainData.__get__rightMain().imageArea, _loc3, 64, 64, returnXmlData.setArrayData(rightMainData.__get__todayItemData(), idx, "todayItem"));
    } // End of the function
    function buttonEvent()
    {
        var _this = this;
        rightMainData.__get__rightMain().itemNextButton.onRelease = function ()
        {
            if (_this.pageCount < _this.rightMainData.todayItemTotalCount - 1)
            {
                ++_this.pageCount;
                _this.makeList(_this.pageCount);
            } // end if
        };
        rightMainData.__get__rightMain().itemPrevButton.onRelease = function ()
        {
            if (_this.pageCount - 1 >= 0)
            {
                --_this.pageCount;
                _this.makeList(_this.pageCount);
            } // end if
        };
        rightMainData.__get__rightMain().buyButton.onRelease = function ()
        {
            com.mgame.webMall.util.CommonPopup.popupStart("buy_normal", _this.returnXmlData.setArrayData(_this.rightMainData.todayItemData, _this.pageCount, "todayItem"));
        };
        rightMainData.__get__rightMain().cartButton.onRelease = function ()
        {
            com.mgame.webMall.util.CommonPopup.popupStart("basket", _this.returnXmlData.setArrayData(_this.rightMainData.todayItemData, _this.pageCount, "todayItem"));
        };
    } // End of the function
    function itemImageLoad(targetMovieClip, imageURL, imageWidth, imageHeight, dataObj)
    {
        var _loc1 = new Object();
        var _loc2 = new MovieClipLoader();
        _loc2.addListener(_loc1);
        if (imageURL.indexOf(".bmp") > -1)
        {
            _loc2.unloadClip(targetMovieClip);
            return;
        } // end if
        _loc2.loadClip(imageURL, targetMovieClip);
        _loc1.onLoadInit = function (target)
        {
            target._width = imageWidth;
            target._height = imageHeight;
            target.onRelease = function ()
            {
                com.mgame.webMall.util.CommonPopup.popupStart("detail", dataObj);
            };
        };
        _loc1.onLoadError = function (target_mc, errorCode, httpStatus)
        {
            trace ("itemImageLoadError");
        };
    } // End of the function
    var rightMainData = null;
    var returnXmlData = null;
    var numberSplit = null;
    var textLengthCheck = null;
    var pageCount = 0;
} // End of Class
