class com.mgame.webMall.util.NumberSplit
{
    function NumberSplit()
    {
    } // End of the function
    function split(value)
    {
        var _loc6 = null;
        var _loc2 = value;
        var _loc7 = _loc2.length;
        var _loc8 = _loc2.length;
        var _loc4 = _loc7 % 3;
        var _loc5 = Math.floor(_loc8 / 3);
        var _loc3 = new Array();
        _loc3.push(_loc2.substr(0, _loc4));
        for (var _loc1 = 0; _loc1 < _loc5; ++_loc1)
        {
            _loc3.push(_loc2.substr(_loc4 + 3 * _loc1, 3));
        } // end of for
        if (_loc4 == 0)
        {
            var _loc9 = _loc3.shift();
        } // end if
        _loc6 = _loc3.toString();
        return (_loc6);
    } // End of the function
    function digit(value)
    {
        if (Number(value) < 10)
        {
            if (value.substr(0, 1) != "0")
            {
                return ("0" + value);
            }
            else
            {
                return (value);
            } // end else if
        }
        else
        {
            return (value);
        } // end else if
    } // End of the function
} // End of Class
