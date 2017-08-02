class com.mgame.webMall.main.TicketListXml
{
    function TicketListXml()
    {
    } // End of the function
    function load()
    {
        var _this = this;
        var _loc2 = new XML();
        _loc2.ignoreWhite = true;
        _loc2.onLoad = function ()
        {
            _this.onLoad(this);
        };
        var _loc3 = new LoadVars();
        _loc3.cmd = "ticketList";
        _loc3.param = com.mgame.webMall.main.MainData.LOGIN_auckey;
        _loc3.sendAndLoad(com.mgame.webMall.main.CommonDataUrl.__get__ticketListURL(), _loc2, "post");
    } // End of the function
    function onLoad(xmlData)
    {
        var _loc2 = new Array();
        var _loc4 = xmlData.firstChild.firstChild.nextSibling.childNodes;
        this.deleteArrayData();
        for (var _loc3 = 0; _loc3 < _loc4.length; ++_loc3)
        {
            _loc2 = _loc4[_loc3].childNodes;
            com.mgame.webMall.main.MainData.__get__TICKET_cause().push(_loc2[0].firstChild.nodeValue);
            com.mgame.webMall.main.MainData.__get__TICKET_ticket_type().push(_loc2[1].firstChild.nodeValue);
            com.mgame.webMall.main.MainData.__get__TICKET_sale_price().push(_loc2[2].firstChild.nodeValue);
            com.mgame.webMall.main.MainData.__get__TICKET_price_control().push(_loc2[3].firstChild.nodeValue);
            com.mgame.webMall.main.MainData.__get__TICKET_property_control().push(_loc2[4].firstChild.nodeValue);
            com.mgame.webMall.main.MainData.__get__TICKET_serial_no().push(_loc2[5].firstChild.nodeValue);
        } // end of for
    } // End of the function
    function deleteArrayData()
    {
        com.mgame.webMall.main.MainData.__set__TICKET_cause([]);
        com.mgame.webMall.main.MainData.__set__TICKET_ticket_type([]);
        com.mgame.webMall.main.MainData.__set__TICKET_sale_price([]);
        com.mgame.webMall.main.MainData.__set__TICKET_price_control([]);
        com.mgame.webMall.main.MainData.__set__TICKET_property_control([]);
        com.mgame.webMall.main.MainData.__set__TICKET_serial_no([]);
    } // End of the function
} // End of Class
