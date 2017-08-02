class com.mgame.webMall.rc4.Encryption
{
    var input, encryptionType, mode;
    function Encryption(type, input, key, mode, keySize, blockSize)
    {
        if (type != null)
        {
            this.setEncryptionType(type);
        } // end if
        if (input != null)
        {
            this.setInput(input);
        } // end if
        if (key != null)
        {
            this.setKey(key);
        } // end if
        if (mode != null)
        {
            this.setMode(mode);
        } // end if
        switch (type)
        {
            case com.mgame.webMall.rc4.RC4:
            {
                isTEAorRC4 = true;
                break;
            } 
        } // End of switch
    } // End of the function
    function encrypt()
    {
        if (!isTEAorRC4)
        {
            throw new Error("Deze functie is ongeldig voor het gekozen encryptietype!  Functie \'encrypt\' kan enkel aangeroepen worden voor een TEA of RC4 encryptie.");
        } // end if
        if (this.getInput().length > 0 && this.getKey().length > 0)
        {
            this.setInput(this.getEncryptionType().encrypt(this.getInput(), this.getKey()));
        }
        else if (this.getInput().length <= 0)
        {
            throw new Error("Input string bestaat niet");
        }
        else if (this.getKey().length <= 0)
        {
            throw new Error("Geen key opgegeven voor de encryptie");
        } // end else if
    } // End of the function
    function decrypt()
    {
        if (!isTEAorRC4)
        {
            throw new Error("Deze functie is ongeldig voor het gekozen encryptietype!  Functie \'decrypt\' kan enkel aangeroepen worden voor een TEA of RC4 encryptie.");
        } // end if
        if (this.getInput().length > 0 && this.getKey().length > 0)
        {
            this.setInput(this.getEncryptionType().decrypt(this.getInput(), this.getKey()));
        }
        else if (this.getInput().length <= 0)
        {
            throw new Error("Input string bestaat niet");
        }
        else if (this.getKey().length <= 0)
        {
            throw new Error("Geen key opgegeven voor de encryptie");
        } // end else if
    } // End of the function
    function getInput()
    {
        return (input);
    } // End of the function
    function setEncryptionType(et)
    {
        encryptionType = et;
    } // End of the function
    function getEncryptionType()
    {
        return (encryptionType);
    } // End of the function
    function setInput(str)
    {
        input = str;
    } // End of the function
    function getKey()
    {
        return (key);
    } // End of the function
    function setKey(str)
    {
        key = str;
    } // End of the function
    function getMode()
    {
        return (mode);
    } // End of the function
    function setMode(str)
    {
        mode = str;
    } // End of the function
    var key = "lolsong_hear";
    var isTEAorRC4 = false;
} // End of Class
