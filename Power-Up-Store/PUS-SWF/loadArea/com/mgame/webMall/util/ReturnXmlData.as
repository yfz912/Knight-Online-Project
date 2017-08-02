class com.mgame.webMall.util.ReturnXmlData
{
    function ReturnXmlData()
    {
    } // End of the function
    function setArrayData(arrData, index, pageType, subIndex)
    {
        this.index = index;
        if (pageType == undefined)
        {
            pageType = "main";
        } // end if
        if (pageType == "packageShop")
        {
            var _loc4 = arrData[index];
            thisXml = new XML(String(_loc4[subIndex]));
            thisArr = thisXml.firstChild.childNodes;
        }
        else
        {
            thisXml = new XML(String(arrData[index]));
            thisArr = thisXml.firstChild.childNodes;
        } // end else if
        if (pageType == "main")
        {
            return (this.makeMainObj());
        }
        else if (pageType == "myBasket")
        {
            return (this.makeMybasketObj());
        }
        else if (pageType == "eventShop")
        {
            return (this.makeEventShop());
        }
        else if (pageType == "packageShop")
        {
            return (this.makePackageObj());
        }
        else if (pageType == "coupon")
        {
            return (this.makeCouponObj());
        }
        else if (pageType == "myShop")
        {
            return (this.makeMyShopObj());
        }
        else if (pageType == "mySettle")
        {
            return (this.makeMySettleObj());
        }
        else if (pageType == "gift")
        {
            return (this.makeGiftObj());
        }
        else if (pageType == "jorgi")
        {
            return (this.makeJorgiObj());
        }
        else if (pageType == "myShop_cashInven")
        {
            return (this.makeCashInvenObj());
        }
        else if (pageType == "cashInvenOutList")
        {
            return (this.makeCashInvenOutListObj());
        }
        else
        {
            return (this.makeSearchObj(pageType));
        } // end else if
    } // End of the function
    function makeMainObj()
    {
        thisObj = new Object();
        thisObj.view_type = thisArr[0].firstChild.nodeValue;
        thisObj.view_rank = thisArr[1].firstChild.nodeValue;
        thisObj.goodsno = thisArr[2].firstChild.nodeValue;
        thisObj.name = thisArr[3].firstChild.nodeValue;
        thisObj.smallimage = thisArr[4].firstChild.nodeValue;
        thisObj.bigimage = thisArr[5].firstChild.nodeValue;
        thisObj.mainicon = thisArr[6].firstChild.nodeValue;
        thisObj.subicon = thisArr[7].firstChild.nodeValue;
        thisObj.price = thisArr[8].firstChild.nodeValue;
        thisObj.dc = thisArr[9].firstChild.nodeValue;
        thisObj.event_price = thisArr[10].firstChild.nodeValue;
        thisObj.dtype = thisArr[11].firstChild.nodeValue;
        thisObj.buytype = thisArr[12].firstChild.nodeValue;
        thisObj.invencnt = thisArr[13].firstChild.nodeValue;
        thisObj.explain1 = thisArr[14].firstChild.nodeValue;
        thisObj.explain2 = thisArr[15].firstChild.nodeValue;
        thisObj.item_type = thisArr[16].firstChild.nodeValue;
        thisObj.limit_type = thisArr[17].firstChild.nodeValue;
        thisObj.limit_total = thisArr[18].firstChild.nodeValue;
        thisObj.limit_remain = thisArr[19].firstChild.nodeValue;
        thisObj.limit_sdate = thisArr[20].firstChild.nodeValue;
        thisObj.limit_edate = thisArr[21].firstChild.nodeValue;
        thisObj.limit_age = thisArr[22].firstChild.nodeValue;
        thisObj.issue_check = thisArr[23].firstChild.nodeValue;
        thisObj.issue_image = thisArr[24].firstChild.nodeValue;
        thisObj.char_sex = thisArr[25].firstChild.nodeValue;
        thisObj.item_property = thisArr[26].firstChild.nodeValue;
        thisObj.repeal = thisArr[27].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "main";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makeMybasketObj()
    {
        thisObj = new Object();
        thisObj.struserid = thisArr[0].firstChild.nodeValue;
        thisObj.item_type = thisArr[1].firstChild.nodeValue;
        thisObj.item_code = thisArr[2].firstChild.nodeValue;
        thisObj.item_name = thisArr[3].firstChild.nodeValue;
        thisObj.item_image = thisArr[4].firstChild.nodeValue;
        thisObj.item_price = thisArr[5].firstChild.nodeValue;
        thisObj.item_count = thisArr[6].firstChild.nodeValue;
        thisObj.total_price = thisArr[7].firstChild.nodeValue;
        thisObj.option_code = thisArr[8].firstChild.nodeValue;
        thisObj.package_code = thisArr[9].firstChild.nodeValue;
        thisObj.indate = thisArr[10].firstChild.nodeValue;
        thisObj.limit_age = thisArr[11].firstChild.nodeValue;
        thisObj.explain1 = thisArr[13].firstChild.nodeValue;
        thisObj.explain2 = thisArr[14].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "myBasket";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makeEventShop()
    {
        thisObj = new Object();
        thisObj.goodsno = thisArr[0].firstChild.nodeValue;
        thisObj.name = thisArr[1].firstChild.nodeValue;
        thisObj.smallimage = thisArr[2].firstChild.nodeValue;
        thisObj.bigimage = thisArr[3].firstChild.nodeValue;
        thisObj.mainicon = thisArr[4].firstChild.nodeValue;
        thisObj.subicon = thisArr[5].firstChild.nodeValue;
        thisObj.price = thisArr[6].firstChild.nodeValue;
        thisObj.dc = thisArr[7].firstChild.nodeValue;
        thisObj.event_price = thisArr[8].firstChild.nodeValue;
        thisObj.dtype = thisArr[9].firstChild.nodeValue;
        thisObj.buytype = thisArr[10].firstChild.nodeValue;
        thisObj.rank = thisArr[11].firstChild.nodeValue;
        thisObj.invencnt = thisArr[12].firstChild.nodeValue;
        thisObj.explain1 = thisArr[13].firstChild.nodeValue;
        thisObj.explain2 = thisArr[14].firstChild.nodeValue;
        thisObj.item_type = thisArr[15].firstChild.nodeValue;
        thisObj.limit_type = thisArr[16].firstChild.nodeValue;
        thisObj.limit_total = thisArr[17].firstChild.nodeValue;
        thisObj.limit_remain = thisArr[18].firstChild.nodeValue;
        thisObj.limit_sdate = thisArr[19].firstChild.nodeValue;
        thisObj.limit_edate = thisArr[20].firstChild.nodeValue;
        thisObj.limit_age = thisArr[21].firstChild.nodeValue;
        thisObj.char_sex = thisArr[22].firstChild.nodeValue;
        thisObj.item_property = thisArr[23].firstChild.nodeValue;
        thisObj.repeal = thisArr[24].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "eventShop";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makePackageObj()
    {
        thisObj = new Object();
        thisObj.packagename = thisArr[0].firstChild.nodeValue;
        thisObj.goodsno = thisArr[1].firstChild.nodeValue;
        thisObj.name = thisArr[2].firstChild.nodeValue;
        thisObj.smallimage = thisArr[3].firstChild.nodeValue;
        thisObj.bigimage = thisArr[4].firstChild.nodeValue;
        thisObj.mainicon = thisArr[5].firstChild.nodeValue;
        thisObj.subicon = thisArr[6].firstChild.nodeValue;
        thisObj.price = thisArr[7].firstChild.nodeValue;
        thisObj.dc = thisArr[8].firstChild.nodeValue;
        thisObj.event_price = thisArr[9].firstChild.nodeValue;
        thisObj.dtype = thisArr[10].firstChild.nodeValue;
        thisObj.buytype = thisArr[11].firstChild.nodeValue;
        thisObj.rank = thisArr[12].firstChild.nodeValue;
        thisObj.invencnt = thisArr[13].firstChild.nodeValue;
        thisObj.explain1 = thisArr[14].firstChild.nodeValue;
        thisObj.explain2 = thisArr[15].firstChild.nodeValue;
        thisObj.item_type = thisArr[16].firstChild.nodeValue;
        thisObj.limit_type = thisArr[17].firstChild.nodeValue;
        thisObj.limit_total = thisArr[18].firstChild.nodeValue;
        thisObj.limit_remain = thisArr[19].firstChild.nodeValue;
        thisObj.limit_sdate = thisArr[20].firstChild.nodeValue;
        thisObj.limit_edate = thisArr[21].firstChild.nodeValue;
        thisObj.limit_age = thisArr[22].firstChild.nodeValue;
        thisObj.char_sex = thisArr[23].firstChild.nodeValue;
        thisObj.item_property = thisArr[24].firstChild.nodeValue;
        thisObj.repeal = thisArr[25].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "packageShop";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makeCouponObj()
    {
        thisObj = new Object();
        thisObj.cause = thisArr[0].firstChild.nodeValue;
        thisObj.serial_no = thisArr[1].firstChild.nodeValue;
        thisObj.ticket_type = thisArr[2].firstChild.nodeValue;
        thisObj.sale_price = thisArr[3].firstChild.nodeValue;
        thisObj.use_type = thisArr[4].firstChild.nodeValue;
        thisObj.price_control = thisArr[5].firstChild.nodeValue;
        thisObj.property_control = thisArr[6].firstChild.nodeValue;
        thisObj.cert_date = thisArr[7].firstChild.nodeValue;
        thisObj.expire_date = thisArr[8].firstChild.nodeValue;
        thisObj.make_date = thisArr[9].firstChild.nodeValue;
        thisObj.limit_date = thisArr[10].firstChild.nodeValue;
        thisObj.active_type = thisArr[11].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "availTicket";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makeMyShopObj()
    {
        thisObj = new Object();
        thisObj.name = thisArr[0].firstChild.nodeValue;
        thisObj.item_cnt = thisArr[1].firstChild.nodeValue;
        thisObj.buycash = thisArr[2].firstChild.nodeValue;
        thisObj.buydate = thisArr[3].firstChild.nodeValue;
        thisObj.cashtype = thisArr[4].firstChild.nodeValue;
        thisObj.dtype = thisArr[5].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "myShop";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makeCashInvenObj()
    {
        thisObj = new Object();
        thisObj.num = thisArr[0].firstChild.nodeValue;
        thisObj.name = thisArr[1].firstChild.nodeValue;
        thisObj.itemCode = thisArr[2].firstChild.nodeValue;
        thisObj.itemCount = thisArr[3].firstChild.nodeValue;
        thisObj.dc = thisArr[4].firstChild.nodeValue;
        thisObj.positive = thisArr[5].firstChild.nodeValue;
        thisObj.indate = thisArr[6].firstChild.nodeValue;
        return (thisObj);
    } // End of the function
    function makeCashInvenOutListObj()
    {
        thisObj = new Object();
        thisObj.item_name = thisArr[0].firstChild.nodeValue;
        thisObj.item_cnt = thisArr[1].firstChild.nodeValue;
        thisObj.item_price = thisArr[2].firstChild.nodeValue;
        thisObj.price_back = thisArr[3].firstChild.nodeValue;
        thisObj.indate = thisArr[4].firstChild.nodeValue;
        thisObj.reg_date = thisArr[5].firstChild.nodeValue;
        thisObj.positive = thisArr[6].firstChild.nodeValue;
        return (thisObj);
    } // End of the function
    function makeSearchObj(cmd)
    {
        thisObj = new Object();
        thisObj.goodsno = thisArr[0].firstChild.nodeValue;
        thisObj.name = thisArr[1].firstChild.nodeValue;
        thisObj.smallimage = thisArr[2].firstChild.nodeValue;
        thisObj.bigimage = thisArr[3].firstChild.nodeValue;
        thisObj.mainicon = thisArr[4].firstChild.nodeValue;
        thisObj.subicon = thisArr[5].firstChild.nodeValue;
        thisObj.price = thisArr[6].firstChild.nodeValue;
        thisObj.dc = thisArr[7].firstChild.nodeValue;
        thisObj.event_price = thisArr[8].firstChild.nodeValue;
        thisObj.dtype = thisArr[9].firstChild.nodeValue;
        thisObj.buytype = thisArr[10].firstChild.nodeValue;
        thisObj.rank = thisArr[11].firstChild.nodeValue;
        thisObj.invencnt = thisArr[12].firstChild.nodeValue;
        thisObj.explain1 = thisArr[13].firstChild.nodeValue;
        thisObj.explain2 = thisArr[14].firstChild.nodeValue;
        thisObj.item_type = thisArr[15].firstChild.nodeValue;
        thisObj.limit_type = thisArr[16].firstChild.nodeValue;
        thisObj.limit_total = thisArr[17].firstChild.nodeValue;
        thisObj.limit_remain = thisArr[18].firstChild.nodeValue;
        thisObj.limit_sdate = thisArr[19].firstChild.nodeValue;
        thisObj.limit_edate = thisArr[20].firstChild.nodeValue;
        thisObj.limit_age = thisArr[21].firstChild.nodeValue;
        thisObj.char_sex = thisArr[22].firstChild.nodeValue;
        thisObj.item_property = thisArr[23].firstChild.nodeValue;
        thisObj.repeal = thisArr[24].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = cmd;
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makeMySettleObj()
    {
        thisObj = new Object();
        thisObj.num = thisArr[0].firstChild.nodeValue;
        thisObj.goodsno = thisArr[1].firstChild.nodeValue;
        thisObj.name = thisArr[2].firstChild.nodeValue;
        thisObj.i_price = thisArr[3].firstChild.nodeValue;
        thisObj.dt_regdate = thisArr[4].firstChild.nodeValue;
        thisObj.lastdate = thisArr[5].firstChild.nodeValue;
        thisObj.i_state = thisArr[6].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "mySettle";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makeGiftObj()
    {
        thisObj = new Object();
        thisObj.num = thisArr[0].firstChild.nodeValue;
        thisObj.goodsno = thisArr[1].firstChild.nodeValue;
        thisObj.name = thisArr[2].firstChild.nodeValue;
        thisObj.price = thisArr[3].firstChild.nodeValue;
        thisObj.bigimage = thisArr[4].firstChild.nodeValue;
        thisObj.message = thisArr[5].firstChild.nodeValue;
        thisObj.userchar = thisArr[6].firstChild.nodeValue;
        thisObj.targetchar = thisArr[7].firstChild.nodeValue;
        thisObj.indate = thisArr[8].firstChild.nodeValue;
        thisObj.dtype = thisArr[9].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "myGift";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function makeJorgiObj()
    {
        thisObj = new Object();
        thisObj.num = thisArr[0].firstChild.nodeValue;
        thisObj.goodsno = thisArr[1].firstChild.nodeValue;
        thisObj.name = thisArr[2].firstChild.nodeValue;
        thisObj.price = thisArr[3].firstChild.nodeValue;
        thisObj.bigimage = thisArr[4].firstChild.nodeValue;
        thisObj.message = thisArr[5].firstChild.nodeValue;
        thisObj.userchar = thisArr[6].firstChild.nodeValue;
        thisObj.targetchar = thisArr[7].firstChild.nodeValue;
        thisObj.indate = thisArr[8].firstChild.nodeValue;
        thisObj.dtype = thisArr[9].firstChild.nodeValue;
        thisObj = this.trim(thisObj);
        thisObj.param = "";
        thisObj.cmd = "myJorgi";
        thisObj.strSubmit = this.ascSplit(thisObj);
        return (thisObj);
    } // End of the function
    function trim(obj)
    {
        for (var _loc2 in obj)
        {
            if (obj[_loc2] == undefined)
            {
                obj[_loc2] = "";
            } // end if
        } // end of for...in
        return (obj);
    } // End of the function
    function ascSplit(dataObj)
    {
        return (dataObj.goodsno);
    } // End of the function
    var thisXml = null;
    var thisArr = null;
    var thisObj = null;
    var index = 0;
} // End of Class
