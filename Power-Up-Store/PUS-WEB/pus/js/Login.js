/*
 * Login
 * */
var Login = {
    _frm : null
    ,_id : null
    ,_password : null
    ,_chtype : null
    ,_pannelP : null
    ,_pannelS : null
    ,_init : function(){
        try{
            this._frm = document.getElementById("frm");
            this._id = document.getElementById("id");
            this._password = document.getElementById("password");
            this._rq = document.getElementById("rq");
        }catch(e){}
        try{
            this._chtype = document.getElementById("types");
        }catch(e){}
        try{
            this._pannelP = document.getElementById("pannelP");
            this._pannelS = document.getElementById("pannelS");
        }catch(e){}
    }
    
    /**
     * Login
     * @returns {unresolved}
     */
    ,_Login : function(){
        this._init();
        LodingBox._Loding("pannelP");
        
        var _path = "/";
        if(this._rq.value != ""){
            _path = base64_decode(this._rq.value);
            _path = _path.replace(/__/gi, "");
            
            
            if(_path.indexOf("forum.nttgame.com") > 0){
                try{
                var _path_sp = _path.split("-");
                var _path_val_sp = "", _path_val = "";
                if(_path_sp.length > 0){
                    _path_val_sp = _path_sp[0].split("?");
                    _path_val = _path_val_sp[1];
                }
                if(_path.indexOf("showthread.php") > 0){
                    _path = _knight + "/community/forum.gcs?t="+_path_val;
                }else if(_path.indexOf("forumdisplay.php") > 0){
                    _path = _knight + "/community/forum.gcs?f="+_path_val;
                }
                
                }catch(e){
                    //_path = _knight + "/community/forum.gcs";
                }
            }
        }
        if(!this._LoginCheck('Box')){
            return ;
        }else{
            
            var result = $.ajax({
                type: "POST",
                url: "/Login/Logins/LoginProcess",
                dataType: "text",
                data: $('#frm').serialize(),
                cache: false,
                async: false,
                error: function (XMLHttpRequest, textStatus, errorThrown) {
                      //f_errormsg("error :"+XMLHttpRequest.responseText);
                      LodingBox._close();
                        }
            }).responseText;
            LodingBox._close();
            try{
                    var data = eval('(' + result + ')');
                    if (data.error == 100) {
                           Box._open('SUCCESS!', 'You have successfully logged in.', '<a href="'+ _path +'"><div class="blue_bt_180_center">Continue</div></a>' );
                           setTimeout(function(){
                               document.location.href = _path;
                           }, 3000);
                    }else {
                        if(data.error == -3 && data.dberror == -2){
                            Box._open('FAILED!', "Has already signed.<br>Do you want to logout and then log-in?", '<a href="'+ LOGOUT +'/'+ base64_encode(document.location.href) +'"><div class="blue_bt_180_center">Re-Login</div></a>' );
                        }else{
                            Box._open('FAILED!', data.message, '<a href="javascript:Box._close();"><div class="blue_bt_180_center">Try Again</div></a>' );
                        }
                    }
            } catch (e){
                Box._open('FAILED!', 'Message :' + e, '' );
            }
        }

    }
    
    /**
     * Login Check
     * @returns {unresolved}
     */
    ,_Login2 : function(){
        this._init();
        LodingBox._Loding("pannelP");
        
        if(!this._LoginCheck()){
            return ;
        }else{
            
            var result = $.ajax({
                type: "POST",
                url: "/Login/Logins/LoginCheckProcess",
                dataType: "text",
                data: $('#frm').serialize(),
                cache: false,
                async: false,
                error: function (XMLHttpRequest, textStatus, errorThrown) {
                      //f_errormsg("error :"+XMLHttpRequest.responseText);
                      LodingBox._close();
                        }
            }).responseText;
            LodingBox._close();
            try{
                    var data = eval('(' + result + ')');
                    if (data.error == 100) {
                            $("#pannelP").fadeOut("fast", function(){
                                $("#pannelS").fadeIn("fast").css({'height':'300'});
                            });
                    }else {
                        if(data.error == -3 && data.dberror == -2){
                            Box._open('FAILED!', "Has already signed.<br>Do you want to logout and then log-in?", '<a href="'+ LOGOUT +'/'+ base64_encode(document.location.href) +'"><div class="blue_bt_180_center">Re-Login</div></a>' );
                        }else{
                            Msg._show(  data.message );
                        }
                    }
            } catch (e){
                 Msg._show( 'Message :' + e);
            }
            
        }

    }
    
    /**
     * Resend Login check
     * @returns {undefined}
     */
    ,_Login2Resend  : function(){
            $("#pannelS").fadeOut("fast", function(){
                $("#pannelP").fadeIn("fast");
                this._password = "";
                document.getElementById("password").value ="";
                document.getElementById("password").focus();
            });
    }
    
    /**
     * Login check
     * @param {type} megtype
     * @returns {Boolean}
     */
    ,_LoginCheck : function( megtype ){
        this._init();
        if(megtype == ""){
            megtype='Box';
        }

        if(this._id.value == "") {
                LodingBox._close();
                if(megtype=='Box'){
                    Box._open('FAILED!', 'Please enter the ID. ID can not contain any spaces.', '' );
                }else{
                    Msg._show( 'Please enter the ID. ID can not contain any spaces.');
                }
                this._id.focus();
                this._id.select();
                return false;
        } else if(this._password.value == "") {
                LodingBox._close();
                if(megtype=='Box'){
                    Box._open('FAILED!', 'Please enter the password. You can not put a space in the password.', '');
                }else{
                    Msg._show( 'Please enter the password. You can not put a space in the password.');
                }
                this._password.focus();
                this._password.select();
                return false;
        } else {
            return true;             
        }
    }
    
    ,_Login3 :  function(){
        this._init();
        
        if(this._id.value == "") {
                alert('FAILED!'+ '\nPlease enter the ID. ID can not contain any spaces.' );
                this._id.focus();
                this._id.select();
                return;
        } else if(this._password.value == "") {
                alert('FAILED!'+ '\nPlease enter the password. You can not put a space in the password.');
                this._password.focus();
                this._password.select();
                return;
        } 
        
        var _path = "/";
        if(this._rq.value != ""){
            _path = base64_decode(this._rq.value);
        }
        
        var result = $.ajax({
            type: "POST",
            url: _www + "/Login/Logins/LoginProcess",
            dataType: "text",
            data: $('#frm').serialize(),
            cache: false,
            async: false,
            error: function (XMLHttpRequest, textStatus, errorThrown) {
                  //f_errormsg("error :"+XMLHttpRequest.responseText);
                  LodingBox._close();
                    }
        }).responseText;
        LodingBox._close();
        try{
                var data = eval('(' + result + ')');
                if (data.error == 100) {
                       alert('You have successfully logged in.');
                       top.document.location.href = _path;
                       return;
                }else {
                    alert(data.message);
                    return;
                }
        } catch (e){
            alert('FAILED!', 'Message :' + e);
        }
    }
    
    
    
    /**
     * Fogot ID / PW / Verification
     * @param {int} 1:id / 2:pw / 3:Verification
     * @returns {undefined}
     */
    ,_Forgot : function(types){
        if(types == ""){
            types = 1;
        }
        var _url, subtitle;
        switch(types){
            case 1 :
                _url = '/Signin/Signins/ForgotID';
                subtitle = "Forgot Your ID";
                break;
            case 2 :
                _url = '/Signin/Signins/ForgotPW';
                subtitle = "Forgot Your Password";
                break;
            case 3 :
                _url = '/Signin/Signins/ResendVerification';
                subtitle = "Re-send verification Email";
                break;
        }

        Box._isTitle = true;
        Box._isSubTitle = true;
        Box._big = true;
        Box._fixed = false;
        Box._top = "150px";
        Box._open2('FORGOT INFORMATION', '', '',subtitle);
        $(".boxContent").html("<div style='width:100%; text-align:center;'><img src='"+ IMG_URL +"/loading.gif'></div>");
        setTimeout(function(){$(".boxContent").load(_url);},300);

    }
    
    /**
     * Forgot Process Complete
     * @param {object} type, id, email
     * @returns error
     */
    ,_ForgotProcess : function(obj){
            
            var email_sp = obj.email.split("@");
            
            var result = $.ajax({
                type: "POST",
                url: "/Signin/Signins/ForgotProcess",
                dataType: "text",
                data: obj,
                cache: false,
                async: false,
                error: function (XMLHttpRequest, textStatus, errorThrown) {
                      //f_errormsg("error :"+XMLHttpRequest.responseText);
                      LodingBox._close();
                        }
            }).responseText;
            LodingBox._close();
            Box._top = "150px";
            try{
                    var data = eval('(' + result + ')');
                    if (data.error == 0) {
                        Box._open2('FORGOT INFORMATION', '<div class="dcenter"><table class="loginbox tcenter"><tr><td>Your Information has been send to your e-mail address.</td></tr></table></div>', '<div class="dcenter"><table class="loginbox tcenter" style="margin-left:-60px;"><tr><td><a href="http://'+ email_sp[1] +'" target="_blank"><div class="blue_bt_180_center">GOTO '+ email_sp[1] +'</div></a></td></tr></table></div>','SUCCESS');
                    }else {
                        Box._open2('FAILED!', '<div class="dcenter"><table class="loginbox tcenter"><tr><td>'+data.message+'</td></tr></table></div>', '<div style="margin-left:85px;"><table class="loginbox tcenter"><tr><td><a href="javascript:Login._Forgot('+ obj.type +');"><div class="blue_bt_180_center">Try Again</div></a></td></tr></table></div>', 'Failed to send e-mail!');
                    }
            } catch (e){
                Box._open2('FAILED!', '<div class="dcenter"><table class="loginbox tcenter"><tr><td>Message :' + e + '</td></tr></table></div>', '<div style="margin-left:85px;"><table class="loginbox tcenter" ><tr><td><a href="javascript:Login._Forgot('+ obj.type +');"><div class="blue_bt_180_center">Try Again</div></a></td></tr></table></div>', 'Failed to send e-mail!' );
            }
    }
    
    /**
     * Forgot ID
     * @returns -
     */
    ,_ForgotID : function(){
        var email = document.getElementById("email");
        if(email.value == "") {
                Msg._show( 'Please enter your new E-mail Address');
                email.focus();
                email.select();
                return;
        } 
        if(!util.emailCheck(email.value)){
                Msg._show( 'Invalid E-mail.');
                email.focus();
                email.select();
                return;
        }
        var data = {type:1, id:'', email:email.value};
        this._ForgotProcess(data);
    }
    
    /**
     * Forgot PW
     * @returns -
     */
    ,_ForgotPW : function(){
        var pid = document.getElementById("pid");
        var email = document.getElementById("email");
        if(pid.value == "") {
                Msg._show( 'Please enter your id');
                pid.focus();
                pid.select();
                return;
        }         
        if(email.value == "") {
                Msg._show( 'Please enter your new E-mail Address');
                email.focus();
                email.select();
                return;
        } 
        if(!util.emailCheck(email.value)){
                Msg._show( 'Invalid E-mail.');
                email.focus();
                email.select();
                return;
        }
        var data = {type:2, id:pid.value, email:email.value};
        this._ForgotProcess(data);
    }
    
    /**
     * Resend Verification EMail
     * @returns -
     */
    ,_ResendVerificationEMail : function(){
        var pid = document.getElementById("pid");
        var email = document.getElementById("email");
        if(pid.value == "") {
                Msg._show( 'Please enter your id');
                pid.focus();
                pid.select();
                return;
        }         
        if(email.value == "") {
                Msg._show( 'Please enter your new E-mail Address');
                email.focus();
                email.select();
                return;
        } 
        if(!util.emailCheck(email.value)){
                Msg._show( 'Invalid E-mail.');
                email.focus();
                email.select();
                return;
        }
        var data = {type:3, id:pid.value, email:email.value};
        this._ForgotProcess(data);
    }
    
};


$(document).ready(function() {
    //setVolatileBehavior(document.getElementById('id'),'black','gray','User ID');
    //setVolatileBehavior(document.getElementById('password'),'black','gray','');
});