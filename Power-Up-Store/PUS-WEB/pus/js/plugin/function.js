/*
 * center
 */
try{
    jQuery.fn.center = function () {
        this.css("position","fixed");
        this.css("top", Math.max(0, (($(window).height() - $(this).outerHeight()) / 2) + $(window).scrollTop()) + "px");
        this.css("left", (Math.max(0, (($(window).width() - $(this).outerWidth()) / 2) + $(window).scrollLeft()) ) + "px");
        return this;
    }

    jQuery.fn.tcenter = function (_top) {
        this.css("position","fixed");
        this.css("top", _top + "px");
        this.css("left", (Math.max(0, (($(window).width() - $(this).outerWidth()) / 2) + $(window).scrollLeft()) ) + "px");
        return this;
    }
    
    jQuery.fn.wcenter = function (type) {
        try{
            if(type == "fixed"){
                this.css("position","fixed");
            }else{
                this.css("position","absolute");
            }
        }catch(e){
            this.css("position","absolute");
        }
        this.css("left", (Math.max(0, (($(window).width() - $(this).outerWidth()) / 2) + $(window).scrollLeft()) ) + "px");
        return this;
    }
}catch(e){}