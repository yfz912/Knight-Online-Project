class mx.controls.listclasses.SelectableRow extends mx.core.UIComponent
{
    var __height, cell, owner, rowIndex, icon_mc, createObject, __width, backGround, highlightColor, highlight, createLabel, createClassObject, listOwner, tabEnabled, item, createEmptyMovieClip, drawRect, isChangedToSelected, bGTween, grandOwner;
    function SelectableRow()
    {
        super();
    } // End of the function
    function setValue(itmObj, state)
    {
        var _loc7 = __height;
        var _loc2 = cell;
        var _loc5 = owner;
        var _loc8 = this.itemToString(itmObj);
        if (_loc2.getValue() != _loc8)
        {
            _loc2.setValue(_loc8, itmObj, state);
        } // end if
        var _loc4 = _loc5.getPropertiesAt(rowIndex + _loc5.__vPosition).icon;
        if (_loc4 == undefined)
        {
            _loc4 = _loc5.__iconFunction(itmObj);
            if (_loc4 == undefined)
            {
                _loc4 = itmObj[_loc5.__iconField];
                if (_loc4 == undefined)
                {
                    _loc4 = _loc5.getStyle("defaultIcon");
                } // end if
            } // end if
        } // end if
        var _loc3 = icon_mc;
        if (_loc4 != undefined && itmObj != undefined)
        {
            _loc3 = this.createObject(_loc4, "icon_mc", 20);
            _loc3._x = 2;
            _loc3._y = (_loc7 - _loc3._height) / 2;
            _loc2._x = 4 + _loc3._width;
        }
        else
        {
            _loc3.removeMovieClip();
            _loc2._x = 2;
        } // end else if
        var _loc9 = _loc3 == undefined ? (0) : (_loc3._width);
        _loc2.setSize(__width - _loc9, Math.min(_loc7, _loc2.getPreferredHeight()));
        _loc2._y = (_loc7 - _loc2._height) / 2;
    } // End of the function
    function size(Void)
    {
        var _loc3 = backGround;
        var _loc2 = cell;
        var _loc4 = __height;
        var _loc5 = __width;
        var _loc6 = icon_mc == undefined ? (0) : (icon_mc._width);
        _loc2.setSize(_loc5 - _loc6, Math.min(_loc4, _loc2.getPreferredHeight()));
        _loc2._y = (_loc4 - _loc2._height) / 2;
        icon_mc._y = (_loc4 - icon_mc._height) / 2;
        _loc3._x = 0;
        _loc3._width = _loc5;
        _loc3._height = _loc4;
        this.drawRowFill(_loc3, normalColor);
        this.drawRowFill(highlight, highlightColor);
    } // End of the function
    function setCellRenderer(forceSizing)
    {
        var _loc3 = owner.__cellRenderer;
        var _loc4;
        if (cell != undefined)
        {
            _loc4 = cell._x;
            cell.removeMovieClip();
            cell.removeTextField();
        } // end if
        var _loc2;
        if (_loc3 == undefined)
        {
            _loc2 = cell = this.createLabel("cll", 0, {styleName: this});
            _loc2.styleName = owner;
            _loc2.selectable = false;
            _loc2.tabEnabled = false;
            _loc2.background = false;
            _loc2.border = false;
        }
        else if (typeof(_loc3) == "string")
        {
            _loc2 = cell = this.createObject(_loc3, "cll", 0, {styleName: this});
        }
        else
        {
            _loc2 = cell = this.createClassObject(_loc3, "cll", 0, {styleName: this});
        } // end else if
        _loc2.owner = this;
        _loc2.listOwner = owner;
        _loc2.getCellIndex = getCellIndex;
        _loc2.getDataLabel = getDataLabel;
        if (_loc4 != undefined)
        {
            _loc2._x = _loc4;
        } // end if
        if (forceSizing)
        {
            this.size();
        } // end if
    } // End of the function
    function getCellIndex(Void)
    {
        return ({columnIndex: 0, itemIndex: owner.rowIndex + listOwner.__vPosition});
    } // End of the function
    function getDataLabel()
    {
        return (listOwner.labelField);
    } // End of the function
    function init(Void)
    {
        super.init();
        tabEnabled = false;
    } // End of the function
    function createChildren(Void)
    {
        this.setCellRenderer(false);
        this.setupBG();
        this.setState(state, false);
    } // End of the function
    function drawRow(itmObj, state, transition)
    {
        item = itmObj;
        this.setState(state, transition);
        this.setValue(itmObj, state, transition);
    } // End of the function
    function itemToString(itmObj)
    {
        if (itmObj == undefined)
        {
            return (" ");
        } // end if
        var _loc2 = owner.__labelFunction(itmObj);
        if (_loc2 == undefined)
        {
            _loc2 = itmObj instanceof XMLNode ? (itmObj.attributes[owner.__labelField]) : (itmObj[owner.__labelField]);
            if (_loc2 == undefined)
            {
                _loc2 = " ";
                if (typeof(itmObj) == "object")
                {
                    for (var _loc4 in itmObj)
                    {
                        if (_loc4 != "__ID__")
                        {
                            _loc2 = itmObj[_loc4] + ", " + _loc2;
                        } // end if
                    } // end of for...in
                    _loc2 = _loc2.substring(0, _loc2.length - 2);
                }
                else
                {
                    _loc2 = itmObj;
                } // end if
            } // end if
        } // end else if
        return (_loc2);
    } // End of the function
    function setupBG(Void)
    {
        var _loc2 = backGround = this.createEmptyMovieClip("bG_mc", mx.controls.listclasses.SelectableRow.LOWEST_DEPTH);
        this.drawRowFill(_loc2, normalColor);
        highlight = this.createEmptyMovieClip("tran_mc", mx.controls.listclasses.SelectableRow.LOWEST_DEPTH + 10);
        _loc2.owner = this;
        _loc2.grandOwner = owner;
        _loc2.onPress = bGOnPress;
        _loc2.onRelease = bGOnRelease;
        _loc2.onRollOver = bGOnRollOver;
        _loc2.onRollOut = bGOnRollOut;
        _loc2.onDragOver = bGOnDragOver;
        _loc2.onDragOut = bGOnDragOut;
        _loc2.useHandCursor = false;
        _loc2.trackAsMenu = true;
        _loc2.drawRect = drawRect;
        highlight.drawRect = drawRect;
    } // End of the function
    function drawRowFill(mc, newClr)
    {
        mc.clear();
        mc.beginFill(newClr);
        mc.drawRect(1, 0, __width, __height);
        mc.endFill();
        mc._width = __width;
        mc._height = __height;
    } // End of the function
    function setState(newState, transition)
    {
        var _loc2 = highlight;
        var _loc8 = backGround;
        var _loc4 = __height;
        var _loc3 = owner;
        if (!_loc3.enabled)
        {
            if (newState == "selected" || state == "selected")
            {
                highlightColor = _loc3.getStyle("selectionDisabledColor");
                this.drawRowFill(_loc2, highlightColor);
                _loc2._visible = true;
                _loc2._y = 0;
                _loc2._height = _loc4;
            }
            else
            {
                _loc2._visible = false;
                normalColor = _loc3.getStyle("backgroundDisabledColor");
                this.drawRowFill(_loc8, normalColor);
            } // end else if
            cell.__enabled = false;
            cell.setColor(_loc3.getStyle("disabledColor"));
        }
        else
        {
            cell.__enabled = true;
            if (transition && (newState == state || newState == "highlighted" && state == "selected"))
            {
                isChangedToSelected = true;
                return;
            } // end if
            var _loc6 = _loc3.getStyle("selectionDuration");
            var _loc7 = 0;
            if (isChangedToSelected && newState == "selected")
            {
                transition = false;
            } // end if
            var _loc10 = transition && _loc6 != 0;
            if (newState == "normal")
            {
                _loc7 = _loc3.getStyle("color");
                normalColor = this.getNormalColor();
                this.drawRowFill(_loc8, normalColor);
                if (_loc10)
                {
                    _loc6 = _loc6 / 2;
                    _loc2._height = _loc4;
                    _loc2._width = __width;
                    _loc2._y = 0;
                    bGTween = new mx.effects.Tween(this, _loc4 + 2, _loc4 * 0.200000, _loc6, 5);
                }
                else
                {
                    _loc2._visible = false;
                } // end else if
                delete this.isChangedToSelected;
            }
            else
            {
                highlightColor = _loc3.getStyle(newState == "highlighted" ? ("rollOverColor") : ("selectionColor"));
                this.drawRowFill(_loc2, highlightColor);
                _loc2._visible = true;
                _loc7 = _loc3.getStyle(newState == "highlighted" ? ("textRollOverColor") : ("textSelectedColor"));
                if (_loc10)
                {
                    _loc2._height = _loc4 * 0.500000;
                    _loc2._y = (_loc4 - _loc2._height) / 2;
                    bGTween = new mx.effects.Tween(this, _loc2._height, _loc4 + 2, _loc6, 5);
                    var _loc9 = _loc3.getStyle("selectionEasing");
                    if (_loc9 != undefined)
                    {
                        bGTween.easingEquation = _loc9;
                    } // end if
                }
                else
                {
                    _loc2._y = 0;
                    _loc2._height = _loc4;
                } // end else if
            } // end else if
            cell.setColor(_loc7);
        } // end else if
        state = newState;
    } // End of the function
    function onTweenUpdate(val)
    {
        highlight._height = val;
        highlight._y = (__height - val) / 2;
    } // End of the function
    function onTweenEnd(val)
    {
        this.onTweenUpdate(val);
        highlight._visible = state != "normal";
    } // End of the function
    function getNormalColor(Void)
    {
        var _loc3;
        var _loc2 = owner;
        if (!owner.enabled)
        {
            _loc3 = _loc2.getStyle("backgroundDisabledColor");
        }
        else
        {
            var _loc5 = rowIndex + _loc2.__vPosition;
            if (rowIndex == undefined)
            {
                _loc3 = _loc2.getPropertiesOf(item).backgroundColor;
            }
            else
            {
                _loc3 = _loc2.getPropertiesAt(_loc5).backgroundColor;
            } // end else if
            if (_loc3 == undefined)
            {
                var _loc4 = _loc2.getStyle("alternatingRowColors");
                if (_loc4 == undefined)
                {
                    _loc3 = _loc2.getStyle("backgroundColor");
                }
                else
                {
                    _loc3 = _loc4[_loc5 % _loc4.length];
                } // end if
            } // end else if
        } // end else if
        return (_loc3);
    } // End of the function
    function invalidateStyle(propName)
    {
        cell.invalidateStyle(propName);
        super.invalidateStyle(propName);
    } // End of the function
    function bGOnPress(Void)
    {
        grandOwner.pressFocus();
        grandOwner.onRowPress(owner.rowIndex);
    } // End of the function
    function bGOnRelease(Void)
    {
        grandOwner.releaseFocus();
        grandOwner.onRowRelease(owner.rowIndex);
    } // End of the function
    function bGOnRollOver(Void)
    {
        grandOwner.onRowRollOver(owner.rowIndex);
    } // End of the function
    function bGOnRollOut(Void)
    {
        grandOwner.onRowRollOut(owner.rowIndex);
    } // End of the function
    function bGOnDragOver(Void)
    {
        grandOwner.onRowDragOver(owner.rowIndex);
    } // End of the function
    function bGOnDragOut(Void)
    {
        grandOwner.onRowDragOut(owner.rowIndex);
    } // End of the function
    static var LOWEST_DEPTH = -16384;
    var state = "normal";
    var disabledColor = 15263976;
    var normalColor = 16777215;
} // End of Class
