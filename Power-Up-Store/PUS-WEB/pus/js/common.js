/*
 * Welcome NttGames  
 * Common
 */
var _returnEventStatus="::: WELCOME NTT PORTAL::KNIGHT ONLINE :::";
var name = "common.js";
var version = "1.0";
var domain = location.host.substr(location.host.indexOf(".")+1);   document.domain	 = domain;

/*
 * Block Options
 * emails
 */
var limitEmail = ['mailinator2.com','sogetthis.com','mailin8r.com','mailinator.net','spamherelots.com','thisisnotmyrealemail.com','mailinator.com','guerrillamail.com','tempemail.net','mailcatch.com','trashmail.net','zoemail.net','incognitomail.net','spamgourmet.com','litedrop.com','hidzz.com','pookmail.com','hushmail.com','spamavert.com','blockfilter.com','deadaddress.com','wh4f.org','spambox.us','mt2009.com','spam.la','tempinbox.com','saynotospams.com','makemoneytradingstocks.org','spamcero.com','spamcorptastic.com','20minutemail.com','signed-first-edition.com','tempe-mail.com','dumpyemail.com','shieldemail.com','dodgit.com','dandikmail.com','maileater.com','haltospam.com','nospamfor.us','nospam4.us','spamfree24.org','spamfree24.com','spamfree24.eu','spamfree24.de','spamfree24.info','spamfree24.net','tempomail.fr','mint.us.to','skeefmail.com','slopsbox.com'];

/**
 * Script Util
 * @type type
 */
var util = {
    
    enter_key : function enter_key(functions){
            if(event.keyCode == 13) {
                    eval(functions + '()');
            }
    }

    /**
     * Number Check
     * @returns {undefined}
     */
    ,numbercheck : function(val){
        var check=/[^0-9]/gi;
        if (check.test(val)){
                return false;
        }else{
                return true;
        }
    }

    /**
     * endter key number only
     * @param {type} e
     * @param {type} decimal
     * @returns {Boolean}
     */
    ,numbersonly : function (e, decimal) {
            var key;
            var keychar;

            if (window.event) {
                    key = window.event.keyCode;
            } else if (e) {
                    key = e.which;
            } else {
                    return true;
            }
            keychar = String.fromCharCode(key);

            if ((key == null) || (key == 0) || (key == 8) || (key == 9) || (key == 13) || (key == 27)) {
                    return true;
            } else if ((("0123456789").indexOf(keychar) > -1)) {
                    return true;
            } else if (decimal && (keychar == ".")) {
                    return true;
            } else
                    return false;
    }
    ,_getObj : function (obj){
        try{
            var _obj = document.getElementById(obj);
            return _obj;
        }catch(e){
            return null;
        }
    }
    ,_getVal : function (obj){
        var _obj = null;
        if(this._is_object(obj)){
            _obj = obj;
        }else{
            _obj = this._getObj(obj);
        }
        try{return this._ignoreSpaces(_obj.value); }
        catch(e){return '';}
    }
    ,_is_object : function (obj){
         return (typeof(obj)!='object')?false:true;
         return (typeof(obj)=='object');
    }
    
    ,_ignoreSpaces : function (string){
            var temp = "";
            string = '' + string;
            splitstring = string.split(" ");
            for(i = 0; i < splitstring.length; i++)
            temp += splitstring[i];
            return temp;
    }
    
    /**
     * Email Check
     * @param {string} email
     * @return true / false
     */
    ,emailCheck : function (obj) {
            var emailAvail = /^[._a-zA-Z0-9-]+@[._a-zA-Z0-9-]+\.[a-zA-Z]+$/;
            if(!emailAvail.test(obj)) return false;
            for(var i=0;i<limitEmail.length;i++) {
                    if(obj.substr(obj.indexOf('@')+1).trim() == limitEmail[i]) return false;
            }
            return true;
    }
    
    ,_checkID : function (el) {
            var pattern = /^[a-zA-Z\d]+$/;
            return (pattern.test(el)) ? true : false;
    }
    ,_checkPassword : function (password) {
            var check1 = /.*[0-9].*/i;
            var check2 = /.*[a-zA-Z].*/i;
            var check3 = /[!"#$%&'()*+,-.:;?@[\\\]_{|}~]/i;

            if(check1.test(password)) {
                    return true;
            } else if(check2.test(password)) {
                    return true;
            } else if(check3.test(password)) {
                    return true;
            } else {
                    return false;
            }
    }
    ,_checkNickName : function (nickname) {
            var check1 = /.*[0-9].*/i;
            var check2 = /.*[a-zA-Z].*/i;
            var check3 = /[!#$%&()*+,-.:;@[]_{|}~]/i;

            if(check1.test(nickname)) {
                    return true;
            } else if(check2.test(nickname)) {
                    return true;
            } else if(check3.test(nickname)) {
                    return true;
            } else{
                    return false;
            }
    }
    ,_maxbyteCheck : function (el, maxbyte) {
        
            if (el != "") {
                    var len = 0;
                    for(j=0; j<el.length; j++) {
                            var str = el.charAt(j);
                            len += (str.charCodeAt() > 128) ? 2 : 1
                    }
                    if (len > maxbyte) {
                            return false;
                    }else{
                            return true;
                    }
            }
    }

    ,_minbyteCheck : function (el, minbyte) {
            if (el != "") {
                    var len = 0;
                    for(j=0; j<el.length; j++) {
                            var str = el.charAt(j);
                            len += (str.charCodeAt() > 128) ? 2 : 1
                    }
                    if (parseInt(len) < parseInt(minbyte)) {
                            return false;
                    }else{
                            return true;
                    }
            }
    }
    
    ,_is_number : function(val){
        var check=/[^0-9]/gi;
        if (check.test(val)){
                return false;
        }else{
                return true;
        }
    }
    
    
};


var serverutil = {
    
    isCheckServerInfor : function(type, val){
        var _serverurl = '/account/create_id_check.gcs';
        var result = '';
        switch(type){
            case "id" :
                result = ajaxRequest(null,_serverurl,'joinId='+ val);
                break;
            case "email" :
                result = ajaxRequest(null,_serverurl,'joinEmail='+ val);
                break;
            case "name" :
                result = ajaxRequest(null,_serverurl,'joinName='+ val);
                break;
        }
        if(result == 1){
                return true;
        }else{
                return false;
        }
    }

    
};


var Msg = {
  _id : "Msg"
  ,_pos : true
  ,_set : function(){
      try{ var box = document.getElementById("msg_box").style.display; return ;}catch(e){}
      var html = "";
            html += "<style>";
            if(this._pos){
                html += "#msg_box { display:none;  position:absolute;  _position:absolute; }";
            }else{
                html += "#msg_box { display:none; }";
            }
            html += "</style>";
          html += "<div id='msg_box'><br/><img src='"+IMG_URL+"/warning.jpg' /><span class='yellow2'><b>Warning: </b></span><span id='msg_container' class='red'>{content}</span></div>";
      $('#errormsg').append(html);
  }
  ,_show : function (content){
            this._set();
            $('#msg_container').html(content);
            
            $('#msg_box').click( function() { Box._close(); });
            $("#msg_box").fadeIn("fast").delay(2000).fadeOut("slow");
        }
  , _hidden : function (){
      $("#msg_box").fadeOut("slow");
  }
};

/*Layer Box*/
var Box = {
    _id : "box"
    ,_w : "100"
    ,_h : "50"
    ,_top : "150px"
    ,_big : false
    ,_isTitle : true
    ,_isSubTitle : true
    ,_isButton : true
    ,_fixed : true
    
    ,_set : function(){
        this._reset();
        //try{ var box = document.getElementById("popup_box").style.display; }catch(e){}
        
        var html = "";
        if(!this._big){
            //html = "<link rel='stylesheet' type='text/css' href='"+CSS_URL+"/popup.css' />";
            html = "<style>";
            html += "#popup_box { display:none; position:fixed;  _position:absolute;  min-height:"+ this._h +"px;  min-width:"+ this._w +"px; top:"+ this._top +"; z-index:100;  }";
            html += "#popup_container { position:absolute; left:0; top:0; background: #000000; width:100%; min-height:100%; height:"+$(document).height()+"px }";
            html += "</style>";
            html += "<div id='popup_box'>";
            html += "<table class='layerpopup'><tr><td class='layerpopup_top'></td></tr>";
            html += "<tr><td class='layerpopup_middle_close'><a href='javascript:Box._close();' id='popupBoxClose'><p>CLOSE&nbsp;<img src='"+IMG_URL+"/closex.jpg' /></p></a></td></tr>";
            html += "<tr><td class='layerpopup_middle'>";
            if(this._isTitle){
            html += "<h1 class='boxTitle'>{title}</h1>";
            }
            html += "<p class='boxContent'>{content}</p>";
            if(this._isButton){
            html += "<div class='boxBtn'>{button}</div>";
            }
            html += "</td></tr><tr><td class='layerpopup_bottom'></td></tr></table>";
            html += "</div><div id='popup_container'></div>";
        }else{
            //html = "<link rel='stylesheet' type='text/css' href='"+CSS_URL+"/popup.css' />";
            html = "<style>";
            html += "#popup_box { display:none; position:fixed;  _position:absolute;  min-height:"+ this._h +"px;  min-width:"+ this._w +"px; top:"+ this._top +";  z-index:100;  }";
            html += "#popup_container { position:absolute; left:0; top:0; background: #000000; width:100%; min-height:100%; height:"+$(document).height()+"px}";
            html += "</style>";
            html += "<div id='popup_box'>";
            html += "<table class='layerpopup800'><tr><td class='layerpopup800_top'></td></tr>";
            html += "<tr><td class='layerpopup800_middle_close'><a href='javascript:Box._close();' id='popupBoxClose'><p>CLOSE&nbsp;<img src='"+IMG_URL+"/closex.jpg' /></p></a></td></tr>";
            //html += "<tr><td class='layerpopup800_middle'><div class='tcenter'><img src='"+IMG_URL+"/bar740_30.png' /></div></td></tr>";
            html += "<tr><td class='layerpopup800_middle'>";
            if(this._isTitle){
            html += "<h1 class='boxTitle'>{title}</h1>";
            }
            if(this._isSubTitle){
            html += "<h2 class='boxSubTitle'>{subtitle}</h2>";
            }
            html += "<p class='boxContent'>{content}</p>";
            if(this._isButton){
            html += "<p class='dtcenter'><span class='boxBtn'></span></p>";
            }
            html += "</td></tr>";
            html += "<tr><td class='layerpopup800_bottom'></td></tr></table>";
            html += "</div><div id='popup_container'></div>";
        }
            $('#msgbox').html(html);  //append
    }
    
    ,_reset : function(){
        try{ 
            //var box = document.getElementById("popup_box").style.display; 
            //$("#popup_box").remove();
            //$("#popup_container").remove();
            $('#msgbox').html("");
        }catch(e){}
        return ;
    }
    
    ,_open : function(title, content, button){
            this._big = false;
            //this._reset();
            this._set();
            var _img = "";
            if(title == "SUCCESS!"){
                _img = "<img src='"+ IMG_URL +"/success.jpg'>";
            }else if(title == "FAILED!"){
                _img = "<img src='"+ IMG_URL +"/failed.jpg'>";
            }else{
                _img = title;
            }
            $('.boxTitle').html(_img);
            $('.boxContent').html(content);
            try{
                $('.boxBtn').html("").append(button);
            }catch(e){}
            
            $("#popup_container").fadeIn("fast", function(){
            	$('#popup_box').fadeIn("slow").center();
            }).css({ "opacity": "0.8"  });
            
            $('#popupBoxClose').click( function() { Box._close(); });
            $('#popup_container').click( function() { Box._close(); });
    }
    
    ,_open2 : function(title, content, button, subtitle){
            
            this._big = true;
            //this._reset();
            this._set();
            $('.boxTitle').html(title);
            $('.boxContent').html(content);
            $('.boxBtn').html("").append(button);
            $('.boxSubTitle').html("").append(subtitle);
            if(this._fixed){
                $("#popup_container").fadeIn("fast", function(){
                    try{
                        $('#popup_box').fadeIn("slow").wcenter("fixed");
                    }catch(e){
                        $('#popup_box').fadeIn("slow").css("position","fixed").css("left", (Math.max(0, (($(window).width() - $('#popup_box').outerWidth()) / 2) + $(window).scrollLeft()) ) + "px");
                    }
                }).css({ "opacity": "0.8"  });
            }else{
                $("#popup_container").fadeIn("fast", function(){
                    try{
                        $('#popup_box').fadeIn("slow").wcenter("");
                    }catch(e){
                        $('#popup_box').fadeIn("slow").css("position","absolute").css("left", (Math.max(0, (($(window).width() - $('#popup_box').outerWidth()) / 2) + $(window).scrollLeft()) ) + "px");
                    }
                }).css({ "opacity": "0.8"  });
            }
            
            $('#popupBoxClose').click( function() { Box._close(); });
            $('#popup_container').click( function() { Box._close(); });
    }
    
    ,_open3 : function(title, content, button, _top, _delay){
            this._big = false;
            //this._reset();
            this._set();
            $('.boxTitle').html(title);
            $('.boxContent').html(content);
            try{
                $('.boxBtn').html("").append(button);
            }catch(e){}
            
            $("#popup_container").fadeIn("fast", function(){
                if(_top > 0){
                    $('#popup_box').fadeIn("slow").tcenter(_top);
                }else{
                    $('#popup_box').fadeIn("slow").center();
                }
            }).css({ "opacity": "0.8"  }).delay(_delay * 1000).fadeOut("fast", function(){
                Box._close();
            });
            
            $('#popupBoxClose').click( function() { Box._close(); });
            $('#popup_container').click( function() { Box._close(); });
    }
    
    ,_close : function(){
            $('#popup_box').fadeOut("slow", function(){
            	$("#popup_container").fadeOut("fast");
                Box._reset();
                //$('#msgbox').html("");
            });
    }
    ,_resize : function(){
        if(this._fixed){
            $('#popup_box').wcenter("fixed");
        }else{
            $('#popup_box').wcenter("");
        }
    }
    
};

/**
 * Open box
 * @type type
 */
var LodingBox = {
    _sID : null
    ,_tID : null

    ,_set : function(){
        
        try{ var box = document.getElementById("loding_box").style.display; $("#loding_box").remove(); }catch(e){}
        
        var html = "<style>";
            html += "#loding_box { position:absolute; left:47%; z-index:100; }";
            html += "#loding_container {position:absolute; left:0; top:0; background: #000000; width:100%; height:100%; opacity:0.4; filter:alpha(opacity=40); z-index:100;}";
            html += "</style>";
            html += "<div id='loding_box'>";
            html += "<img src='"+ IMG_URL +"/loading.gif'>";
            html += "</div>";
            html += "<div id='loding_container'>&nbsp;</div>";
            $('#'+this._tID).prepend(html);
    }
    ,_Loding : function (tid){
            this._tID = tid;
            this._set();

            $("#loding_container").fadeIn("fast", function(){
            	$('#loding_box').fadeIn("slow");
            }); //.css({ "opacity": "0.5"  });
    }
    ,_close : function (){
            try{
                $('#loding_box').fadeOut("slow", function(){
                    $("#loding_container").fadeOut("fast");
                });
            }catch(e){}
    }
    ,_complete : function (sID){
            this._sID = sID;
            try{
                $('#loding_box').fadeOut("slow", function(){
                    $("#loding_container").fadeOut("fast");
                }).delay(1000);
            }catch(e){}
            $("#"+this._sID).fadeIn();
    }
    
}


/**
 * Policy Box
 * @returns {undefined}
 */
var openPolicy = function(types){
    var _dPolicy = document.getElementById("dPolicy");
    if(_dPolicy.style.display == "none" || _dPolicy.style.display == ""){
        $("#dPolicy").css({"position":"fixed","width":"780px","height":"auto","top":"50px","zIndex":"999"});
        var url = _www + "/files/Policy.html?types="+types+"&frame=false";
        $("#dBlank").html('<div style="position:absolute; z-index:999; left:0; top:0; background: #000000; opacity:0.8; filter:alpha(opacity=80); width:100%; min-height:100%; height:'+$(document).height()+'px"><div>').fadeIn("fast");
        $("#dPolicy").fadeIn().load(url, function(){
               $(this).fadeIn("fast"); //function(){}).css({ "opacity": "0.5"  }
        }).wcenter("fixed");
    }else{
        $("#dBlank").html("").fadeOut();
        $("#dPolicy").fadeOut();
    }
}

/**
 * Policy Box
 * @returns {undefined}
 */
var openPolicyGlobal = function(types){
    var _dPolicy = document.getElementById("dPolicy");
    var _w = 800;
    var _h = 780;
    if(_dPolicy.style.display == "none" || _dPolicy.style.display == ""){
        _dPolicy.style.position = "fixed";
        _dPolicy.style.width = _w +"px";
        _dPolicy.style.height = _h + "px";
        _dPolicy.style.top = "50px";
        _dPolicy.style.zIndex = "1000";
        var url = _www + "/files/Policy.html?types="+types+"&frame=true";
        $("#dBlank").html('<div style="position:absolute; z-index:900; left:0; top:0; background: #000000; opacity:0.8; filter:alpha(opacity=80); width:100%; min-height:100%; height:'+$(document).height()+'px"><div>').fadeIn("fast").css({ "opacity": "0.5"  });
        $("#dPolicy").fadeIn().css("display","block").html('<iframe src="'+ url +'" width="'+_w+'" height="'+_h+'" scrolling="no" frameborder="0" style="border:none"  allowtransparency="true"></iframe>').wcenter("fixed");
    }else{
        $("#dBlank").html("").fadeOut();
        $(_dPolicy).fadeOut();
    }
}


/**
 * Login
 * @param {strint} return code
 * @returns {undefined}
 */
var openLogin = function(rq){
    var _dBlank = document.getElementById("dBlank");
    var _w = 524;
    var _h = 400;
    var _loginbox = null;
    var _loginbg = null;
    if(rq != "close"){
        var url = _www + "/Api/Apis/LoginLayer?rq="+rq;
        var htmllogin = '<div id="loginbox" style="z-index:10001"><iframe src="'+ url +'" width="'+_w+'" height="'+_h+'" scrolling="no" frameborder="0" style="border:none"  allowtransparency="true"></iframe></div>';
        var htmlbg = '<div id="loginbg" onclick=\'openLogin("close")\' style="position:absolute; left:0; top:0; background: #000000; z-index:10000; width:100%; min-height:100%; height:'+ $(document).height() +'px; cursor:pointer;"></div>'; //<iframe scrolling="no" width="100%" height="'+ $(document).height() +'" height="100%" src="'+ _www +'/files/null.html" marginheight="0" marginwidth="0" frameborder="0" align="center" allowTransparency="false"></iframe>
        $(_dBlank).html(htmllogin + htmlbg);
        _loginbox = document.getElementById("loginbox");
        _loginbg = document.getElementById("loginbg");
        _loginbox.style.position = "absolute";
        _loginbox.style.width = _w +"px";
        _loginbox.style.height = _h + "px";
        _loginbox.style.top = "150px";
        $(_dBlank).css("display", "block");
        $(_loginbg).fadeIn("fast", function(){
                $(_loginbox).fadeIn().wcenter("absolute");
        }).css({ "opacity": "0.9"  });
    }else{
        $("#loginbox").fadeOut("fast");
        $("#loginbg").fadeOut("fast");
        $("#dBlank").fadeOut("fast");
    }
}

/**
 * all menu
 * @returns {undefined}
 */
var AllGame = function(){
    var _subment = $("#submenu");
    var _submenudown = $("#submenudown");
    
    if(_subment.css("display") == "none"){
        $("#submenudown").attr("src", IMG_URL+"/down_over.png");
        _subment.slideDown('fast', function(){});
    }else{
        $("#submenudown").attr("src", IMG_URL+"/down.png");
        _subment.slideUp('fast', function(){});
    }
};

/**
 * main moving
 * @returns {XMLHttpRequest}
 */
var MainMoving = function(movetype){
    
    var _container_intro = $("#container_intro");
    var _container_intro1 = $("#container_intro1");
    var _container_intro2 = $("#container_intro2");
    var _container_intro3 = $("#container_intro3");
    
    //alert(_container_intro1.hasClass('container_intro'));
    
    //Kinght
    if(movetype == 2){
        //_container_intro.fadeOut('slow', function () {
        //    _container_intro.fadeIn('slow');
        ///});
        _container_intro1.removeClass("container_intro").addClass("container_intro2");
        _container_intro2.fadeOut('slow', function () {
                    $("#container_intro2 p span#text").html("Players from around the globe join together for glory in Knight Online World. USKO offers highly acclaimed PvP, party play, and an intricate war system with in-game events daily.");
                    //$("#container_intro2 p a#link1").attr("href","/");
                    $("#container_intro2 p a#link1").attr("href",_knight);
                    _container_intro2.removeClass("container_intro").addClass("container_intro2");
                    _container_intro2.fadeIn('slow');
        });
        _container_intro3.removeClass("container_intro").addClass("container_intro2");
        
    //Kingdom
    }else{
        _container_intro1.removeClass("container_intro2").addClass("container_intro");
        _container_intro2.fadeOut('slow', function () {
                    $("#container_intro2 p span#text").html("Kingdom Online is a medieval based MMORPG with beautifully rendered characters, vast landscapes, and visual effects that fully immerse players.");
                    //$("#container_intro2 p a#link1").attr("href","/");
                    $("#container_intro2 p a#link1").attr("href",_kingdom);
            
                    _container_intro2.removeClass("container_intro2").addClass("container_intro");
                    _container_intro2.fadeIn('slow');
        });
        _container_intro3.removeClass("container_intro2").addClass("container_intro");
    }
    
    
}



/**
 * Ajax create
 */
function ajaxCreate() {
	var xmlHttp;

	if(window.ActiveXObject) {
		xmlHttp	=	new ActiveXObject("Microsoft.XMLHTTP");
	} else if(window.XMLHttpRequest) {
		xmlHttp	=	new XMLHttpRequest();
	}

	return xmlHttp;
}

/**
 * Request Ajax
 * @param {string} object id
 * @param {string} serverurl
 * @param {object} parameter
 * @param {blooen} xml ture / false
 * @param {blooen} output document.write ture / false
 * @returns {@exp;ajax@pro;responseText}
 */
function ajaxRequest(div,actionfile,param,xml,output) {
	var ajax = ajaxCreate();
	
	ajax.open(param ? "POST" : "GET",actionfile,false);	
	ajax.setRequestHeader("content-type","application/x-www-form-urlencoded");
	ajax.send(param ? param : null);

	if(ajax == null){
		alert("AJAX NOT SUPPORT.");
		history.back();
	}

	if(xml) {
		eval(div+"(ajax)");
	} else {
		if(div) {
			document.getElementById(div).innerHTML	=	ajax.responseText;
		}else if(output){
			document.write(ajax.responseText);
		}else{
			return ajax.responseText;
		}
	}
}



/**
 * base64_encode
 * @param {type} input
 * @returns {base64_encode.output}
 */
 var keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
function base64_encode(input) {
   input = escape(input);
   var output = "";
   var chr1, chr2, chr3 = "";
   var enc1, enc2, enc3, enc4 = "";
   var i = 0;

   do {
      chr1 = input.charCodeAt(i++);
      chr2 = input.charCodeAt(i++);
      chr3 = input.charCodeAt(i++);

      enc1 = chr1 >> 2;
      enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
      enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
      enc4 = chr3 & 63;

      if (isNaN(chr2)) {
         enc3 = enc4 = 64;
      } else if (isNaN(chr3)) {
         enc4 = 64;
      }

      output = output +
         keyStr.charAt(enc1) +
         keyStr.charAt(enc2) +
         keyStr.charAt(enc3) +
         keyStr.charAt(enc4);
      chr1 = chr2 = chr3 = "";
      enc1 = enc2 = enc3 = enc4 = "";
   } while (i < input.length);

   return output;
}

/**
 * base64_decode
 * @param {type} input
 * @returns {unresolved}
 */
function base64_decode(input) {
   var output = "";
   var chr1, chr2, chr3 = "";
   var enc1, enc2, enc3, enc4 = "";
   var i = 0;

   // remove all characters that are not A-Z, a-z, 0-9, +, /, or =
   var base64test = /[^A-Za-z0-9\+\/\=]/g;
   if (base64test.exec(input)) {
      alert("There were invalid base64 characters in the input text.\n" +
            "Valid base64 characters are A-Z, a-z, 0-9, '+', '/',and '='\n" +
            "Expect errors in decoding.");
   }
   input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");

   do {
      enc1 = keyStr.indexOf(input.charAt(i++));
      enc2 = keyStr.indexOf(input.charAt(i++));
      enc3 = keyStr.indexOf(input.charAt(i++));
      enc4 = keyStr.indexOf(input.charAt(i++));

      chr1 = (enc1 << 2) | (enc2 >> 4);
      chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
      chr3 = ((enc3 & 3) << 6) | enc4;

      output = output + String.fromCharCode(chr1);

      if (enc3 != 64) {
         output = output + String.fromCharCode(chr2);
      }
      if (enc4 != 64) {
         output = output + String.fromCharCode(chr3);
      }

      chr1 = chr2 = chr3 = "";
      enc1 = enc2 = enc3 = enc4 = "";

   } while (i < input.length);

   return unescape(output);
}



/*text Box default value seting*/
function setVolatileBehavior(elem, onColor, offColor, promptText){
    elem.addEventListener("change", function(){
        if (document.activeElement == elem && elem.value==promptText){
            elem.value='';
            elem.style.color = onColor;
        }
        else if (elem.value==''){
            elem.value=promptText;
            elem.style.color = offColor;
        }
    });
    elem.addEventListener("blur", function(){
        if (document.activeElement == elem && elem.value==promptText){
            elem.value='';
            elem.style.color = onColor;
        }
        else if (elem.value==''){
            elem.value=promptText;
            elem.style.color = offColor;
        }
    });
    elem.addEventListener("focus", function(){
        if (document.activeElement == elem && elem.value==promptText){
            elem.value='';
            elem.style.color = onColor;
        }
        else if (elem.value==''){
            elem.value=promptText;
            elem.style.color = offColor;
        }
    });
    elem.value=promptText;
    elem.style.color=offColor;
}

/**
 * TIMER FUNCTIOn
 * @param {type} time
 * @param {type} update
 * @param {type} complete
 * @returns {unresolved}
 */
function timer(time,update,complete) {
    var start = new Date().getTime();
    var interval = setInterval(function() {
        var now = time-(new Date().getTime()-start);
        if( now <= 0) {
            clearInterval(interval);
            complete();
        }
        else update(Math.floor(now/1000));
    },100);
    return interval;
}

/*image over up*/
function MM_openBrWindow(theURL,winName,features) { //v2.0
	window.open(theURL,winName,features);
}

function MM_swapImgRestore() { //v3.0
	var i,x,a=document.MM_sr; for(i=0;a&&i<a.length&&(x=a[i])&&x.oSrc;i++) x.src=x.oSrc;
}

function MM_preloadImages() { //v3.0
	var d=document; if(d.images){ if(!d.MM_p) d.MM_p=new Array();
	var i,j=d.MM_p.length,a=MM_preloadImages.arguments; for(i=0; i<a.length; i++)
	if (a[i].indexOf("#")!=0){ d.MM_p[j]=new Image; d.MM_p[j++].src=a[i];}}
}

function MM_findObj(n, d) { //v4.01
	var p,i,x;  if(!d) d=document; if((p=n.indexOf("?"))>0&&parent.frames.length) {
	d=parent.frames[n.substring(p+1)].document; n=n.substring(0,p);}
	if(!(x=d[n])&&d.all) x=d.all[n]; for (i=0;!x&&i<d.forms.length;i++) x=d.forms[i][n];
	for(i=0;!x&&d.layers&&i<d.layers.length;i++) x=MM_findObj(n,d.layers[i].document);
	if(!x && d.getElementById) x=d.getElementById(n); return x;
}

function MM_swapImage() { //v3.0
	var i,j=0,x,a=MM_swapImage.arguments; document.MM_sr=new Array; for(i=0;i<(a.length-2);i+=3)
	if ((x=MM_findObj(a[i]))!=null){document.MM_sr[j++]=x; if(!x.oSrc) x.oSrc=x.src; x.src=a[i+2];}
}

function MM_showHideLayers() { //v6.0
	var i,p,v,obj,args=MM_showHideLayers.arguments;
	for (i=0; i<(args.length-2); i+=3) if ((obj=MM_findObj(args[i]))!=null) { v=args[i+2];
		if (obj.style) { obj=obj.style; v=(v=='show')?'visible':(v=='hide')?'hidden':v; }
		obj.visibility=v; }
}

function MM_reloadPage(init) {  //reloads the window if Nav4 resized
	if (init==true) with (navigator) {if ((appName=="Netscape")&&(parseInt(appVersion)==4)) {
		document.MM_pgW=innerWidth; document.MM_pgH=innerHeight; onresize=MM_reloadPage; }}
	else if (innerWidth!=document.MM_pgW || innerHeight!=document.MM_pgH) location.reload();
}
MM_reloadPage(true);



function returnEventStatus() {
	window.status=(_returnEventStatus);
	return true;
}

function setPng24(obj) { 
    obj.width=obj.height=1; 
    obj.className=obj.className.replace(/\bpng24\b/i,''); 
    obj.style.filter = "progid:DXImageTransform.Microsoft.AlphaImageLoader(src='"+ obj.src +"',sizingMethod='image');" 
    obj.src='';  
    return ''; 
}

$(document).ready(function() {
    var _nations = "US";
    try{
        _nations = _nation;
    }catch(e){}
    try{
        var urls = document.location.href;
        var passurl = ["/Api/Apis/LoginLayer", "/Account/Integrations", "forum.nttgame.com", "kingdom.nttgame.com", "/Logins/GameLogin"];
        var z = 0;
        for(i=0; i < passurl.length; i++){
            if(urls.indexOf(passurl[i]) > 0){
                z++;
            }
        }
        var _img_integration = "/banner/EukoUser.jpg";
        if(_nations == "TR"){
            _img_integration = "/banner/EukoUser_t.jpg";
        }
        if(z == 0){
            var _banners = "<div><a href='"+ _www  +"/Account/Integrations'><img src='"+IMG_URL + _img_integration + "'></a></div>";
            $('<div id="object">').appendTo('body').html(_banners).css({
                'top': '100%',
                'left': '100%',
                'margin': '-270px 0 0 -210px',
                'z-index': '3',
                'position' : 'fixed',
                'display' : 'none'
            }).delay(2000).fadeIn('slow', function(){});
        }
    }catch(e){ }
});