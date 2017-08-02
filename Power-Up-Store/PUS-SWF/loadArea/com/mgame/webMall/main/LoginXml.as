class com.mgame.webMall.main.LoginXml
{
    function LoginXml()
    {
    } // End of the function
    function load(mainData)
    {
        this.mainData = mainData;
        this.xmlLoad();
    } // End of the function
    function xmlLoad()
    {
        var _this = this;
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        _loc2.onLoad = function ()
        {
            _this.hiddenPageLoad(this);
        };
        var _loc3 = new LoadVars();
        _loc3.mgmac = com.mgame.webMall.main.MainData.mgmac;
        _loc3.sendAndLoad(com.mgame.webMall.main.CommonDataUrl.__get__loginXmlLoadURL(), _loc2, "POST");
    } // End of the function
    function hiddenPageLoad(loginData)
    {
        var _this = this;
        var _loc2 = new XML();
        var loader_status = 200;
        _loc2.onHTTPStatus = function (s)
        {
            loader_status = s;
        };
        _loc2.onLoad = function ()
        {
            if (loader_status == 404 || loader_status == 0)
            {
                _this.popupLoad("[HTC-003] " + com.mgame.webMall.text.MainPackageTextDefine.__get__LoginXml_57());
            }
            else
            {
                _this.hiddenCheck(this, loginData);
            } // end else if
        };
        _loc2.load(com.mgame.webMall.main.CommonDataUrl.__get__hiddenPageURL());
    } // End of the function
    function hiddenCheck(v, loginData)
    {
        encryptionInput = new com.mgame.webMall.rc4.EncryptionInput();
        var _loc4 = encryptionInput.inputData(v, 1);
        var _loc2 = _loc4.split(",");
        var _loc5 = _loc2[2].split("|")[1];
        var _loc3 = Number(_loc2[3].split("-")[0]);
        if (_loc5 != "on")
        {
            this.popupLoad("[HTC-001] " + com.mgame.webMall.text.MainPackageTextDefine.__get__LoginXml_57());
            return;
        } // end if
        if (_loc3 < 2012 || _loc3 > 2030)
        {
            this.popupLoad("[HTC-002]" + com.mgame.webMall.text.MainPackageTextDefine.__get__LoginXml_57());
            return;
        } // end if
        this.onLoad(loginData);
    } // End of the function
    function popupLoad(msg)
    {
        var _loc2 = new com.mgame.webMall.main.MainCommonPopup();
        _loc2.setData(mainData);
        _loc2.errorMsgPopupLoad(msg);
    } // End of the function
    function onLoad(xmlData)
    {
        var _loc3 = Number(xmlData.firstChild.childNodes[0].firstChild.nodeValue);
        if (_loc3 != 1)
        {
            this.xmlLoadError();
            return;
        } // end if
        com.mgame.webMall.main.MainData.__set__LOGIN_nid(String(xmlData.firstChild.childNodes[1].firstChild.nodeValue));
        com.mgame.webMall.main.MainData.__set__LOGIN_uid(String(xmlData.firstChild.childNodes[2].firstChild.nodeValue));
        com.mgame.webMall.main.MainData.__set__LOGIN_gcode(String(xmlData.firstChild.childNodes[3].firstChild.nodeValue));
        com.mgame.webMall.main.MainData.__set__LOGIN_utype(String(xmlData.firstChild.childNodes[4].firstChild.nodeValue));
        com.mgame.webMall.main.MainData.__set__LOGIN_otpcode(String(xmlData.firstChild.childNodes[5].firstChild.nodeValue));
        com.mgame.webMall.main.MainData.__set__LOGIN_site(String(xmlData.firstChild.childNodes[6].firstChild.nodeValue));
        com.mgame.webMall.main.MainData.__set__LOGIN_auckey(String(xmlData.firstChild.childNodes[7].firstChild.nodeValue));
        com.mgame.webMall.main.MainData.__set__LOGIN_game_code(String(xmlData.firstChild.childNodes[8].firstChild.nodeValue));
        com.mgame.webMall.main.MainData.__set__LOGIN_email(String(xmlData.firstChild.childNodes[9].firstChild.nodeValue));
        mainData.__get__mainLoad().serviceCheck();
    } // End of the function
    function xmlLoadError()
    {
        var _loc2 = com.mgame.webMall.text.MainPackageTextDefine.__get__LoginXml_61();
        this.popupLoad(_loc2);
    } // End of the function
    var mainData = null;
    var encryptionInput = null;
} // End of Class
