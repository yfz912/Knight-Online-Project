class com.mgame.webMall.page.commonStorePage.StorePageLoad
{
    function StorePageLoad()
    {
    } // End of the function
    function load(mainStage)
    {
        storePageData = new com.mgame.webMall.page.commonStorePage.StorePageData();
        storePageXml = new com.mgame.webMall.page.commonStorePage.StorePageXml();
        storePageMakeType = new com.mgame.webMall.page.commonStorePage.StorePageMakeType();
        storePageData.__set__mainStage(mainStage);
        storePageData.__set__main(mainStage.main);
        storePageData.__set__maskMovieClip(mainStage.maskMovieClip);
        storePageData.__get__main().setMask(storePageData.__get__maskMovieClip());
        storePageData.__set__storePageLoad(this);
        storePageData.__set__shopNum(com.mgame.webMall.main.MainData.PARAMETER_shopNum);
        storePageXml.load(this, storePageData);
    } // End of the function
    function init()
    {
        storePageMakeType.type(storePageData.__get__layoutType(), storePageData);
        this.scroll();
    } // End of the function
    function scroll()
    {
        if (storePageData.__get__layoutType() == "3")
        {
            storePageData.__get__mainStage().scrollbar._visible = false;
            scrollBar.deleteWheelScroll();
        }
        else
        {
            storePageData.__get__mainStage().scrollbar._visible = true;
            storePageData.__set__bar(storePageData.__get__mainStage().scrollbar.bar);
            storePageData.__set__scrollUpButton(storePageData.__get__mainStage().scrollbar.scrollUpButton);
            storePageData.__set__scrollDownButton(storePageData.__get__mainStage().scrollbar.scrollDownButton);
            if (scrollBar == null)
            {
                scrollBar = new com.mgame.webMall.util.ScrollBar();
            } // end if
            scrollBar.setScrollTarget(storePageData.__get__main());
            scrollBar.setScrollUpButton(storePageData.__get__scrollUpButton());
            scrollBar.setScrollDownButton(storePageData.__get__scrollDownButton());
            scrollBar.setScrollBar(storePageData.__get__bar());
            scrollBar.deleteWheelScroll();
            scrollBar.start(storePageData.__get__maskMovieClip()._height, scrollTargetOriginY, scrollbarY, scrollbarHeight);
            com.mgame.webMall.main.MainData.__set__currentScrollBarFunc(scrollBar);
            com.mgame.webMall.main.MainData.__set__currentScrollTarget(storePageData.main);
        } // end else if
        com.mgame.webMall.main.MainLoad.getMainData().__get__mainStage().mainClose._alpha = 0;
        com.mgame.webMall.main.MainLoad.getMainData().__get__mainStage().mainClose._visible = false;
    } // End of the function
    function getStorePageXml()
    {
        return (storePageXml);
    } // End of the function
    var storePageData = null;
    var storePageXml = null;
    var storePageMakeType = null;
    var scrollBar = null;
    var scrollbarY = 15;
    var scrollbarHeight = 527;
    var scrollTargetOriginY = 26;
} // End of Class
