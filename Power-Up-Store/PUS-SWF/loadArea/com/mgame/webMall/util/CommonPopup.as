class com.mgame.webMall.util.CommonPopup
{
    function CommonPopup()
    {
    } // End of the function
    static function popupStart(type, dataObj, optValue)
    {
        com.mgame.webMall.main.MainData.__get__currentScrollBarFunc().setMouseWheelStyle(false);
        var _loc6 = "";
        if (type == "buy_normal")
        {
            if (com.mgame.webMall.main.MainData.__get__PARAMETER_cmd() == "settleShop")
            {
                type = "premium_check";
            } // end if
        } // end if
        if (type == "detail")
        {
            if (dataObj.limit_type != "0")
            {
                type = "limit_detail";
            } // end if
        } // end if
        var _loc2 = new com.mgame.webMall.main.MainCommonPopup();
        _loc2.setData(com.mgame.webMall.main.MainLoad.getMainData());
        var _loc4 = com.mgame.webMall.text.UtilPackageTextDefine.__get__CommonPopup_57();
        if (type == "buy_select")
        {
            if (dataObj.length > 10)
            {
                var _loc5 = com.mgame.webMall.text.UtilPackageTextDefine.__get__CommonPopup_63();
                _loc2.errorMsgPopupLoad(_loc5, "close");
                return;
            } // end if
        } // end if
        if (type == "cNotice")
        {
            _loc2.cashItemProvisionPopupLoad();
            return;
        } // end if
        if (type == "buy_package")
        {
            type = "buy_select";
            _loc2.popupStart(type, dataObj, "package", optValue);
        }
        else if (type == "buy_basket")
        {
            type = "buy_select";
            if (dataObj.length == 0)
            {
                _loc2.errorMsgPopupLoad(_loc4, "close");
            }
            else
            {
                _loc2.popupStart(type, dataObj, "basket");
            } // end else if
        }
        else if (type == "inven_check" || type == "ticket_register")
        {
            _loc2.popupStart(type, dataObj);
        }
        else if (dataObj.length == 0)
        {
            _loc2.errorMsgPopupLoad(_loc4, "close");
        }
        else
        {
            _loc2.popupStart(type, dataObj);
        } // end else if
        com.mgame.webMall.util.CommonPopup.setCookie(dataObj);
    } // End of the function
    static function alert(msg)
    {
        var _loc1 = new com.mgame.webMall.main.MainCommonPopup();
        _loc1.setData(com.mgame.webMall.main.MainLoad.getMainData());
        _loc1.errorMsgPopupLoad(msg, "close");
    } // End of the function
    static function setCookie(dataObj)
    {
        if (dataObj.goodsno == undefined)
        {
            return;
        } // end if
        if (com.mgame.webMall.main.MainData.__get__todayItemCookie().data.idx == undefined)
        {
            com.mgame.webMall.main.MainData.__get__todayItemCookie().data.idx = "";
        } // end if
        if (com.mgame.webMall.main.MainData.__get__todayItemCookie().data.idx == "undefined")
        {
            com.mgame.webMall.main.MainData.__get__todayItemCookie().data.idx = "";
        } // end if
        var _loc2 = com.mgame.webMall.main.MainData.__get__todayItemCookie().data.idx;
        if (_loc2.indexOf(dataObj.goodsno + "\x0b") < 0)
        {
            com.mgame.webMall.main.MainData.__get__todayItemCookie().data.idx = com.mgame.webMall.main.MainData.__get__todayItemCookie().data.idx + (dataObj.goodsno + "\x0b");
        } // end if
    } // End of the function
    static var rightMenu = null;
} // End of Class
