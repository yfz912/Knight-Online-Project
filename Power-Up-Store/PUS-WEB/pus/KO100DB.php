<?php

/**
 * @copyright 2013
 */
 class KO100DB
 {
    public $Response;
    public $Signature;
    public $ResponseData;
    private $Params = array();
    public $responseArray = array();
    private $Socket;
    private $error;
    
    function GetArray()
    {
        
        $exp = explode("\n",$this->Response);
        foreach( $exp as $b )
            array_push($this->responseArray, $b);
    
        return $this->responseArray;
    }
    
    function AddParameter($parameter)
    {
        array_push($this->Params, $parameter);
    }
   
    function GetResponse()
    {
   
        
       if( !( $this->Socket = fsockopen("46.45.142.138",443,$err,$errstr,30) ) )
        {
            $this->error = -1;
            return -1;
        }

        
        $OutData = $this->Signature."\n";

        foreach ($this->Params as $param) {
            $OutData .= $param."\n";
        }   
        fwrite($this->Socket, $OutData);
        
        while (!feof($this->Socket))
        {
            $this->Response .= fgets($this->Socket, 128);
        }
        $arr = $this->GetArray();
        return $arr[0];
        
    }
 }

?>