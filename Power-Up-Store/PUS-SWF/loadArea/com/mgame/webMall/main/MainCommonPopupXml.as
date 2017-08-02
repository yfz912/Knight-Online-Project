class com.mgame.webMall.main.MainCommonPopupXml
{
    function MainCommonPopupXml()
    {
    } // End of the function
    function setData(mainCommonPopup, obj, param, cmd, itemCount, cashType, serialNo, targetServer, targetID, message, price, dtype)
    {
        this.mainCommonPopup = mainCommonPopup;
        this.obj = obj;
        this.param = param;
        this.cmd = cmd;
        this.itemCount = itemCount;
        this.cashType = cashType;
        this.serialNo = serialNo;
        this.targetServer = targetServer;
        this.targetID = targetID;
        this.message = message;
        this.price = price;
        this.dtype = dtype;
        this.xmlLoad();
    } // End of the function
    function xmlLoad()
    {
        encryptionInput = new com.mgame.webMall.rc4.EncryptionInput();
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.xmlOnLoad(this);
        };
        if (cmd == "BUY_NORMAL" || cmd == "GIFT_NORMAL")
        {
            _loc2.obj = encryptionInput.inputData(obj.strSubmit);
            _loc2.price = obj.dc;
        }
        else
        {
            _loc2.obj = encryptionInput.inputData(String(obj));
            _loc2.price = price;
        } // end else if
        if (cashType == "MILAGE")
        {
            cmd == "BUY_MILAGE";
        } // end if
        if (cashType == "GIFTCARD")
        {
            cmd == "BUY_GIFTCARD";
        } // end if
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.cmd = cmd;
        _loc2.itemID = obj.goodsno;
		_loc2.itemCount = itemCount;
        _loc2.cashType = cashType;
        _loc2.serialNo = encryptionInput.inputData(serialNo);
        _loc2.targetServer = encryptionInput.inputData(targetServer);
        _loc2.targetChar = encryptionInput.inputData(targetID);
        _loc2.message = encryptionInput.inputData(message);
		
        _loc2.sendAndLoad(loadURL, _loc3, "post");
    } // End of the function
    function xmlOnLoad(xmlData)
    {
        var _loc2 = xmlData.firstChild.firstChild.nextSibling.childNodes;
        if (_loc2[0].firstChild.nodeValue == "-1")
        {
            this.errorMsg(_loc2);
        }
        else if (cmd == "BUY_NORMAL")
        {
            this.buyComplete(_loc2[2].firstChild.nodeValue);
        }
        else if (cmd == "BUY_PACKAGE")
        {
            this.packageComplete(_loc2[2].firstChild.nodeValue);
        }
        else if (cmd == "GIFT_NORMAL")
        {
            this.giftComplete(_loc2[2].firstChild.nodeValue);
        }
        else
        {
            this.selectBuyComplete(_loc2[2].firstChild.nodeValue);
        } // end else if
    } // End of the function
    function buyComplete(data)
    {
        var _loc2 = data.split("\x0b");
        var _loc5 = _loc2[0];
        var _loc6 = _loc2[1];
        var _loc4 = _loc2[2];
        var _loc3 = _loc2[3];
        mainCommonPopup.buyCompletePopupLoad(_loc5, _loc6, _loc4, _loc3, dtype);
    } // End of the function
    function giftComplete(data)
    {
        var _loc2 = data.split("\x0b");
        var _loc6 = _loc2[0];
        var _loc8 = _loc2[1];
        var _loc5 = _loc2[2];
        var _loc3 = _loc2[3];
        var _loc7 = _loc2[4];
        var _loc4 = _loc2[5];
        mainCommonPopup.giftCompletePopupLoad(_loc6, _loc8, _loc5, _loc3, _loc7, _loc4, dtype);
    } // End of the function
    function selectBuyComplete(data)
    {
        var _loc3 = data.split("|");
        var _loc5 = new Array();
        var _loc6 = new Array();
        var _loc7 = new Array();
        var _loc4 = new Array();
        for (var _loc2 = 0; _loc2 < _loc3.length; ++_loc2)
        {
            _loc5.push(String(_loc3[_loc2]).split("\x0b")[0]);
            _loc6.push(String(_loc3[_loc2]).split("\x0b")[1]);
            _loc7.push(String(_loc3[_loc2]).split("\x0b")[2]);
            _loc4.push(String(_loc3[_loc2]).split("\x0b")[3]);
        } // end of for
        mainCommonPopup.bySelectCompletePopupLoad(_loc5, _loc6, _loc7, _loc4, dtype);
    } // End of the function
    function packageComplete(data)
    {
        var _loc2 = data.split("\x0b");
        var _loc5 = _loc2[0];
        var _loc6 = "1";
        var _loc4 = _loc2[1];
        var _loc3 = _loc2[2];
        mainCommonPopup.buyCompletePopupLoad(_loc5, _loc6, _loc4, _loc3);
    } // End of the function
    function errorMsg(dataArr)
    {
        mainCommonPopup.errorMsgPopupLoad(dataArr[2], "close");
    } // End of the function
    function settleCloseStart(num, mainCommonPopup)
    {
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.settleCloseXmlOnLoad(this);
        };
        _loc2.num = num;
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.cmd = "TERMINATE";
        _loc2.sendAndLoad(settleCloseURL, _loc3, "post");
    } // End of the function
    function settleCloseXmlOnLoad(xmlData)
    {
        var _loc3 = xmlData.firstChild.childNodes[1].childNodes[0].firstChild.nodeValue;
        var _loc2 = xmlData.firstChild.childNodes[1].childNodes[3].firstChild.nodeValue;
        if (_loc3 == "1")
        {
            mainCommonPopup.premiumCloseCompletePopupLoad();
        }
        else
        {
            _loc2 = "<p align=\'center\'><br>" + _loc2 + "</p>";
            mainCommonPopup.errorMsgPopupLoad(_loc2, "close");
        } // end else if
    } // End of the function
    function invenCheckStart(popupMovieClip, mainCommonPopup)
    {
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        var _loc3 = new LoadVars();
        _loc2.onLoad = function ()
        {
            _this.invenCheckXmlOnLoad(this, popupMovieClip);
        };
        _loc3.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc3.cmd = "CASH_INVEN_CHECK";
        _loc3.sendAndLoad(invenCheckURL, _loc2, "post");
    } // End of the function
    function invenCheckXmlOnLoad(xmlData, popupMovieClip)
    {
        var _loc6 = xmlData.firstChild.firstChild.firstChild.nodeValue;
        if (_loc6 == "1")
        {
            var _loc5 = xmlData.firstChild.childNodes[1].childNodes[0].firstChild.nodeValue;
            var _loc4 = xmlData.firstChild.childNodes[1].childNodes[3].firstChild.nodeValue;
            var _loc2 = xmlData.firstChild.childNodes[1].childNodes[4].firstChild.nodeValue;
            if (_loc5 != "1")
            {
                _loc4 = "-";
                _loc2 = "-";
            } // end if
            mainCommonPopup.setInvenData(popupMovieClip, _loc4, _loc2, "", "");
        }
        else
        {
            trace ("장비창 xml error");
        } // end else if
    } // End of the function
    function couponRegisterStart(serialObj, mainCommonPopup)
    {
        encryptionInput = new com.mgame.webMall.rc4.EncryptionInput();
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.couponXmlOnload(this);
        };
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.cmd = "ticketReg";
        _loc2.Serial1 = encryptionInput.inputData(serialObj.num1);
        _loc2.Serial2 = encryptionInput.inputData(serialObj.num2);
        _loc2.Serial3 = encryptionInput.inputData(serialObj.num3);
        _loc2.Serial4 = encryptionInput.inputData(serialObj.num4);
        _loc2.sendAndLoad(couponURL, _loc3, "post");
    } // End of the function
    function couponXmlOnload(xmlData)
    {
        var _loc2 = "";
        _loc2 = "<p align=\'center\'><br>" + xmlData.firstChild.childNodes[1].childNodes[1].firstChild.nodeValue + "</p>";
        if (xmlData.firstChild.childNodes[1].childNodes[0].firstChild.nodeValue == "1")
        {
            mainCommonPopup.couponSerialCompletePopupLoad(_loc2);
        }
        else
        {
            mainCommonPopup.errorMsgPopupLoad(_loc2, "close");
        } // end else if
    } // End of the function
    function basketControlStart(dataObj, count, mainCommonPopup)
    {
        encryptionInput = new com.mgame.webMall.rc4.EncryptionInput();
        this.mainCommonPopup = mainCommonPopup;
        var _loc4 = "";
        var _loc7 = String(count);
        if (dataObj.length > 0)
        {
            for (var _loc2 = 0; _loc2 < dataObj.length; ++_loc2)
            {
                if (_loc2 < dataObj.length - 1)
                {
                    _loc4 = _loc4 + (dataObj[_loc2].goodsno + "|");
                    continue;
                } // end if
                _loc4 = _loc4 + dataObj[_loc2].goodsno;
            } // end of for
            _loc7 = "1";
        }
        else
        {
            _loc4 = dataObj.goodsno;
            _loc7 = "1";
        } // end else if
        var _this = this;
        var _loc6 = new XML();
        _loc6.ignoreWhite = true;
        var _loc5 = new LoadVars();
        _loc6.onLoad = function ()
        {
            _this.basketXmlOnLoad(this);
        };
        _loc5.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc5.basketObj = encryptionInput.inputData(_loc4);
        _loc5.basketCount = _loc7;
        _loc5.cmd = "inBasket";
        _loc5.sendAndLoad(basketURL, _loc6, "post");
    } // End of the function
    function basketControlEdit(goodsno, count, mainCommonPopup)
    {
        encryptionInput = new com.mgame.webMall.rc4.EncryptionInput();
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.basketXmlOnLoad(this);
        };
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.basketObj = encryptionInput.inputData(goodsno);
        _loc2.basketCount = count;
        _loc2.cmd = "moBasket";
        _loc2.sendAndLoad(basketURL, _loc3, "post");
    } // End of the function
    function basketControlDelete(dataObj, mainCommonPopup)
    {
        encryptionInput = new com.mgame.webMall.rc4.EncryptionInput();
        this.mainCommonPopup = mainCommonPopup;
        var _loc4 = "";
        if (dataObj.length > 0)
        {
            for (var _loc2 = 0; _loc2 < dataObj.length; ++_loc2)
            {
                if (_loc2 < dataObj.length - 1)
                {
                    _loc4 = _loc4 + (dataObj[_loc2] + "|");
                    continue;
                } // end if
                _loc4 = _loc4 + dataObj[_loc2];
            } // end of for
        }
        else
        {
            _loc4 = dataObj.goodsno;
        } // end else if
        var _this = this;
        var _loc6 = new XML();
        _loc6.ignoreWhite = true;
        var _loc5 = new LoadVars();
        _loc6.onLoad = function ()
        {
            _this.basketXmlOnLoad(this);
        };
        _loc5.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc5.basketObj = encryptionInput.inputData(_loc4);
        _loc5.cmd = "delBasket";
        _loc5.sendAndLoad(basketURL, _loc6, "post");
    } // End of the function
    function basketXmlOnLoad(xmlData)
    {
        var _loc2 = "";
        _loc2 = "<p align=\'center\'><br>" + xmlData.firstChild.childNodes[1].childNodes[1].firstChild.nodeValue + "</p>";
        if (xmlData.firstChild.childNodes[1].childNodes[0].firstChild.nodeValue == "1")
        {
            mainCommonPopup.basketControlPopupLoad(_loc2);
        }
        else
        {
            mainCommonPopup.errorMsgPopupLoad(_loc2, "close");
        } // end else if
    } // End of the function
    function userCheck(userID, mainCommonPopup, popupMovieClip)
    {
        encryptionInput = new com.mgame.webMall.rc4.EncryptionInput();
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.userCheckOnLoad(this, userID, popupMovieClip);
        };
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.cmd = "USER_SEARCH";
        _loc2.targetChar = encryptionInput.inputData(userID);
        _loc2.sendAndLoad(loadURL, _loc3, "post");
    } // End of the function
    function userCheckOnLoad(xmlData, userID, popupMovieClip)
    {
        var _loc3 = xmlData.firstChild.childNodes[1].childNodes[0].firstChild.nodeValue;
        var _loc2 = xmlData.firstChild.childNodes[1].childNodes[2].firstChild.nodeValue;
        _loc2 = "<br><p align=\'center\'>" + _loc2 + "</p>";
        if (_loc3 == "1")
        {
            mainCommonPopup.__set__targetCharCheckValue(true);
            mainCommonPopup.__set__targetChar(userID);
            mainCommonPopup.errorMsgPopupLoad(_loc2, "open", popupMovieClip);
        }
        else
        {
            mainCommonPopup.__set__targetCharCheckValue(false);
            mainCommonPopup.errorMsgPopupLoad(_loc2, "open", popupMovieClip);
        } // end else if
    } // End of the function
    function jorgiStart(goodsno, targetChar, msg, mainCommonPopup)
    {
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.jorgiOnLoad(this);
        };
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.cmd = "jorgiMsg";
        _loc2.obj = goodsno;
        _loc2.targetChar = targetChar;
        _loc2.message = msg;
        _loc2.sendAndLoad(msgJorgiURL, _loc3, "post");
    } // End of the function
    function jorgiOnLoad(xmlData)
    {
        var _loc3 = xmlData.firstChild.childNodes[1].childNodes[0].firstChild.nodeValue;
        var _loc2 = xmlData.firstChild.childNodes[1].childNodes[1].firstChild.nodeValue;
        _loc2 = "<br><p align=\'center\'>" + _loc2 + "</p>";
        if (_loc3 == "1")
        {
            mainCommonPopup.errorMsgPopupLoad(_loc2, "close");
        }
        else
        {
            mainCommonPopup.errorMsgPopupLoad(_loc2, "close");
        } // end else if
    } // End of the function
    function cashItemCancelStart(itemNum, msg, mainCommonPopup, popupMovieClip)
    {
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.cashItemXmlOnLoad(this, popupMovieClip);
        };
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.cmd = "CASH_ITEM_CANCEL";
        _loc2.obj = itemNum;
        _loc2.message = msg;
        _loc2.sendAndLoad(cashItemCancelURL, _loc3, "post");
    } // End of the function
    function cashItemXmlOnLoad(xmlData, popupMovieClip)
    {
        var _loc2 = xmlData.firstChild.childNodes[1].childNodes[0].firstChild.nodeValue;
        var _loc3 = xmlData.firstChild.childNodes[1].childNodes[2].firstChild.nodeValue;
        mainCommonPopup.cashItemCancelComplete(popupMovieClip, _loc2, _loc3);
    } // End of the function
    function cashItemSubmitStart(itemNum, mainCommonPopup, popupMovieClip)
    {
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.cashItemXmlOnLoad(this, popupMovieClip);
        };
        _loc2.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc2.cmd = "CASH_ITEM_SUBMIT";
        _loc2.obj = itemNum;
        _loc2.sendAndLoad(cashItemCancelURL, _loc3, "post");
    } // End of the function
    function cashItemSubmitXmlOnLoad(xmlData, popupMovieClip)
    {
        var _loc2 = xmlData.firstChild.childNodes[1].childNodes[0].firstChild.nodeValue;
        var _loc3 = xmlData.firstChild.childNodes[1].childNodes[2].firstChild.nodeValue;
        mainCommonPopup.cashItemSubmitComplete(popupMovieClip, _loc2, _loc3);
    } // End of the function
    function myEmailEditStart(nid, id, password, newEmail, mainCommonPopup, childPopup01, childPopup02)
    {
        this.mainCommonPopup = mainCommonPopup;
        var _this = this;
        var _loc3 = new XML();
        _loc3.ignoreWhite = true;
        var _loc2 = new LoadVars();
        _loc3.onLoad = function ()
        {
            _this.myEmailEditComplete(this, childPopup01, childPopup02);
        };
        _loc2.usernid = nid;
        _loc2.userid = id;
        _loc2.userpass = password;
        _loc2.useremail = newEmail;
        _loc2.sendAndLoad(emailEditURL, _loc3, "post");
    } // End of the function
    function myEmailEditComplete(xmlData, childPopup01, childPopup02)
    {
        var _loc2 = xmlData.firstChild.childNodes[0].firstChild.nodeValue;
        var _loc3 = xmlData.firstChild.childNodes[1].firstChild.nodeValue;
        mainCommonPopup.emailEditComplete(_loc2, _loc3, childPopup01, childPopup02);
    } // End of the function
    var obj = null;
    var cmd = null;
    var param = null;
    var itemCount = null;
    var cashType = null;
    var serialNo = null;
    var targetServer = null;
    var targetID = null;
    var message = null;
    var price = null;
    var dtype = null;
    static var loadURL = com.mgame.webMall.main.CommonDataUrl.__get__commonPopupCompleteURL();
    static var settleCloseURL = com.mgame.webMall.main.CommonDataUrl.__get__settleCloseURL();
    static var invenCheckURL = com.mgame.webMall.main.CommonDataUrl.__get__previewAndInvenURL();
    static var couponURL = com.mgame.webMall.main.CommonDataUrl.__get__couponRegisterURL();
    static var basketURL = com.mgame.webMall.main.CommonDataUrl.__get__basketControlURL();
    static var msgJorgiURL = com.mgame.webMall.main.CommonDataUrl.__get__msgJorgiURL();
    static var cashItemCancelURL = com.mgame.webMall.main.CommonDataUrl.__get__previewAndInvenURL();
    static var emailEditURL = com.mgame.webMall.main.CommonDataUrl.__get__myEmailEditURL();
    var mainCommonPopup = null;
    var encryptionInput = null;
} // End of Class
