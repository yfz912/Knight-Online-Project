class com.mgame.webMall.util.ScrollBar
{
    var _parent, _y, _height;
    function ScrollBar()
    {
    } // End of the function
    function setScrollTarget(target)
    {
        scrollTarget = target;
    } // End of the function
    function setScrollUpButton(target)
    {
        scrollUpButton = target;
    } // End of the function
    function setScrollDownButton(target)
    {
        scrollDownButton = target;
    } // End of the function
    function setScrollBar(target)
    {
        scrollBar = target;
    } // End of the function
    function setMouseWheelEvent(target)
    {
        this.setScrollTarget(target);
        this.mouseWheelEvent();
    } // End of the function
    function setMouseWheelStyle(value)
    {
        mouseWheelStyleValue = value;
    } // End of the function
    function scrollLineLoad()
    {
        if (scrollBar._parent.scrollLine != undefined)
        {
            scrollBar._parent.scrollLine.removeMovieClip();
        } // end if
        scrollBar._parent.attachMovie("scrollLine", "scrollLine", scrollBar._parent.getNextHighestDepth());
        scrollBar._parent.scrollLine._x = 4;
        scrollBar._parent.scrollLine._y = Math.floor(scrollBar._y + scrollBar._height / 2);
    } // End of the function
    function start(scrollAreaSize, scrollTargetOriginY, scrollbarY, scrollbarHeight)
    {
        this.scrollAreaSize = scrollAreaSize;
        scrollbarOriginY = scrollbarY;
        this.scrollTargetOriginY = scrollTargetOriginY;
        scrollTarget._y = this.scrollTargetOriginY;
        scrollBar._y = scrollbarOriginY;
        var _loc2 = 1 - this.scrollAreaSize / scrollTarget._height;
        if (_loc2 < 0)
        {
            _loc2 = 0;
        } // end if
        if (_loc2 == 0)
        {
            scrollBar.enabled = false;
            mouseWheelStyleValue = false;
        }
        else
        {
            scrollBar.enabled = true;
            mouseWheelStyleValue = true;
        } // end else if
        if (mouseWheelStyleValue)
        {
            this.mouseWheelEvent();
        } // end if
        originBarSize = scrollbarHeight;
        changeBarSize = originBarSize - originBarSize * _loc2;
        scrollBar._height = changeBarSize;
        this.scrollLineLoad();
        this.buttonEvent();
    } // End of the function
    function buttonEvent()
    {
        var _this = this;
        scrollBar.onPress = function ()
        {
            _this.scrollbarStartDrag();
        };
        scrollBar.onRelease = function ()
        {
            _this.deleteMoveEnterFrame();
        };
        scrollBar.onReleaseOutside = function ()
        {
            _this.deleteMoveEnterFrame();
        };
        scrollUpButton.onPress = function ()
        {
            _this.scrollUpEvent();
        };
        scrollUpButton.onRelease = scrollUpButton.onReleaseOutside = function ()
        {
            _this.deleteScrollUpEvent();
        };
        scrollDownButton.onPress = function ()
        {
            _this.scrollDownEvent();
        };
        scrollDownButton.onRelease = scrollDownButton.onReleaseOutside = function ()
        {
            _this.deleteScrollDownEvent();
        };
    } // End of the function
    function scrollbarStartDrag()
    {
        dragTop = scrollbarOriginY - (scrollbarOriginY - (scrollUpButton._height + scrollUpButton._y)) + 1;
        dragBottom = originBarSize - changeBarSize + (scrollUpButton._height + scrollUpButton._y) - 1;
        scrollBar.startDrag(false, 0, dragTop, 0, dragBottom);
        this.moveEnterFrame();
    } // End of the function
    function moveEnterFrame()
    {
        var _this = this;
        scrollBar.onEnterFrame = function ()
        {
            var _loc2 = (_this.scrollBar._y - _this.scrollbarOriginY) / (Math.floor(_this.dragBottom) - _this.scrollbarOriginY);
            var _loc3 = (_this.scrollTarget._height - _this.scrollAreaSize) * _loc2;
            _this.scrollTarget._y = _this.scrollTargetOriginY - _loc3;
            _parent.scrollLine._y = Math.floor(_y + _height / 2);
        };
    } // End of the function
    function deleteMoveEnterFrame()
    {
        scrollBar.stopDrag();
        delete scrollBar.onEnterFrame;
    } // End of the function
    function scrollUpEvent()
    {
        var _this = this;
        scrollUpButton.onEnterFrame = function ()
        {
            _this.pressUpMove();
        };
    } // End of the function
    function scrollDownEvent()
    {
        var _this = this;
        scrollDownButton.onEnterFrame = function ()
        {
            _this.pressDownMove();
        };
    } // End of the function
    function deleteScrollUpEvent()
    {
        delete scrollUpButton.onEnterFrame;
    } // End of the function
    function deleteScrollDownEvent()
    {
        delete scrollDownButton.onEnterFrame;
    } // End of the function
    function mouseWheelEvent(type)
    {
        var _this = this;
        Mouse.addListener(mouseListener);
        mouseListener.onMouseWheel = function (delta)
        {
            if (com.mgame.webMall.main.MainData.__get__wheelValue() && _this.mouseWheelStyleValue)
            {
                if (delta > 0)
                {
                    _this.pressUpMove();
                }
                else
                {
                    _this.pressDownMove();
                } // end if
            } // end else if
        };
    } // End of the function
    function pressUpMove()
    {
        if (scrollBar._y > scrollbarOriginY)
        {
            scrollBar._y = scrollBar._y - 12;
            var _loc2 = (scrollBar._y - scrollbarOriginY) / (Math.round(dragBottom) - scrollbarOriginY);
            var _loc3 = (scrollTarget._height - scrollAreaSize) * _loc2;
            scrollTarget._y = scrollTargetOriginY - _loc3;
            if (scrollTarget._y > scrollTargetOriginY)
            {
                scrollTarget._y = scrollTargetOriginY;
            } // end if
        }
        else
        {
            scrollBar._y = scrollbarOriginY;
            this.deleteScrollUpEvent();
        } // end else if
        scrollBar._parent.scrollLine._y = Math.floor(scrollBar._y + scrollBar._height / 2);
    } // End of the function
    function pressDownMove()
    {
        if (originBarSize != changeBarSize)
        {
            dragBottom = originBarSize - changeBarSize + (scrollUpButton._height + scrollUpButton._y);
            if (scrollBar._y < Math.round(dragBottom))
            {
                scrollBar._y = scrollBar._y + 12;
                var _loc2 = (scrollBar._y - scrollbarOriginY) / (Math.round(dragBottom) - scrollbarOriginY);
                var _loc3 = (scrollTarget._height - scrollAreaSize) * _loc2;
                scrollTarget._y = scrollTargetOriginY - _loc3;
            }
            else
            {
                scrollBar._y = Math.round(dragBottom);
                this.deleteScrollDownEvent();
            } // end if
        } // end else if
        scrollBar._parent.scrollLine._y = Math.floor(scrollBar._y + scrollBar._height / 2);
    } // End of the function
    function deleteWheelScroll()
    {
        Mouse.removeListener(mouseListener);
    } // End of the function
    var scrollTarget = null;
    var scrollBar = null;
    var scrollUpButton = null;
    var scrollDownButton = null;
    var enterFrameMovieClip = null;
    var mouseWheelStyleValue = true;
    var scrollAreaSize = 0;
    var scrollTargetOriginY = 0;
    var scrollbarOriginY = 0;
    var originBarSize = 0;
    var changeBarSize = 0;
    var dragTop = 0;
    var dragBottom = 0;
    var mouseListener = new Object();
} // End of Class
