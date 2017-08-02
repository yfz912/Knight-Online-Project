class mx.controls.ComboBox extends mx.controls.ComboBase
{
    var editable, __set__editable, __labels, __get__labels, data, __dropdownWidth, __width, __set__dropdownWidth, _editable, selectedIndex, __dropdown, dataProvider, __labelFunction, owner, wrapDownArrowButton, _y, createObject, mask, border_mc, text_mc, __get__selectedLabel, __get__labelField, __get__labelFunction, getValue, dispatchValueChangedEvent, length, __get__rowCount, __get__dropdownWidth, selectedItem, isPressed, __set__visible, height, localToGlobal, __selectedIndexOnDropdown, __initialSelectedIndexOnDropdown, __get__height, getStyle, _parent, __get__dropdown, width, __dataProvider, selected, dispatchEvent, __set__labelField, __set__labelFunction, __set__labels, __set__rowCount;
    function ComboBox()
    {
        super();
    } // End of the function
    function init()
    {
        super.init();
    } // End of the function
    function createChildren()
    {
        super.createChildren();
        this.__set__editable(editable);
        if (__labels.length > 0)
        {
            var _loc6 = new Array();
            for (var _loc3 = 0; _loc3 < this.__get__labels().length; ++_loc3)
            {
                _loc6.addItem({label: this.__get__labels()[_loc3], data: data[_loc3]});
            } // end of for
            this.setDataProvider(_loc6);
        } // end if
        this.__set__dropdownWidth(typeof(__dropdownWidth) == "number" ? (__dropdownWidth) : (__width));
        if (!_editable)
        {
            selectedIndex = 0;
        } // end if
        initializing = false;
    } // End of the function
    function onKillFocus(n)
    {
        if (_showingDropdown && n != null)
        {
            this.displayDropdown(false);
        } // end if
        super.onKillFocus();
    } // End of the function
    function getDropdown()
    {
        if (initializing)
        {
            return;
        } // end if
        if (!this.hasDropdown())
        {
            var _loc3 = new Object();
            _loc3.styleName = this;
            if (dropdownBorderStyle != undefined)
            {
                _loc3.borderStyle = dropdownBorderStyle;
            } // end if
            _loc3._visible = false;
            __dropdown = mx.managers.PopUpManager.createPopUp(this, mx.controls.List, false, _loc3, true);
            __dropdown.scroller.mask.removeMovieClip();
            if (dataProvider == undefined)
            {
                dataProvider = new Array();
            } // end if
            __dropdown.setDataProvider(dataProvider);
            __dropdown.selectMultiple = false;
            __dropdown.rowCount = __rowCount;
            __dropdown.selectedIndex = selectedIndex;
            __dropdown.vScrollPolicy = "auto";
            __dropdown.labelField = __labelField;
            __dropdown.labelFunction = __labelFunction;
            __dropdown.owner = this;
            __dropdown.changeHandler = _changeHandler;
            __dropdown.scrollHandler = _scrollHandler;
            __dropdown.itemRollOverHandler = _itemRollOverHandler;
            __dropdown.itemRollOutHandler = _itemRollOutHandler;
            __dropdown.resizeHandler = _resizeHandler;
            __dropdown.mouseDownOutsideHandler = function (eventObj)
            {
                var _loc3 = owner;
                var _loc4 = new Object();
                _loc4.x = _loc3._root._xmouse;
                _loc4.y = _loc3._root._ymouse;
                _loc3._root.localToGlobal(_loc4);
                if (_loc3.hitTest(_loc4.x, _loc4.y, false))
                {
                }
                else if (!wrapDownArrowButton && owner.downArrow_mc.hitTest(_root._xmouse, _root._ymouse, false))
                {
                }
                else
                {
                    _loc3.displayDropdown(false);
                } // end else if
            };
            __dropdown.onTweenUpdate = function (v)
            {
                _y = v;
            };
            __dropdown.setSize(__dropdownWidth, __dropdown.height);
            this.createObject("BoundingBox", "mask", 20);
            mask._y = border_mc.height;
            mask._width = __dropdownWidth;
            mask._height = __dropdown.height;
            mask._visible = false;
            __dropdown.setMask(mask);
        } // end if
        return (__dropdown);
    } // End of the function
    function setSize(w, h, noEvent)
    {
        super.setSize(w, h, noEvent);
        __dropdownWidth = w;
        __dropdown.rowHeight = h;
        __dropdown.setSize(__dropdownWidth, __dropdown.height);
    } // End of the function
    function setEditable(e)
    {
        super.setEditable(e);
        if (e)
        {
            text_mc.setText("");
        }
        else
        {
            text_mc.setText(this.__get__selectedLabel());
        } // end else if
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
    function getLabelField()
    {
        return (__labelField);
    } // End of the function
    function get labelField()
    {
        return (this.getLabelField());
    } // End of the function
    function setLabelField(s)
    {
        __dropdown.labelField = __labelField = s;
        text_mc.setText(this.__get__selectedLabel());
    } // End of the function
    function set labelField(s)
    {
        this.setLabelField(s);
        //return (this.labelField());
        null;
    } // End of the function
    function getLabelFunction()
    {
        return (__labelFunction);
    } // End of the function
    function get labelFunction()
    {
        return (this.getLabelFunction());
    } // End of the function
    function set labelFunction(f)
    {
        __dropdown.labelFunction = __labelFunction = f;
        text_mc.setText(this.__get__selectedLabel());
        //return (this.labelFunction());
        null;
    } // End of the function
    function setSelectedItem(v)
    {
        super.setSelectedItem(v);
        __dropdown.selectedItem = v;
        text_mc.setText(this.__get__selectedLabel());
    } // End of the function
    function setSelectedIndex(v)
    {
        super.setSelectedIndex(v);
        __dropdown.selectedIndex = v;
        if (v != undefined)
        {
            text_mc.setText(this.__get__selectedLabel());
        } // end if
        this.dispatchValueChangedEvent(this.getValue());
    } // End of the function
    function setRowCount(count)
    {
        if (isNaN(count))
        {
            return;
        } // end if
        __rowCount = count;
        __dropdown.setRowCount(count);
    } // End of the function
    function get rowCount()
    {
        return (Math.max(1, Math.min(length, __rowCount)));
    } // End of the function
    function set rowCount(v)
    {
        this.setRowCount(v);
        //return (this.rowCount());
        null;
    } // End of the function
    function setDropdownWidth(w)
    {
        __dropdownWidth = w;
        __dropdown.setSize(w, __dropdown.height);
    } // End of the function
    function get dropdownWidth()
    {
        return (__dropdownWidth);
    } // End of the function
    function set dropdownWidth(v)
    {
        this.setDropdownWidth(v);
        //return (this.dropdownWidth());
        null;
    } // End of the function
    function get dropdown()
    {
        return (this.getDropdown());
    } // End of the function
    function setDataProvider(dp)
    {
        super.setDataProvider(dp);
        __dropdown.setDataProvider(dp);
        if (!_editable)
        {
            selectedIndex = 0;
        } // end if
    } // End of the function
    function open()
    {
        this.displayDropdown(true);
    } // End of the function
    function close()
    {
        this.displayDropdown(false);
    } // End of the function
    function get selectedLabel()
    {
        var _loc2 = selectedItem;
        if (_loc2 == undefined)
        {
            return ("");
        }
        else if (this.__get__labelFunction() != undefined)
        {
            //return (this.labelFunction()(_loc2));
        }
        else if (typeof(_loc2) != "object")
        {
            return (_loc2);
        }
        else if (_loc2[this.__get__labelField()] != undefined)
        {
            //return (_loc2[this.labelField()]);
        }
        else if (_loc2.label != undefined)
        {
            return (_loc2.label);
        }
        else
        {
            var _loc3 = " ";
            for (var _loc4 in _loc2)
            {
                if (_loc4 != "__ID__")
                {
                    _loc3 = _loc2[_loc4] + ", " + _loc3;
                } // end if
            } // end of for...in
            _loc3 = _loc3.substring(0, _loc3.length - 3);
            return (_loc3);
        } // end else if
    } // End of the function
    function hasDropdown()
    {
        return (__dropdown != undefined && __dropdown.valueOf() != undefined);
    } // End of the function
    function tweenEndShow(value)
    {
        _y = value;
        isPressed = true;
        owner.dispatchEvent({type: "open", target: owner});
    } // End of the function
    function tweenEndHide(value)
    {
        _y = value;
        this.__set__visible(false);
        owner.dispatchEvent({type: "close", target: owner});
    } // End of the function
    function displayDropdown(show)
    {
        if (show == _showingDropdown)
        {
            return;
        } // end if
        var _loc3 = new Object();
        _loc3.x = 0;
        _loc3.y = height;
        this.localToGlobal(_loc3);
        if (show)
        {
            __selectedIndexOnDropdown = selectedIndex;
            __initialSelectedIndexOnDropdown = selectedIndex;
            this.getDropdown();
            var _loc2 = __dropdown;
            _loc2.isPressed = true;
            _loc2.rowCount = rowCount;
            _loc2.visible = show;
            _loc2._parent.globalToLocal(_loc3);
            _loc2.onTweenEnd = tweenEndShow;
            var _loc5;
            var _loc8;
            if (_loc3.y + _loc2.height > Stage.height)
            {
                _loc5 = _loc3.y - this.__get__height();
                _loc8 = _loc5 - _loc2.height;
                mask._y = -_loc2.height;
            }
            else
            {
                _loc5 = _loc3.y - _loc2.height;
                _loc8 = _loc3.y;
                mask._y = border_mc.height;
            } // end else if
            var _loc6 = _loc2.selectedIndex;
            if (_loc6 == undefined)
            {
                _loc6 = 0;
            } // end if
            var _loc4 = _loc2.vPosition;
            _loc4 = _loc6 - 1;
            _loc4 = Math.min(Math.max(_loc4, 0), _loc2.length - _loc2.rowCount);
            _loc2.vPosition = _loc4;
            _loc2.move(_loc3.x, _loc5);
            _loc2.tween = new mx.effects.Tween(__dropdown, _loc5, _loc8, this.getStyle("openDuration"));
        }
        else
        {
            __dropdown._parent.globalToLocal(_loc3);
            delete __dropdown.dragScrolling;
            __dropdown.onTweenEnd = tweenEndHide;
            __dropdown.tween = new mx.effects.Tween(__dropdown, __dropdown._y, _loc3.y - __dropdown.height, this.getStyle("openDuration"));
            if (__initialSelectedIndexOnDropdown != selectedIndex)
            {
                this.dispatchChangeEvent(undefined, __initialSelectedIndexOnDropdown, selectedIndex);
            } // end if
        } // end else if
        var _loc9 = this.getStyle("openEasing");
        if (_loc9 != undefined)
        {
            __dropdown.tween.easingEquation = _loc9;
        } // end if
        _showingDropdown = show;
    } // End of the function
    function onDownArrow()
    {
        _parent.displayDropdown(!_parent._showingDropdown);
    } // End of the function
    function keyDown(e)
    {
        if (e.ctrlKey && e.code == 40)
        {
            this.displayDropdown(true);
        }
        else if (e.ctrlKey && e.code == 38)
        {
            this.displayDropdown(false);
            this.dispatchChangeEvent(undefined, __selectedIndexOnDropdown, selectedIndex);
        }
        else if (e.code == 27)
        {
            this.displayDropdown(false);
        }
        else if (e.code == 13)
        {
            if (_showingDropdown)
            {
                selectedIndex = __dropdown.selectedIndex;
                this.displayDropdown(false);
            } // end if
        }
        else if (!_editable || e.code == 38 || e.code == 40 || e.code == 33 || e.code == 34)
        {
            selectedIndex = 0 + selectedIndex;
            bInKeyDown = true;
            var _loc3 = this.__get__dropdown();
            _loc3.keyDown(e);
            bInKeyDown = false;
            selectedIndex = __dropdown.selectedIndex;
        } // end else if
    } // End of the function
    function invalidateStyle(styleProp)
    {
        __dropdown.invalidateStyle(styleProp);
        super.invalidateStyle(styleProp);
    } // End of the function
    function changeTextStyleInChildren(styleProp)
    {
        if (this.__get__dropdown().stylecache != undefined)
        {
            delete this.__get__dropdown().stylecache[styleProp];
            delete this.__get__dropdown().stylecache.tf;
        } // end if
        __dropdown.changeTextStyleInChildren(styleProp);
        super.changeTextStyleInChildren(styleProp);
    } // End of the function
    function changeColorStyleInChildren(sheetName, styleProp, newValue)
    {
        if (this.__get__dropdown().stylecache != undefined)
        {
            delete this.__get__dropdown().stylecache[styleProp];
            delete this.__get__dropdown().stylecache.tf;
        } // end if
        __dropdown.changeColorStyleInChildren(sheetName, styleProp, newValue);
        super.changeColorStyleInChildren(sheetName, styleProp, newValue);
    } // End of the function
    function notifyStyleChangeInChildren(sheetName, styleProp, newValue)
    {
        if (this.__get__dropdown().stylecache != undefined)
        {
            delete this.__get__dropdown().stylecache[styleProp];
            delete this.__get__dropdown().stylecache.tf;
        } // end if
        __dropdown.notifyStyleChangeInChildren(sheetName, styleProp, newValue);
        super.notifyStyleChangeInChildren(sheetName, styleProp, newValue);
    } // End of the function
    function onUnload()
    {
        __dropdown.removeMovieClip();
    } // End of the function
    function _resizeHandler()
    {
        var _loc2 = owner;
        _loc2.mask._width = width;
        _loc2.mask._height = height;
    } // End of the function
    function _changeHandler(obj)
    {
        var _loc2 = owner;
        var _loc3 = _loc2.selectedIndex;
        obj.target = _loc2;
        if (this == owner.text_mc)
        {
            _loc2.selectedIndex = undefined;
            _loc2.dispatchChangeEvent(obj, -1, -2);
        }
        else
        {
            _loc2.selectedIndex = selectedIndex;
            if (!_loc2._showingDropdown)
            {
                _loc2.dispatchChangeEvent(obj, _loc3, _loc2.selectedIndex);
            }
            else if (!_loc2.bInKeyDown)
            {
                _loc2.displayDropdown(false);
            } // end else if
        } // end else if
    } // End of the function
    function _scrollHandler(obj)
    {
        var _loc2 = owner;
        obj.target = _loc2;
        _loc2.dispatchEvent(obj);
    } // End of the function
    function _itemRollOverHandler(obj)
    {
        var _loc2 = owner;
        obj.target = _loc2;
        _loc2.dispatchEvent(obj);
    } // End of the function
    function _itemRollOutHandler(obj)
    {
        var _loc2 = owner;
        obj.target = _loc2;
        _loc2.dispatchEvent(obj);
    } // End of the function
    function modelChanged(eventObj)
    {
        super.modelChanged(eventObj);
        if (__dataProvider.length == 0)
        {
            text_mc.setText("");
            delete this.selected;
        }
        else if (__dataProvider.length == eventObj.lastItem - eventObj.firstItem + 1 && eventObj.eventName == "addItems")
        {
            selectedIndex = 0;
        } // end else if
    } // End of the function
    function dispatchChangeEvent(obj, prevValue, newValue)
    {
        var _loc2;
        if (prevValue != newValue)
        {
            if (obj != undefined && obj.type == "change")
            {
                _loc2 = obj;
            }
            else
            {
                _loc2 = {type: "change"};
            } // end else if
            this.dispatchEvent(_loc2);
        } // end if
    } // End of the function
    static var symbolName = "ComboBox";
    static var symbolOwner = mx.controls.ComboBox;
    static var version = "2.0.2.127";
    var clipParameters = {labels: 1, data: 1, editable: 1, rowCount: 1, dropdownWidth: 1};
    static var mergedClipParameters = mx.core.UIObject.mergeClipParameters(mx.controls.ComboBox.prototype.clipParameters, mx.controls.ComboBase.prototype.clipParameters);
    var className = "ComboBox";
    var _showingDropdown = false;
    var __rowCount = 5;
    var dropdownBorderStyle = undefined;
    var initializing = true;
    var __labelField = "label";
    var bInKeyDown = false;
} // End of Class
