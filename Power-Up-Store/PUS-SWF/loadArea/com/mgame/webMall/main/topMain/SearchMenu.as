class com.mgame.webMall.main.topMain.SearchMenu
{
    function SearchMenu()
    {
    } // End of the function
    function load(mainLoad, mainData)
    {
        this.mainData = mainData;
        this.mainLoad = mainLoad;
        previewItemXml = new com.mgame.webMall.main.topMain.PreviewItemXml();
        scrollBar = new com.mgame.webMall.util.ScrollBar();
        this.componentLoad();
        this.categoryXmlLoad();
    } // End of the function
    function componentLoad()
    {
        var _this = this;
        searchInput = mainData.__get__mainStage().searchMenu.searchInput;
        nameTypeRadio = mainData.__get__mainStage().searchMenu.nameTypeRadio;
        explainTypeRadio = mainData.__get__mainStage().searchMenu.explainTypeRadio;
        categoryComboBox = mainData.__get__mainStage().searchMenu.categoryComboBox;
        nameTypeRadio.selected = true;
        nameTypeRadio.__set__data("name");
        explainTypeRadio.__set__data("detail");
        var _loc3 = new Object();
        _loc3.click = function (evt_obj)
        {
            com.mgame.webMall.main.MainData.__set__PARAMETER_searchType(evt_obj.target.selection.data);
        };
        mainData.__get__mainStage().searchMenu.radioGroup.addEventListener("click", _loc3);
        var _loc2 = new Object();
        _loc2.enter = function (eventObject)
        {
            com.mgame.webMall.main.MainData.__set__PARAMETER_property(_this.categoryComboBox.selectedItem.data);
            com.mgame.webMall.main.MainData.__set__PARAMETER_searchText(eventObject.target.text);
            _this.serachPageMove(com.mgame.webMall.main.MainData.__get__PARAMETER_property(), com.mgame.webMall.main.MainData.__get__PARAMETER_searchType(), com.mgame.webMall.main.MainData.__get__PARAMETER_searchText());
        };
        searchInput.addEventListener("enter", _loc2);
        _loc2.change = function (eventObject)
        {
        };
        searchInput.addEventListener("change", _loc2);
        mainData.__get__mainStage().searchMenu.searchButton.onRelease = function ()
        {
            com.mgame.webMall.main.MainData.__set__PARAMETER_property(_this.categoryComboBox.selectedItem.data);
            com.mgame.webMall.main.MainData.__set__PARAMETER_searchText(_this.searchInput.text);
            _this.serachPageMove(com.mgame.webMall.main.MainData.__get__PARAMETER_property(), com.mgame.webMall.main.MainData.__get__PARAMETER_searchType(), com.mgame.webMall.main.MainData.__get__PARAMETER_searchText());
        };
        mainData.__get__mainStage().searchMenu.todayItemButton.onRelease = function ()
        {
            _this.deleteAndLoad("todayItemPage");
        };
    } // End of the function
    function categoryAddItem(dataArr)
    {
        var _this = this;
        categoryComboBox.removeAll();
        categoryComboBox.addItem(com.mgame.webMall.text.MainPackageTextDefine.__get__SearchMenu_94(), "");
        for (var _loc2 = 0; _loc2 < dataArr.length; ++_loc2)
        {
            categoryComboBox.addItem(dataArr[_loc2], dataArr[_loc2]);
        } // end of for
        com.mgame.webMall.main.MainData.__set__PARAMETER_property(_this.categoryComboBox.selectedItem.data);
        var _loc4 = new Object();
        _loc4.change = function (evt_obj)
        {
            com.mgame.webMall.main.MainData.__set__PARAMETER_property(_this.categoryComboBox.selectedItem.data);
        };
        categoryComboBox.addEventListener("change", _loc4);
        _loc4.itemRollOver = function (eventObject)
        {
            com.mgame.webMall.main.MainData.__set__wheelValue(false);
        };
        categoryComboBox.addEventListener("itemRollOver", _loc4);
        _loc4.itemRollOut = function (eventObject)
        {
            com.mgame.webMall.main.MainData.__set__wheelValue(true);
        };
        categoryComboBox.addEventListener("itemRollOut", _loc4);
    } // End of the function
    function serachPageMove(property, searchType, searchText)
    {
        this.deleteAndLoad("searchPage");
    } // End of the function
    function deleteAndLoad(typeStr)
    {
        previewItemXml.viewClose();
        mainLoad.deletePage();
        mainData.__set__typeStr(typeStr);
        mainLoad.pageCheck();
    } // End of the function
    function categoryXmlLoad()
    {
        var _this = this;
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        _loc2.onLoad = function ()
        {
            _this.onLoad(this);
        };
        var _loc3 = new LoadVars();
        _loc3.cmd = "myMainSearch";
        _loc3.sendAndLoad(loadURL, _loc2, "post");
    } // End of the function
    function onLoad(xmlData)
    {
        var _loc4 = new Array();
        if (xmlData.firstChild.firstChild.firstChild.nodeValue == "1")
        {
            var _loc3 = xmlData.firstChild.firstChild.nextSibling.childNodes;
            for (var _loc2 = 0; _loc2 < _loc3.length; ++_loc2)
            {
                _loc4.push(_loc3[_loc2].firstChild.firstChild.nodeValue);
            } // end of for
            this.categoryAddItem(_loc4);
        }
        else
        {
            trace ("검색어 XML 데이터 로딩 실패");
        } // end else if
    } // End of the function
    var mainLoad = null;
    var mainData = null;
    var previewItemXml = null;
    var searchInput = null;
    var nameTypeRadio = null;
    var explainTypeRadio = null;
    var categoryComboBox = null;
    var scrollBar = null;
    static var loadURL = com.mgame.webMall.main.CommonDataUrl.__get__mainSearchURL();
} // End of Class
