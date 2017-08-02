class mx.controls.TextArea extends mx.core.ScrollView
{
    var label, __get__maxChars, __get__restrict, invalidate, __get__wordWrap, __get__editable, __get__password, __get__html, __get__text, initText, dispatchValueChangedEvent, getHPosition, setHPosition, __get__hPosition, getVPosition, setVPosition, __get__vPosition, _color, focusTextField, _parent, owner, hscroll, scroll, __set__text, tfx, tfy, tfw, tfh, doLater, _vpos, _hpos, hookedV, vScroller, hookedH, hScroller, getViewMetrics, __get__width, __get__height, hScrollPolicy, vScrollPolicy, getStyle, getFocusManager, addEventListener, removeEventListener, _getTextFormat, __get__tabIndex, __get___accProps, __get__styleSheet, __set___accProps, __set__editable, __set__hPosition, __set__html, __get__length, __set__maxChars, __get__maxHPosition, __get__maxVPosition, __set__password, __set__restrict, __set__styleSheet, __set__tabIndex, __set__vPosition, __set__wordWrap;
    function TextArea()
    {
        super();
    } // End of the function
    function get maxChars()
    {
        return (label.maxChars);
    } // End of the function
    function set maxChars(x)
    {
        label.maxChars = x;
        //return (this.maxChars());
        null;
    } // End of the function
    function get length()
    {
        return (label.length);
    } // End of the function
    function get restrict()
    {
        return (label.restrict);
    } // End of the function
    function set restrict(s)
    {
        label.restrict = s == "" ? (null) : (s);
        //return (this.restrict());
        null;
    } // End of the function
    function get wordWrap()
    {
        return (label.wordWrap);
    } // End of the function
    function set wordWrap(s)
    {
        label.wordWrap = s;
        this.invalidate();
        //return (this.wordWrap());
        null;
    } // End of the function
    function get editable()
    {
        return (__editable);
    } // End of the function
    function set editable(x)
    {
        __editable = x;
        label.type = x ? ("input") : ("dynamic");
        //return (this.editable());
        null;
    } // End of the function
    function get password()
    {
        return (label.password);
    } // End of the function
    function set password(s)
    {
        label.password = s;
        //return (this.password());
        null;
    } // End of the function
    function get html()
    {
        return (this.getHtml());
    } // End of the function
    function set html(value)
    {
        this.setHtml(value);
        //return (this.html());
        null;
    } // End of the function
    function getHtml()
    {
        return (label.html);
    } // End of the function
    function setHtml(value)
    {
        if (value != label.html)
        {
            label.html = value;
        } // end if
    } // End of the function
    function get text()
    {
        return (this.getText());
    } // End of the function
    function set text(t)
    {
        this.setText(t);
        //return (this.text());
        null;
    } // End of the function
    function getText()
    {
        if (initializing)
        {
            return (initText);
        } // end if
        var _loc2 = label;
        if (_loc2.html == true)
        {
            return (_loc2.htmlText);
        } // end if
        return (_loc2.text);
    } // End of the function
    function setText(t)
    {
        if (initializing)
        {
            initText = t;
        }
        else
        {
            var _loc2 = label;
            if (_loc2.html == true)
            {
                _loc2.htmlText = t;
            }
            else
            {
                _loc2.text = t;
            } // end else if
            this.invalidate();
        } // end else if
        this.dispatchValueChangedEvent(t);
    } // End of the function
    function get hPosition()
    {
        return (this.getHPosition());
    } // End of the function
    function set hPosition(pos)
    {
        this.setHPosition(pos);
        label.hscroll = pos;
        label.background = false;
        //return (this.hPosition());
        null;
    } // End of the function
    function get vPosition()
    {
        return (this.getVPosition());
    } // End of the function
    function set vPosition(pos)
    {
        this.setVPosition(pos);
        label.scroll = pos + 1;
        label.background = false;
        //return (this.vPosition());
        null;
    } // End of the function
    function get maxVPosition()
    {
        var _loc2 = label.maxscroll - 1;
        return (_loc2 == undefined ? (0) : (_loc2));
    } // End of the function
    function get maxHPosition()
    {
        var _loc2 = label.maxhscroll;
        return (_loc2 == undefined ? (0) : (_loc2));
    } // End of the function
    function init(Void)
    {
        super.init();
        label.styleName = this;
        _color = mx.core.UIObject.textColorList;
        focusTextField = label;
        label.owner = this;
        label.onSetFocus = function (x)
        {
            _parent.onSetFocus(x);
        };
        label.onKillFocus = function (x)
        {
            _parent.onKillFocus(x);
        };
        label.drawFocus = function (b)
        {
            _parent.drawFocus(b);
        };
        label.onChanged = function ()
        {
            owner.adjustScrollBars();
            owner.dispatchEvent({type: "change"});
            owner.dispatchValueChangedEvent(owner.text);
        };
        label.onScroller = function ()
        {
            owner.hPosition = hscroll;
            owner.vPosition = scroll - 1;
        };
        if (this.__get__text() == undefined)
        {
            this.__set__text("");
        } // end if
    } // End of the function
    function createChildren(Void)
    {
        super.createChildren();
        label.autoSize = "none";
    } // End of the function
    function layoutContent(x, y, totalW, totalH, displayW, displayH)
    {
        var _loc2 = label;
        if (tfx != x || tfy != y || tfw != displayW || tfh != displayH)
        {
            tfx = x;
            tfy = y;
            tfw = displayW;
            tfh = displayH;
            _loc2.move(tfx, tfy);
            _loc2.setSize(tfw, tfh);
            this.doLater(this, "adjustScrollBars");
        } // end if
    } // End of the function
    function scrollChanged(Void)
    {
        var _loc2 = Selection;
        if (_loc2.lastBeginIndex != undefined)
        {
            this.restoreSelection();
        } // end if
        label.background = false;
    } // End of the function
    function onScroll(docObj)
    {
        var _loc3 = label;
        super.onScroll(docObj);
        _loc3.hscroll = this.__get__hPosition() + 0;
        _loc3.scroll = this.__get__vPosition() + 1;
        _vpos = _loc3.scroll;
        _hpos = _loc3.hscroll;
        _loc3.background = false;
        if (hookedV != true)
        {
            vScroller.addEventListener("scrollChanged", this);
            hookedV = true;
        } // end if
        if (hookedH != true)
        {
            hScroller.addEventListener("scrollChanged", this);
            hookedH = true;
        } // end if
    } // End of the function
    function size(Void)
    {
        var _loc3 = this.getViewMetrics();
        var _loc7 = _loc3.left + _loc3.right;
        var _loc4 = _loc3.top + _loc3.bottom;
        var _loc6 = _loc3.left;
        var _loc5 = _loc3.top;
        tfx = _loc6;
        tfy = _loc5;
        tfw = this.__get__width() - _loc7;
        tfh = this.__get__height() - _loc4;
        super.size();
        label.move(tfx, tfy);
        label.setSize(tfw, tfh);
        if (this.__get__height() <= 40)
        {
            hScrollPolicy = "off";
            vScrollPolicy = "off";
        } // end if
        this.doLater(this, "adjustScrollBars");
    } // End of the function
    function setEnabled(enable)
    {
        vScroller.enabled = enable;
        hScroller.enabled = enable;
        label.type = this.__get__editable() == false || enable == false ? ("dynamic") : ("input");
        label.selectable = enable;
        var _loc3 = this.getStyle(enable ? ("color") : ("disabledColor"));
        if (_loc3 == undefined)
        {
            _loc3 = enable ? (0) : (8947848);
        } // end if
        this.setColor(_loc3);
    } // End of the function
    function setColor(col)
    {
        label.textColor = col;
    } // End of the function
    function setFocus(Void)
    {
        Selection.setFocus(label);
    } // End of the function
    function onSetFocus(x)
    {
        var f = Selection.getFocus();
        var o = eval(f);
        if (o != this.label)
        {
            Selection.setFocus(this.label);
            return;
        } // end if
        this.getFocusManager().defaultPushButtonEnabled = false;
        this.addEventListener("keyDown", this);
        super.onSetFocus(x);
    } // End of the function
    function onKillFocus(x)
    {
        this.getFocusManager().defaultPushButtonEnabled = true;
        this.removeEventListener("keyDown", this);
        super.onKillFocus(x);
    } // End of the function
    function restoreSelection(x)
    {
        var _loc2 = Selection;
        Selection.setSelection(_loc2.lastBeginIndex, _loc2.lastEndIndex);
        label.scroll = _vpos;
        label.hscroll = _hpos;
    } // End of the function
    function getLineOffsets(Void)
    {
        var _loc16 = this._getTextFormat();
        var _loc18 = _loc16.getTextExtent2(label.text);
        var _loc5 = _root._getTextExtent;
        _loc5.setNewTextFormat(_loc16);
        var _loc14 = label.wordWrap;
        var _loc9 = 0;
        var _loc7 = label._width - 2 - 2;
        var _loc12 = new Array();
        var _loc17 = new String(label.text);
        var _loc15 = _loc17.split("\r");
        for (var _loc11 = 0; _loc11 < _loc15.length; ++_loc11)
        {
            _loc12.push(_loc9);
            var _loc4 = _loc15[_loc11];
            _loc5.text = _loc4;
            var _loc13 = Math.ceil(_loc5.textWidth / _loc7);
            var _loc10 = Math.floor(_loc4.length / _loc13);
            var _loc3;
            while (_loc14 && _loc5.textWidth > _loc7)
            {
                _loc3 = _loc4.indexOf(" ", _loc10);
                var _loc6;
                if (_loc3 == -1)
                {
                    _loc3 = _loc4.lastIndexOf(" ");
                    if (_loc3 == -1)
                    {
                        _loc3 = _loc10;
                    } // end if
                } // end if
                _loc6 = _loc4.substr(0, _loc3);
                _loc5.text = _loc6;
                if (_loc5.textWidth > _loc7)
                {
                    while (_loc5.textWidth > _loc7)
                    {
                        var _loc8 = _loc3;
                        _loc3 = _loc4.lastIndexOf(" ", _loc3 - 1);
                        if (_loc3 == -1)
                        {
                            _loc3 = _loc8 - 1;
                        } // end if
                        _loc6 = _loc4.substr(0, _loc3);
                        _loc5.text = _loc6;
                    } // end while
                }
                else if (_loc5.textWidth < _loc7)
                {
                    _loc8 = _loc3;
                    while (_loc5.textWidth < _loc7)
                    {
                        _loc8 = _loc3;
                        _loc3 = _loc4.indexOf(" ", _loc3 + 1);
                        if (_loc3 == -1)
                        {
                            if (_loc4.indexOf(" ", 0) != -1)
                            {
                                break;
                            }
                            else
                            {
                                _loc3 = _loc8 + 1;
                            } // end if
                        } // end else if
                        _loc6 = _loc4.substr(0, _loc3);
                        _loc5.text = _loc6;
                    } // end while
                    _loc3 = _loc8;
                } // end else if
                _loc9 = _loc9 + _loc3;
                _loc12.push(_loc9 + 1);
                _loc4 = _loc4.substr(_loc3);
                if (_loc4.charAt(0) == " ")
                {
                    _loc4 = _loc4.substr(1, _loc4.length - 1);
                    _loc9 = _loc9 + 1;
                } // end if
                _loc5.text = _loc4;
            } // end while
            _loc9 = _loc9 + (_loc4.length + 1);
        } // end of for
        return (_loc12);
    } // End of the function
    function keyDown(e)
    {
        var _loc5 = e.code;
        if (_loc5 == 34)
        {
            var _loc6 = label.bottomScroll - label.scroll + 1;
            var _loc3 = this.getLineOffsets();
            var _loc2 = Math.min(label.bottomScroll + 1, label.maxscroll);
            if (_loc2 == label.maxscroll)
            {
                var _loc4 = label.length;
                Selection.setSelection(_loc4, _loc4);
            }
            else
            {
                label.scroll = _loc2;
                Selection.setSelection(_loc3[_loc2 - 1], _loc3[_loc2 - 1]);
            } // end else if
        }
        else if (_loc5 == 33)
        {
            _loc6 = label.bottomScroll - label.scroll + 1;
            _loc3 = this.getLineOffsets();
            _loc2 = label.scroll - 1;
            if (_loc2 < 1)
            {
                Selection.setSelection(0, 0);
            }
            else
            {
                Selection.setSelection(_loc3[_loc2 - 1], _loc3[_loc2 - 1]);
                label.scroll = Math.max(_loc2 - _loc6, 1);
            } // end else if
        } // end else if
    } // End of the function
    function draw(Void)
    {
        var _loc2 = label;
        var _loc4 = this.getText();
        if (initializing)
        {
            initializing = false;
            delete this.initText;
        } // end if
        var _loc3 = this._getTextFormat();
        _loc2.embedFonts = _loc3.embedFonts == true;
        if (_loc3 != undefined)
        {
            _loc2.setTextFormat(_loc3);
            _loc2.setNewTextFormat(_loc3);
        } // end if
        _loc2.multiline = true;
        _loc2.wordWrap = this.__get__wordWrap() == true;
        if (_loc2.html == true)
        {
            _loc2.setTextFormat(_loc3);
            _loc2.htmlText = _loc4;
        }
        else
        {
            _loc2.text = _loc4;
        } // end else if
        _loc2.type = this.__get__editable() == true ? ("input") : ("dynamic");
        this.size();
        _loc2.background = false;
    } // End of the function
    function adjustScrollBars()
    {
        var _loc2 = label;
        var _loc4 = _loc2.bottomScroll - _loc2.scroll + 1;
        var _loc3 = _loc4 + _loc2.maxscroll - 1;
        if (_loc3 < 1)
        {
            _loc3 = 1;
        } // end if
        var _loc5 = 0;
        if (_loc2.textWidth + 5 > _loc2._width)
        {
            if (!_loc2.wordWrap)
            {
                _loc5 = _loc2._width + _loc2.maxhscroll;
            } // end if
        }
        else
        {
            _loc2.hscroll = 0;
            _loc2.background = false;
        } // end else if
        if (_loc2.height / _loc4 != Math.round(_loc2.height / _loc4))
        {
            --_loc3;
        } // end if
        this.setScrollProperties(_loc5, 1, _loc3, _loc2.height / _loc4);
    } // End of the function
    function setScrollProperties(colCount, colWidth, rwCount, rwHeight, hPadding, wPadding)
    {
        super.setScrollProperties(colCount, colWidth, rwCount, rwHeight, hPadding, wPadding);
        if (vScroller == undefined)
        {
            hookedV = false;
        } // end if
        if (hScroller == undefined)
        {
            hookedH = false;
        } // end if
    } // End of the function
    function get tabIndex()
    {
        return (label.tabIndex);
    } // End of the function
    function set tabIndex(w)
    {
        label.tabIndex = w;
        //return (this.tabIndex());
        null;
    } // End of the function
    function set _accProps(val)
    {
        label._accProps = val;
        //return (this._accProps());
        null;
    } // End of the function
    function get _accProps()
    {
        return (label._accProps);
    } // End of the function
    function get styleSheet()
    {
        return (label.styleSheet);
    } // End of the function
    function set styleSheet(v)
    {
        label.styleSheet = v;
        //return (this.styleSheet());
        null;
    } // End of the function
    static var symbolName = "TextArea";
    static var symbolOwner = mx.controls.TextArea;
    static var version = "2.0.2.127";
    var className = "TextArea";
    var initializing = true;
    var clipParameters = {text: 1, wordWrap: 1, editable: 1, maxChars: 1, restrict: 1, html: 1, password: 1};
    static var mergedClipParameters = mx.core.UIObject.mergeClipParameters(mx.controls.TextArea.prototype.clipParameters, mx.core.ScrollView.prototype.clipParameters);
    var __vScrollPolicy = "auto";
    var __hScrollPolicy = "auto";
    var __editable = true;
} // End of Class
