class com.mgame.webMall.util.TextLengthCheck
{
    function TextLengthCheck()
    {
    } // End of the function
    function checkTextValue(str, checkLength)
    {
        if (str.length > checkLength)
        {
            return (this.trim(str, checkLength));
        }
        else
        {
            return (str);
        } // end else if
    } // End of the function
    function trim(str, checkLength)
    {
        var _loc1 = null;
        if (str.length >= checkLength)
        {
            _loc1 = str.substr(0, checkLength);
            _loc1 = _loc1 + "..";
        }
        else
        {
            _loc1 = str;
        } // end else if
        return (_loc1);
    } // End of the function
    function FFGetByteLength(obj)
    {
        var _loc1 = obj.text;
        var _loc5 = _loc1;
        var _loc7 = _loc5.length;
        var _loc3 = 0;
        var _loc4 = null;
        var _loc6 = 0;
        var _loc8 = new Object();
        while (_loc1 && _loc1.indexOf(" ") == 0)
        {
            for (var _loc1 = _loc1.substring(1); _loc1 && _loc1.lastIndexOf(" ") == _loc1.length - 1; _loc1 = _loc1.substring(0, _loc1.length - 1))
            {
            } // end of for
        } // end while
        for (var _loc2 = 0; _loc2 < _loc7; ++_loc2)
        {
            _loc4 = _loc5.charAt(_loc2);
            if (escape(_loc4).length > 4)
            {
                _loc3 = _loc3 + 2;
            }
            else if (_loc4 == "\r" && _loc5.charAt(_loc2 + 1) == "\n")
            {
                _loc3 = _loc3 + 2;
            }
            else if (_loc4 != "\n")
            {
                ++_loc3;
            } // end else if
            if (_loc3 >= 100)
            {
                _loc3 = 100;
                _loc6 = _loc2;
                break;
            } // end if
        } // end of for
        _loc8.count = _loc3;
        _loc8.strLen = _loc6;
        _loc8.strValue = _loc1;
        return (_loc8);
    } // End of the function
} // End of Class
