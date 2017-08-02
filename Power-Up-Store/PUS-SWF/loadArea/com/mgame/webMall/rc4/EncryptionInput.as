class com.mgame.webMall.rc4.EncryptionInput
{
    function EncryptionInput(value)
    {
    } // End of the function
    function inputData(value, type)
    {
        if (value.length < 1)
        {
            return ("");
        } // end if
        value = escape(value);
        if (type == 1)
        {
            encryption = new com.mgame.webMall.rc4.Encryption(com.mgame.webMall.rc4.EncryptionTypes.RC4(), value, com.mgame.webMall.main.MainData.__get__hiddenKey(), null, null, null);
            encryption.decrypt();
        }
        else
        {
            encryption = new com.mgame.webMall.rc4.Encryption(com.mgame.webMall.rc4.EncryptionTypes.RC4(), value, com.mgame.webMall.main.MainData.__get__thisKey(), null, null, null);
            encryption.encrypt();
        } // end else if
        retVal = encryption.getInput();
        return (retVal);
    } // End of the function
    var encryption = null;
    var retVal = null;
} // End of Class
