class com.mgame.webMall.rc4.RC4
{
    function RC4()
    {
    } // End of the function
    static function encrypt(src, key)
    {
        var _loc3 = com.mgame.webMall.rc4.RC4.strToChars(src);
        var _loc1 = com.mgame.webMall.rc4.RC4.strToChars(key);
        var _loc2 = com.mgame.webMall.rc4.RC4.calculate(_loc3, _loc1);
        return (com.mgame.webMall.rc4.RC4.charsToHex(_loc2));
    } // End of the function
    static function decrypt(src, key)
    {
        var _loc3 = com.mgame.webMall.rc4.RC4.hexToChars(src);
        var _loc1 = com.mgame.webMall.rc4.RC4.strToChars(key);
        var _loc2 = com.mgame.webMall.rc4.RC4.calculate(_loc3, _loc1);
        return (com.mgame.webMall.rc4.RC4.charsToStr(_loc2));
    } // End of the function
    static function initialize(pwd)
    {
        var _loc2 = 0;
        var _loc3;
        var _loc4 = pwd.length;
        for (var _loc1 = 0; _loc1 <= 255; ++_loc1)
        {
            com.mgame.webMall.rc4.RC4.mykey[_loc1] = pwd[_loc1 % _loc4];
            com.mgame.webMall.rc4.RC4.sbox[_loc1] = _loc1;
        } // end of for
        for (var _loc1 = 0; _loc1 <= 255; ++_loc1)
        {
            _loc2 = (_loc2 + com.mgame.webMall.rc4.RC4.sbox[_loc1] + com.mgame.webMall.rc4.RC4.mykey[_loc1]) % 256;
            _loc3 = com.mgame.webMall.rc4.RC4.sbox[_loc1];
            com.mgame.webMall.rc4.RC4.sbox[_loc1] = com.mgame.webMall.rc4.RC4.sbox[_loc2];
            com.mgame.webMall.rc4.RC4.sbox[_loc2] = _loc3;
        } // end of for
    } // End of the function
    static function calculate(plaintxt, psw)
    {
        com.mgame.webMall.rc4.RC4.initialize(psw);
        var _loc1 = 0;
        var _loc2 = 0;
        var _loc9 = new Array();
        var _loc7;
        var _loc5;
        var _loc6;
        for (var _loc3 = 0; _loc3 < plaintxt.length; ++_loc3)
        {
            _loc1 = (_loc1 + 1) % 256;
            _loc2 = (_loc2 + com.mgame.webMall.rc4.RC4.sbox[_loc1]) % 256;
            _loc5 = com.mgame.webMall.rc4.RC4.sbox[_loc1];
            com.mgame.webMall.rc4.RC4.sbox[_loc1] = com.mgame.webMall.rc4.RC4.sbox[_loc2];
            com.mgame.webMall.rc4.RC4.sbox[_loc2] = _loc5;
            var _loc4 = (com.mgame.webMall.rc4.RC4.sbox[_loc1] + com.mgame.webMall.rc4.RC4.sbox[_loc2]) % 256;
            _loc7 = com.mgame.webMall.rc4.RC4.sbox[_loc4];
            _loc6 = plaintxt[_loc3] ^ _loc7;
            _loc9.push(_loc6);
        } // end of for
        return (_loc9);
    } // End of the function
    static function charsToHex(chars)
    {
        var _loc4 = new String("");
        var _loc3 = new Array("0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f");
        for (var _loc1 = 0; _loc1 < chars.length; ++_loc1)
        {
            _loc4 = _loc4 + (_loc3[chars[_loc1] >> 4] + _loc3[chars[_loc1] & 15]);
        } // end of for
        return (_loc4);
    } // End of the function
    static function hexToChars(hex)
    {
        var _loc3 = new Array();
        for (var _loc1 = hex.substr(0, 2) == "0x" ? (2) : (0); _loc1 < hex.length; _loc1 = _loc1 + 2)
        {
            _loc3.push(parseInt(hex.substr(_loc1, 2), 16));
        } // end of for
        return (_loc3);
    } // End of the function
    static function charsToStr(chars)
    {
        var _loc3 = new String("");
        for (var _loc1 = 0; _loc1 < chars.length; ++_loc1)
        {
            _loc3 = _loc3 + String.fromCharCode(chars[_loc1]);
        } // end of for
        return (_loc3);
    } // End of the function
    static function strToChars(str)
    {
        var _loc3 = new Array();
        for (var _loc1 = 0; _loc1 < str.length; ++_loc1)
        {
            _loc3.push(str.charCodeAt(_loc1));
        } // end of for
        return (_loc3);
    } // End of the function
    static var sbox = new Array(255);
    static var mykey = new Array(255);
} // End of Class
