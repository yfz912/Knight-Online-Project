class com.mgame.webMall.util.ReturnPriceType
{
    function ReturnPriceType()
    {
    } // End of the function
    static function getData()
    {
        if (com.mgame.webMall.main.MainData.__get__commonStorePageType() == "gzone")
        {
            return (" GP");
        }
        else if (com.mgame.webMall.main.MainData.__get__commonStorePageType() == "point")
        {
            return (" P");
        }
        else
        {
            //return (com.mgame.webMall.text.UtilPackageTextDefine.ReturnPriceType_27());
        } // end else if
    } // End of the function
    static function getDtypeData(dtype)
    {
        if (dtype == "5")
        {
            return (" GP");
        }
        else if (dtype == "8")
        {
            return (" P");
        }
        else
        {
            //return (com.mgame.webMall.text.UtilPackageTextDefine.ReturnPriceType_41());
        } // end else if
    } // End of the function
} // End of Class
