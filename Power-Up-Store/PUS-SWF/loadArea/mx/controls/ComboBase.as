class mx.controls.ComboBase extends mx.core.UIComponent
{
    var getValue, tabEnabled, tabChildren, boundingBox_mc, downArrow_mc, createClassObject, onDownArrow, trackAsMenu, trackAsMenuWas, _parent, onPressWas, onDragOutWas, onDragOverWas, border_mc, __border, text_mc, oldOnSetFocus, oldOnKillFocus, focusTextField, __height, __width, getFocusManager, __get__height, __get__editable, __get__text, __get__restrict, height, __get__tabIndex, __set__editable, __set__restrict, __set__tabIndex, __set__text, __get__textField;
    function ComboBase()
    {
        super();
        getValue = _getValue;
    } // End of the function
    function init()
    {
        super.init();
        tabEnabled = !_editable;
        tabChildren = _editable;
        boundingBox_mc._visible = false;
        boundingBox_mc._width = boundingBox_mc._height = 0;
    } // End of the function
    function createChildren()
    {
        var _loc3 = new Object();
        _loc3.styleName = this;
        if (downArrow_mc == undefined)
        {
            _loc3.falseUpSkin = downArrowUpName;
            _loc3.falseOverSkin = downArrowOverName;
            _loc3.falseDownSkin = downArrowDownName;
            _loc3.falseDisabledSkin = downArrowDisabledName;
            _loc3.validateNow = true;
            _loc3.tabEnabled = false;
            this.createClassObject(mx.controls.SimpleButton, "downArrow_mc", 19, _loc3);
            downArrow_mc.buttonDownHandler = onDownArrow;
            downArrow_mc.useHandCursor = false;
            downArrow_mc.onPressWas = downArrow_mc.onPress;
            downArrow_mc.onPress = function ()
            {
                trackAsMenuWas = trackAsMenu;
                trackAsMenu = true;
                if (!_editable)
                {
                    _parent.text_mc.trackAsMenu = trackAsMenu;
                } // end if
                this.onPressWas();
            };
            downArrow_mc.onDragOutWas = downArrow_mc.onDragOut;
            downArrow_mc.onDragOut = function ()
            {
                trackAsMenuWas = trackAsMenu;
                trackAsMenu = false;
                if (!_editable)
                {
                    _parent.text_mc.trackAsMenu = trackAsMenu;
                } // end if
                this.onDragOutWas();
            };
            downArrow_mc.onDragOverWas = downArrow_mc.onDragOver;
            downArrow_mc.onDragOver = function ()
            {
                trackAsMenu = trackAsMenuWas;
                if (!_editable)
                {
                    _parent.text_mc.trackAsMenu = trackAsMenu;
                } // end if
                this.onDragOverWas();
            };
        } // end if
        if (border_mc == undefined)
        {
            _loc3.tabEnabled = false;
            this.createClassObject(_global.styles.rectBorderClass, "border_mc", 17, _loc3);
            border_mc.move(0, 0);
            __border = border_mc;
        } // end if
        _loc3.borderStyle = "none";
        _loc3.readOnly = !_editable;
        _loc3.tabEnabled = _editable;
        if (text_mc == undefined)
        {
            this.createClassObject(mx.controls.TextInput, "text_mc", 18, _loc3);
            text_mc.move(0, 0);
            text_mc.addEnterEvents();
            text_mc.enterHandler = _enterHandler;
            text_mc.changeHandler = _changeHandler;
            text_mc.oldOnSetFocus = text_mc.onSetFocus;
            text_mc.onSetFocus = function ()
            {
                this.oldOnSetFocus();
                _parent.onSetFocus();
            };
            text_mc.__set__restrict("^\x1b");
            text_mc.oldOnKillFocus = text_mc.onKillFocus;
            text_mc.onKillFocus = function (n)
            {
                this.oldOnKillFocus(n);
                _parent.onKillFocus(n);
            };
            text_mc.drawFocus = function (b)
            {
                _parent.drawFocus(b);
            };
            delete text_mc.borderStyle;
        } // end if
        focusTextField = text_mc;
        text_mc.owner = this;
        this.layoutChildren(__width, __height);
    } // End of the function
    function onKillFocus()
    {
        super.onKillFocus();
        Key.removeListener(text_mc);
        this.getFocusManager().defaultPushButtonEnabled = true;
    } // End of the function
    function onSetFocus()
    {
        super.onSetFocus();
        this.getFocusManager().defaultPushButtonEnabled = false;
        Key.addListener(text_mc);
    } // End of the function
    function setFocus()
    {
        if (_editable)
        {
            Selection.setFocus(text_mc);
        }
        else
        {
            Selection.setFocus(this);
        } // end else if
    } // End of the function
    function setSize(w, h, noEvent)
    {
        super.setSize(w, h == undefined ? (this.__get__height()) : (h), noEvent);
    } // End of the function
    function setEnabled(enabledFlag)
    {
        super.setEnabled(enabledFlag);
        downArrow_mc.enabled = enabledFlag;
        text_mc.enabled = enabledFlag;
    } // End of the function
    function setEditable(e)
    {
        _editable = e;
        if (wrapDownArrowButton == false)
        {
            if (e)
            {
                border_mc.borderStyle = "inset";
                text_mc.borderStyle = "inset";
                symbolName = "ComboBox";
                this.invalidateStyle();
            }
            else
            {
                border_mc.borderStyle = "comboNonEdit";
                text_mc.borderStyle = "dropDown";
                symbolName = "DropDown";
                this.invalidateStyle();
            } // end if
        } // end else if
        tabEnabled = !e;
        tabChildren = e;
        text_mc.tabEnabled = e;
        if (e)
        {
            delete text_mc.onPress;
            delete text_mc.onRelease;
            delete text_mc.onReleaseOutside;
            delete text_mc.onDragOut;
            delete text_mc.onDragOver;
            delete text_mc.onRollOver;
            delete text_mc.onRollOut;
        }
        else
        {
            text_mc.onPress = function ()
            {
                _parent.downArrow_mc.onPress();
            };
            text_mc.onRelease = function ()
            {
                _parent.downArrow_mc.onRelease();
            };
            text_mc.onReleaseOutside = function ()
            {
                _parent.downArrow_mc.onReleaseOutside();
            };
            text_mc.onDragOut = function ()
            {
                _parent.downArrow_mc.onDragOut();
            };
            text_mc.onDragOver = function ()
            {
                _parent.downArrow_mc.onDragOver();
            };
            text_mc.onRollOver = function ()
            {
                _parent.downArrow_mc.onRollOver();
            };
            text_mc.onRollOut = function ()
            {
                _parent.downArrow_mc.onRollOut();
            };
            text_mc.useHandCursor = false;
        } // end else if
    } // End of the function
    function get editable()
    {
        return (_editable);
    } // End of the function
    function set editable(e)
    {
        this.setEditable(e);
        //return (this.editable());
        null;
    } // End of the function
    function _getValue()
    {
        return (_editable ? (text_mc.getText()) : (this.DSgetValue()));
    } // End of the function
    function draw()
    {
        downArrow_mc.draw();
        border_mc.draw();
    } // End of the function
    function size()
    {
        this.layoutChildren(__width, __height);
    } // End of the function
    function setTheme(t)
    {
        downArrowUpName = t + "downArrow" + "Up_mc";
        downArrowDownName = t + "downArrow" + "Down_mc";
        downArrowDisabledName = t + "downArrow" + "Disabled_mc";
    } // End of the function
    function get text()
    {
        return (text_mc.getText());
    } // End of the function
    function set text(t)
    {
        this.setText(t);
        //return (this.text());
        null;
    } // End of the function
    function setText(t)
    {
        text_mc.setText(t);
    } // End of the function
    function get textField()
    {
        return (text_mc);
    } // End of the function
    function get restrict()
    {
        //return (text_mc.restrict());
    } // End of the function
    function set restrict(w)
    {
        text_mc.__set__restrict(w);
        //return (this.restrict());
        null;
    } // End of the function
    function invalidateStyle()
    {
        downArrow_mc.invalidateStyle();
        text_mc.invalidateStyle();
        border_mc.invalidateStyle();
    } // End of the function
    function layoutChildren(w, h)
    {
        if (downArrow_mc == undefined)
        {
            return;
        } // end if
        if (wrapDownArrowButton)
        {
            var _loc2 = border_mc.__get__borderMetrics();
            downArrow_mc._width = downArrow_mc._height = h - _loc2.top - _loc2.bottom;
            downArrow_mc.move(w - downArrow_mc._width - _loc2.right, _loc2.top);
            border_mc.setSize(w, h);
            text_mc.setSize(w - downArrow_mc._width, h);
        }
        else
        {
            downArrow_mc.move(w - downArrow_mc._width, 0);
            border_mc.setSize(w - downArrow_mc.width, h);
            text_mc.setSize(w - downArrow_mc._width, h);
            downArrow_mc._height = height;
        } // end else if
    } // End of the function
    function _changeHandler(obj)
    {
    } // End of the function
    function _enterHandler(obj)
    {
        var _loc2 = _parent;
        obj.target = _loc2;
        _loc2.dispatchEvent(obj);
    } // End of the function
    function get tabIndex()
    {
        //return (text_mc.tabIndex());
    } // End of the function
    function set tabIndex(w)
    {
        text_mc.__set__tabIndex(w);
        //return (this.tabIndex());
        null;
    } // End of the function
    static var mixIt1 = mx.controls.listclasses.DataSelector.Initialize(mx.controls.ComboBase);
    static var symbolName = "ComboBase";
    static var symbolOwner = mx.controls.ComboBase;
    static var version = "2.0.2.127";
    var _editable = false;
    var downArrowUpName = "ScrollDownArrowUp";
    var downArrowDownName = "ScrollDownArrowDown";
    var downArrowOverName = "ScrollDownArrowOver";
    var downArrowDisabledName = "ScrollDownArrowDisabled";
    var wrapDownArrowButton = true;
    var DSgetValue = mx.controls.listclasses.DataSelector.prototype.getValue;
    var multipleSelection = false;
} // End of Class
