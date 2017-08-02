class com.mgame.webMall.rc4.EncryptionTypes
{
    function EncryptionTypes()
    {
        _RC4 = com.mgame.webMall.rc4.EncryptionTypes.RC4();
    } // End of the function
    static function RC4()
    {
        return (com.mgame.webMall.rc4.EncryptionTypes._RC4);
    } // End of the function
    static var _RC4 = com.mgame.webMall.rc4.RC4;
} // End of Class
