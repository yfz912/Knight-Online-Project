class com.mgame.webMall.main.topMain.TopMenu
{
    var index, pageType, bg, idx;
    function TopMenu()
    {
        subCategoryName01 = new Array(com.mgame.webMall.text.MainPackageTextDefine.__get__TopMenu_23_01(), com.mgame.webMall.text.MainPackageTextDefine.__get__TopMenu_23_02());
        subCategoryName02 = new Array(com.mgame.webMall.text.MainPackageTextDefine.__get__TopMenu_24_01(), com.mgame.webMall.text.MainPackageTextDefine.__get__TopMenu_24_02(), com.mgame.webMall.text.MainPackageTextDefine.__get__TopMenu_24_03(), com.mgame.webMall.text.MainPackageTextDefine.__get__TopMenu_24_04());
    } // End of the function
    function load(mainLoad, mainData)
    {
        this.mainData = mainData;
        this.mainLoad = mainLoad;
        previewItemXml = new com.mgame.webMall.main.topMain.PreviewItemXml();
        this.xmlLoad();
    } // End of the function
    function xmlLoad()
    {
        var _this = this;
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        _loc2.onLoad = function ()
        {
            _this.onLoad(this);
        };
        var _loc3 = new LoadVars();
        _loc3.cmd = "myMainMenu";
        _loc3.sendAndLoad(loadURL, _loc2, "post");
    } // End of the function
    function onLoad(xmlData)
    {
        categoryNameArr = new Array();
        categoryIdxArr = new Array();
        categoryType = new Array();
        if (xmlData.firstChild.firstChild.firstChild.nodeValue == "1")
        {
            var _loc3 = xmlData.firstChild.firstChild.nextSibling.childNodes;
            for (var _loc2 = 0; _loc2 < _loc3.length; ++_loc2)
            {
                categoryIdxArr.push(_loc3[_loc2].firstChild.firstChild.nodeValue);
                categoryNameArr.push(_loc3[_loc2].firstChild.nextSibling.firstChild.nodeValue);
                categoryType.push(_loc3[_loc2].firstChild.nextSibling.nextSibling.firstChild.nodeValue);
            } // end of for
            this.makeCategoryMenu();
            this.buttonEvent();
        }
        else
        {
            trace ("카테고리 메뉴 로딩 실패");
        } // end else if
    } // End of the function
    function makeCategoryMenu()
    {
        var _loc3 = null;
        var _loc5 = 8;
        var _loc4 = 38;
        for (var _loc2 = 0; _loc2 < categoryIdxArr.length; ++_loc2)
        {
            mainData.__get__mainStage().searchMenu.attachMovie("categoryMovieClip", "categoryMovieClip" + _loc2, mainData.__get__mainStage().searchMenu.getNextHighestDepth());
            _loc3 = mainData.__get__mainStage().searchMenu["categoryMovieClip" + _loc2];
            if (_loc2 < 1)
            {
                _loc3._x = _loc5;
                _loc3._y = _loc4;
            }
            else
            {
                _loc3._x = mainData.__get__mainStage().searchMenu["categoryMovieClip" + (_loc2 - 1)]._x + mainData.__get__mainStage().searchMenu["categoryMovieClip" + (_loc2 - 1)]._width + 1;
                _loc3._y = _loc4;
            } // end else if
            _loc3.index = categoryIdxArr[_loc2];
            _loc3.pageType = categoryType[_loc2];
            _loc3.name_txt.text = categoryNameArr[_loc2];
            this.buttonEvent("category", _loc3);
        } // end of for
    } // End of the function
    function buttonEvent(type, target)
    {
        var _this = this;
        if (type == "category")
        {
            target.onRelease = function ()
            {
                if (index != "2" && index != "4" && index != "7")
                {
                    _this.previewItemXml.viewClose();
                }
                else
                {
                    com.mgame.webMall.main.MainData.__set__previewPageType(true);
                } // end else if
                _this.currentCategoryTargetName = target._name;
                com.mgame.webMall.main.MainData.__set__PARAMETER_shopNum(index);
                com.mgame.webMall.main.MainData.__set__PARAMETER_cmd(null);
                _this.deleteAndLoad(_this.returnPageType(pageType), "");
            };
            target.onRollOver = function ()
            {
                _this.subMenuLoad(target);
                target.name_txt.textColor = "0xFFCC33";
                bg._alpha = 80;
            };
            target.onRollOut = function ()
            {
                _this.deleteSubMenu();
                target.name_txt.textColor = "0xFFFFFF";
                bg._alpha = 0;
                _this.currentSelectCategory(_this.currentCategoryTargetName);
            };
        }
        else
        {
            mainData.__get__mainStage().mainLogo.onRelease = function ()
            {
                _this.previewItemXml.viewClose();
                _this.mainReload();
            };
        } // end else if
    } // End of the function
    function currentSelectCategory(targetName)
    {
        for (var _loc2 = 0; _loc2 < 8; ++_loc2)
        {
            mainData.__get__mainStage().searchMenu["categoryMovieClip" + _loc2].bg._alpha = 0;
            mainData.__get__mainStage().searchMenu["categoryMovieClip" + _loc2].name_txt.textColor = "0xFFFFFF";
        } // end of for
        mainData.__get__mainStage().searchMenu[targetName].bg._alpha = 80;
        mainData.__get__mainStage().searchMenu[targetName].name_txt.textColor = "0xFFCC33";
    } // End of the function
    function subMenuLoad(target)
    {
        var _this = this;
        var _loc6 = target._name;
        var _loc5 = target.index;
        var _loc4 = _loc6.substr(_loc6.length - 1);
        return;
        if (_loc5 == "5")
        {
            mainData.__get__mainStage().submenu01.removeMovieClip();
            mainData.__get__mainStage().submenu02.removeMovieClip();
            mainData.__get__mainStage().attachMovie("submenu01", "submenu01", 0);
            if (Number(_loc4) > 5)
            {
                mainData.__get__mainStage().submenu01._x = target._x - 2;
                mainData.__get__mainStage().submenu01._y = target._height + target._y + 6;
            }
            else
            {
                mainData.__get__mainStage().submenu01._x = target._x + 4;
                mainData.__get__mainStage().submenu01._y = target._height + target._y + 6;
            } // end else if
            for (var _loc2 = 1; _loc2 < 3; ++_loc2)
            {
                mainData.__get__mainStage().submenu01["area0" + _loc2].idx = _loc2 - 1;
                mainData.__get__mainStage().submenu01["area0" + _loc2].onRelease = function ()
                {
                    com.mgame.webMall.main.MainData.__set__previewPageType(true);
                    _this.deleteAndLoad("searchPage", _this.subCategoryName01[idx]);
                };
            } // end of for
        }
        else if (_loc5 == "4")
        {
            mainData.__get__mainStage().submenu01.removeMovieClip();
            mainData.__get__mainStage().submenu02.removeMovieClip();
            mainData.__get__mainStage().attachMovie("submenu02", "submenu02", mainData.__get__mainStage().getNextHighestDepth());
            if (Number(_loc4) > 5)
            {
                mainData.__get__mainStage().submenu02._x = target._x - (mainData.__get__mainStage().submenu02._width - target._width) + 6;
                mainData.__get__mainStage().submenu02._y = target._height + target._y + 6;
            }
            else
            {
                mainData.__get__mainStage().submenu02._x = target._x + 4;
                mainData.__get__mainStage().submenu02._y = target._height + target._y + 6;
            } // end else if
            for (var _loc2 = 1; _loc2 < 5; ++_loc2)
            {
                mainData.__get__mainStage().submenu02["area0" + _loc2].idx = _loc2 - 1;
                mainData.__get__mainStage().submenu02["area0" + _loc2].onRelease = function ()
                {
                    com.mgame.webMall.main.MainData.__set__previewPageType(true);
                    _this.deleteAndLoad("searchPage", _this.subCategoryName02[idx]);
                };
            } // end of for
        }
        else
        {
            mainData.__get__mainStage().submenu01.removeMovieClip();
            mainData.__get__mainStage().submenu02.removeMovieClip();
        } // end else if
    } // End of the function
    function deleteSubMenu()
    {
        var _this = this;
        mainData.__get__mainStage().searchMenu.submenu01.onRollOut = function ()
        {
            _this.mainData.mainStage.submenu01.removeMovieClip();
            _this.mainData.mainStage.submenu02.removeMovieClip();
        };
        mainData.__get__mainStage().searchMenu.submenu02.onRollOut = function ()
        {
            _this.mainData.mainStage.submenu01.removeMovieClip();
            _this.mainData.mainStage.submenu02.removeMovieClip();
        };
    } // End of the function
    function mainReload()
    {
        mainLoad.deletePage();
        mainLoad.reLoad();
    } // End of the function
    function deleteAndLoad(typeStr, categoryName)
    {
        com.mgame.webMall.main.MainData.__get__storePageCtype().clearTimer();
        com.mgame.webMall.main.MainData.__set__PARAMETER_property(categoryName);
        com.mgame.webMall.main.MainData.__set__PARAMETER_searchText("");
        mainLoad.deletePage();
        mainData.__set__selectMenuType("category");
        mainData.__set__typeStr(typeStr);
        mainLoad.pageCheck();
    } // End of the function
    function returnPageType(value)
    {
        com.mgame.webMall.main.MainData.__set__commonStorePageType(value);
        if (value == "normal" || value == "giftcard" || value == "milage")
        {
            return ("commonStore");
        }
        else if (value == "package")
        {
            return ("packagePage");
        }
        else if (value == "event")
        {
            return ("eventShopPage");
        }
        else if (value == "mainPage")
        {
            return ("mainPage");
        } // end else if
    } // End of the function
    var mainData = null;
    var mainLoad = null;
    var previewItemXml = null;
    static var loadURL = com.mgame.webMall.main.CommonDataUrl.__get__categoryURL();
    var categoryNameArr = null;
    var categoryIdxArr = null;
    var categoryType = null;
    var subCategoryName01 = null;
    var subCategoryName02 = null;
    var currentCategoryTargetName = "";
} // End of Class
