

$(document).ready(function() {
    
    try{ //Layer Box
        $('#popupBoxClose').click( function() { Box._close(); });
        $('#popup_container').click( function() { Box._close(); });
        $(window).resize(function() {  
            try{
                if(document.getElementById("popup_box").style.display != "none"){
                    Box._resize();
                }
            }catch(e){}
            try{
                if(document.getElementById("dPolicy").style.display != "none"){
                    $("#dPolicy").wcenter("fixed");
                }
            }catch(e){}
            } );
    }catch(e){}
    
});


