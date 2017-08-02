class mx.controls.List extends mx.controls.listclasses.ScrollSelectList
{
    var border_mc, __labels, setDataProvider, __get__labels, __dataProvider, __get__rowCount, roundUp, __maxHPosition, invScrollProps, invalidate, __vPosition, getViewMetrics, __rowHeight, __width, setSize, totalWidth, totalHeight, displayWidth, __hScrollPolicy, vScroller, __hPosition, listContent, data, mask_mc, __height, __rowCount, invRowHeight, invLayoutContent, setScrollProperties, oldVWidth, __set__labels;
    function List()
    {
        super();
    } // End of the function
    function setEnabled(v)
    {
        super.setEnabled(v);
        border_mc.backgroundColorName = v ? ("backgroundColor") : ("backgroundDisabledColor");
        border_mc.invalidate();
    } // End of the function
    function get labels()
    {
        return (__labels);
    } // End of the function
    function set labels(lbls)
    {
        __labels = lbls;
        this.setDataProvider(lbls);
        //return (this.labels());
        null;
    } // End of the function
    function setVPosition(pos)
    {
        pos = Math.min(__dataProvider.length - this.__get__rowCount() + roundUp, pos);
        pos = Math.max(0, pos);
        super.setVPosition(pos);
    } // End of the function
    function setHPosition(pos)
    {
        pos = Math.max(Math.min(__maxHPosition, pos), 0);
        super.setHPosition(pos);
        this.hScroll(pos);
    } // End of the function
    function setMaxHPosition(pos)
    {
        __maxHPosition = pos;
        invScrollProps = true;
        this.invalidate();
    } // End of the function
    function setHScrollPolicy(policy)
    {
        if (policy.toLowerCase() == "auto" && !autoHScrollAble)
        {
            return;
        } // end if
        super.setHScrollPolicy(policy);
        if (policy == "off")
        {
            this.setHPosition(0);
            this.setVPosition(Math.min(__dataProvider.length - this.__get__rowCount() + roundUp, __vPosition));
        } // end if
    } // End of the function
    function setRowCount(rC)
    {
        if (isNaN(rC))
        {
            return;
        } // end if
        var _loc2 = this.getViewMetrics();
        this.setSize(__width, __rowHeight * rC + _loc2.top + _loc2.bottom);
    } // End of the function
    function layoutContent(x, y, tW, tH, dW, dH)
    {
        totalWidth = tW;
        totalHeight = tH;
        displayWidth = dW;
        var _loc4 = __hScrollPolicy == "on" || __hScrollPolicy == "auto" ? (Math.max(tW, dW)) : (dW);
        super.layoutContent(x, y, _loc4, dH);
    } // End of the function
    function modelChanged(eventObj)
    {
        super.modelChanged(eventObj);
        var _loc3 = eventObj.eventName;
        if (_loc3 == "addItems" || _loc3 == "removeItems" || _loc3 == "updateAll" || _loc3 == "filterModel")
        {
            invScrollProps = true;
            this.invalidate("invScrollProps");
        } // end if
    } // End of the function
    function onScroll(eventObj)
    {
        var _loc3 = eventObj.target;
        if (_loc3 == vScroller)
        {
            this.setVPosition(_loc3.scrollPosition);
        }
        else
        {
            this.hScroll(_loc3.scrollPosition);
        } // end else if
        super.onScroll(eventObj);
    } // End of the function
    function hScroll(pos)
    {
        __hPosition = pos;
        listContent._x = -pos;
    } // End of the function
    function init(Void)
    {
        super.init();
        if (this.__get__labels().length > 0)
        {
            var _loc6 = new Array();
            for (var _loc3 = 0; _loc3 < this.__get__labels().length; ++_loc3)
            {
                _loc6.addItem({label: this.__get__labels()[_loc3], data: data[_loc3]});
            } // end of for
            this.setDataProvider(_loc6);
        } // end if
        __maxHPosition = 0;
    } // End of the function
    function createChildren(Void)
    {
        super.createChildren();
        listContent.setMask((MovieClip)(mask_mc));
        border_mc.move(0, 0);
        border_mc.setSize(__width, __height);
    } // End of the function
    function getRowCount(Void)
    {
        var _loc2 = this.getViewMetrics();
        return (__rowCount == 0 ? (Math.ceil((__height - _loc2.top - _loc2.bottom) / __rowHeight)) : (__rowCount));
    } // End of the function
    function size(Void)
    {
        super.size();
        this.configureScrolling();
        var _loc3 = this.getViewMetrics();
        this.layoutContent(_loc3.left, _loc3.top, __width + __maxHPosition, totalHeight, __width - _loc3.left - _loc3.right, __height - _loc3.top - _loc3.bottom);
    } // End of the function
    function draw(Void)
    {
        if (invRowHeight)
        {
            invScrollProps = true;
            super.draw();
            listContent.setMask((MovieClip)(mask_mc));
            invLayoutContent = true;
        } // end if
        if (invScrollProps)
        {
            this.configureScrolling();
            delete this.invScrollProps;
        } // end if
        if (invLayoutContent)
        {
            var _loc3 = this.getViewMetrics();
            this.layoutContent(_loc3.left, _loc3.top, __width + __maxHPosition, totalHeight, __width - _loc3.left - _loc3.right, __height - _loc3.top - _loc3.bottom);
        } // end if
        super.draw();
    } // End of the function
    function configureScrolling(Void)
    {
        var _loc2 = __dataProvider.length;
        if (__vPosition > Math.max(0, _loc2 - this.getRowCount() + roundUp))
        {
            this.setVPosition(Math.max(0, Math.min(_loc2 - this.getRowCount() + roundUp, __vPosition)));
        } // end if
        var _loc3 = this.getViewMetrics();
        var _loc4 = __hScrollPolicy != "off" ? (__maxHPosition + __width - _loc3.left - _loc3.right) : (__width - _loc3.left - _loc3.right);
        if (_loc2 == undefined)
        {
            _loc2 = 0;
        } // end if
        this.setScrollProperties(_loc4, 1, _loc2, __rowHeight);
        if (oldVWidth != _loc4)
        {
            invLayoutContent = true;
        } // end if
        oldVWidth = _loc4;
    } // End of the function
    static var symbolOwner = mx.controls.List;
    static var symbolName = "List";
    var className = "List";
    static var version = "2.0.2.127";
    var clipParameters = {rowHeight: 1, enabled: 1, visible: 1, labels: 1};
    var scrollDepth = 1;
    var __vScrollPolicy = "on";
    var autoHScrollAble = false;
} // End of Class
