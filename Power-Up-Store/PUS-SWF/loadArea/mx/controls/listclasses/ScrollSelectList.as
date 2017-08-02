class mx.controls.listclasses.ScrollSelectList extends mx.core.ScrollView
{
    var invLayoutContent, rows, topRowZ, listContent, __vPosition, __dataProvider, tW, layoutX, layoutY, tH, invRowHeight, invalidate, __get__rowHeight, __height, __get__rowCount, invUpdateControl, __cellRenderer, __get__cellRenderer, __get__labelField, __get__labelFunction, __labelFunction, __get__iconField, __iconField, __get__iconFunction, __iconFunction, getLength, baseRowZ, lastPosition, propertyTable, isSelected, wasKeySelected, changeFlag, clearSelected, selectItem, lastSelected, dispatchEvent, dragScrolling, _ymouse, scrollInterval, isPressed, onMouseUp, getSelectedIndex, enabled, tabEnabled, tabChildren, createEmptyMovieClip, border_mc, __set__cellRenderer, __set__iconField, __set__iconFunction, __set__labelField, __set__labelFunction, __set__rowCount, __set__rowHeight;
    function ScrollSelectList()
    {
        super();
    } // End of the function
    function layoutContent(x, y, w, h)
    {
        delete this.invLayoutContent;
        var _loc4 = Math.ceil(h / __rowHeight);
        roundUp = h % __rowHeight != 0;
        var _loc12 = _loc4 - __rowCount;
        if (_loc12 < 0)
        {
            for (var _loc3 = _loc4; _loc3 < __rowCount; ++_loc3)
            {
                rows[_loc3].removeMovieClip();
                delete rows[_loc3];
            } // end of for
            topRowZ = topRowZ + _loc12;
        }
        else if (_loc12 > 0)
        {
            if (rows == undefined)
            {
                rows = new Array();
            } // end if
            for (var _loc3 = __rowCount; _loc3 < _loc4; ++_loc3)
            {
                var _loc2 = rows[_loc3] = listContent.createObject(__rowRenderer, "listRow" + topRowZ++, topRowZ, {owner: this, styleName: this, rowIndex: _loc3});
                _loc2._x = x;
                _loc2._y = Math.round(_loc3 * __rowHeight + y);
                _loc2.setSize(w, __rowHeight);
                _loc2.drawRow(__dataProvider.getItemAt(__vPosition + _loc3), this.getStateAt(__vPosition + _loc3));
                _loc2.lastY = _loc2._y;
            } // end of for
        } // end else if
        if (w != tW)
        {
            var _loc11 = _loc12 > 0 ? (__rowCount) : (_loc4);
            for (var _loc3 = 0; _loc3 < _loc11; ++_loc3)
            {
                rows[_loc3].setSize(w, __rowHeight);
            } // end of for
        } // end if
        if (layoutX != x || layoutY != y)
        {
            for (var _loc3 = 0; _loc3 < _loc4; ++_loc3)
            {
                rows[_loc3]._x = x;
                rows[_loc3]._y = Math.round(_loc3 * __rowHeight + y);
            } // end of for
        } // end if
        __rowCount = _loc4;
        layoutX = x;
        layoutY = y;
        tW = w;
        tH = h;
    } // End of the function
    function getRowHeight(Void)
    {
        return (__rowHeight);
    } // End of the function
    function setRowHeight(v)
    {
        __rowHeight = v;
        invRowHeight = true;
        this.invalidate();
    } // End of the function
    function get rowHeight()
    {
        return (this.getRowHeight());
    } // End of the function
    function set rowHeight(w)
    {
        this.setRowHeight(w);
        //return (this.rowHeight());
        null;
    } // End of the function
    function setRowCount(v)
    {
        __rowCount = v;
    } // End of the function
    function getRowCount(Void)
    {
        var _loc2 = __rowCount == 0 ? (Math.ceil(__height / __rowHeight)) : (__rowCount);
        return (_loc2);
    } // End of the function
    function get rowCount()
    {
        return (this.getRowCount());
    } // End of the function
    function set rowCount(w)
    {
        this.setRowCount(w);
        //return (this.rowCount());
        null;
    } // End of the function
    function setEnabled(v)
    {
        super.setEnabled(v);
        invUpdateControl = true;
        this.invalidate();
    } // End of the function
    function setCellRenderer(cR)
    {
        __cellRenderer = cR;
        for (var _loc2 = 0; _loc2 < rows.length; ++_loc2)
        {
            rows[_loc2].setCellRenderer(true);
        } // end of for
        invUpdateControl = true;
        this.invalidate();
    } // End of the function
    function set cellRenderer(cR)
    {
        this.setCellRenderer(cR);
        //return (this.cellRenderer());
        null;
    } // End of the function
    function get cellRenderer()
    {
        return (__cellRenderer);
    } // End of the function
    function set labelField(field)
    {
        this.setLabelField(field);
        //return (this.labelField());
        null;
    } // End of the function
    function setLabelField(field)
    {
        __labelField = field;
        invUpdateControl = true;
        this.invalidate();
    } // End of the function
    function get labelField()
    {
        return (__labelField);
    } // End of the function
    function set labelFunction(func)
    {
        this.setLabelFunction(func);
        //return (this.labelFunction());
        null;
    } // End of the function
    function setLabelFunction(func)
    {
        __labelFunction = func;
        invUpdateControl = true;
        this.invalidate();
    } // End of the function
    function get labelFunction()
    {
        return (__labelFunction);
    } // End of the function
    function set iconField(field)
    {
        this.setIconField(field);
        //return (this.iconField());
        null;
    } // End of the function
    function setIconField(field)
    {
        __iconField = field;
        invUpdateControl = true;
        this.invalidate();
    } // End of the function
    function get iconField()
    {
        return (__iconField);
    } // End of the function
    function set iconFunction(func)
    {
        this.setIconFunction(func);
        //return (this.iconFunction());
        null;
    } // End of the function
    function setIconFunction(func)
    {
        __iconFunction = func;
        invUpdateControl = true;
        this.invalidate();
    } // End of the function
    function get iconFunction()
    {
        return (__iconFunction);
    } // End of the function
    function setVPosition(pos)
    {
        if (pos < 0)
        {
            return;
        } // end if
        if (pos > 0 && pos > this.getLength() - __rowCount + roundUp)
        {
            return;
        } // end if
        var _loc8 = pos - __vPosition;
        if (_loc8 == 0)
        {
            return;
        } // end if
        __vPosition = pos;
        var _loc10 = _loc8 > 0;
        _loc8 = Math.abs(_loc8);
        if (_loc8 >= __rowCount)
        {
            this.updateControl();
        }
        else
        {
            var _loc4 = new Array();
            var _loc9 = __rowCount - _loc8;
            var _loc12 = _loc8 * __rowHeight;
            var _loc11 = _loc9 * __rowHeight;
            var _loc6 = _loc10 ? (1) : (-1);
            for (var _loc3 = 0; _loc3 < __rowCount; ++_loc3)
            {
                if (_loc3 < _loc8 && _loc10 || _loc3 >= _loc9 && !_loc10)
                {
                    rows[_loc3]._y = rows[_loc3]._y + Math.round(_loc6 * _loc11);
                    var _loc5 = _loc3 + _loc6 * _loc9;
                    var _loc7 = __vPosition + _loc5;
                    _loc4[_loc5] = rows[_loc3];
                    _loc4[_loc5].rowIndex = _loc5;
                    _loc4[_loc5].drawRow(__dataProvider.getItemAt(_loc7), this.getStateAt(_loc7), false);
                    continue;
                } // end if
                rows[_loc3]._y = rows[_loc3]._y - Math.round(_loc6 * _loc12);
                _loc5 = _loc3 - _loc6 * _loc8;
                _loc4[_loc5] = rows[_loc3];
                _loc4[_loc5].rowIndex = _loc5;
            } // end of for
            rows = _loc4;
            for (var _loc3 = 0; _loc3 < __rowCount; ++_loc3)
            {
                rows[_loc3].swapDepths(baseRowZ + _loc3);
            } // end of for
        } // end else if
        lastPosition = pos;
        super.setVPosition(pos);
    } // End of the function
    function setPropertiesAt(index, obj)
    {
        var _loc2 = __dataProvider.getItemID(index);
        if (_loc2 == undefined)
        {
            return;
        } // end if
        if (propertyTable == undefined)
        {
            propertyTable = new Object();
        } // end if
        propertyTable[_loc2] = obj;
        rows[index - __vPosition].drawRow(__dataProvider.getItemAt(index), this.getStateAt(index));
    } // End of the function
    function getPropertiesAt(index)
    {
        var _loc2 = __dataProvider.getItemID(index);
        if (_loc2 == undefined)
        {
            return;
        } // end if
        return (propertyTable[_loc2]);
    } // End of the function
    function getPropertiesOf(obj)
    {
        var _loc2 = obj.getID();
        if (_loc2 == undefined)
        {
            return;
        } // end if
        return (propertyTable[_loc2]);
    } // End of the function
    function getStyle(styleProp)
    {
        var _loc2 = super.getStyle(styleProp);
        var _loc3 = mx.styles.StyleManager.colorNames[_loc2];
        if (_loc3 != undefined)
        {
            _loc2 = _loc3;
        } // end if
        return (_loc2);
    } // End of the function
    function updateControl(Void)
    {
        for (var _loc2 = 0; _loc2 < __rowCount; ++_loc2)
        {
            rows[_loc2].drawRow(__dataProvider.getItemAt(_loc2 + __vPosition), this.getStateAt(_loc2 + __vPosition));
        } // end of for
        delete this.invUpdateControl;
    } // End of the function
    function getStateAt(index)
    {
        return (this.isSelected(index) ? ("selected") : ("normal"));
    } // End of the function
    function selectRow(rowIndex, transition, allowChangeEvent)
    {
        if (!selectable)
        {
            return;
        } // end if
        var _loc3 = __vPosition + rowIndex;
        var _loc8 = __dataProvider.getItemAt(_loc3);
        var _loc5 = rows[rowIndex];
        if (_loc8 == undefined)
        {
            return;
        } // end if
        if (transition == undefined)
        {
            transition = true;
        } // end if
        if (allowChangeEvent == undefined)
        {
            allowChangeEvent = wasKeySelected;
        } // end if
        changeFlag = true;
        if (!multipleSelection && !Key.isDown(17) || !Key.isDown(16) && !Key.isDown(17))
        {
            this.clearSelected(transition);
            this.selectItem(_loc3, true);
            lastSelected = _loc3;
            _loc5.drawRow(_loc5.item, this.getStateAt(_loc3), transition);
        }
        else if (Key.isDown(16) && multipleSelection)
        {
            if (lastSelected == undefined)
            {
                lastSelected = _loc3;
            } // end if
            var _loc4 = lastSelected < _loc3 ? (1) : (-1);
            this.clearSelected(false);
            for (var _loc2 = lastSelected; _loc2 != _loc3; _loc2 = _loc2 + _loc4)
            {
                this.selectItem(_loc2, true);
                if (_loc2 >= __vPosition && _loc2 < __vPosition + __rowCount)
                {
                    rows[_loc2 - __vPosition].drawRow(rows[_loc2 - __vPosition].item, "selected", false);
                } // end if
            } // end of for
            this.selectItem(_loc3, true);
            _loc5.drawRow(_loc5.item, "selected", transition);
        }
        else if (Key.isDown(17))
        {
            var _loc7 = this.isSelected(_loc3);
            if (!multipleSelection || wasKeySelected)
            {
                this.clearSelected(transition);
            } // end if
            if (!(!multipleSelection && _loc7))
            {
                this.selectItem(_loc3, !_loc7);
                var _loc9 = !_loc7 ? ("selected") : ("normal");
                _loc5.drawRow(_loc5.item, _loc9, transition);
            } // end if
            lastSelected = _loc3;
        } // end else if
        if (allowChangeEvent)
        {
            this.dispatchEvent({type: "change"});
        } // end if
        delete this.wasKeySelected;
    } // End of the function
    function dragScroll(Void)
    {
        clearInterval(dragScrolling);
        if (_ymouse < 0)
        {
            this.setVPosition(__vPosition - 1);
            this.selectRow(0, false);
            var _loc2 = Math.min(-_ymouse - 30, 0);
            scrollInterval = 0.593000 * _loc2 * _loc2 + 1 + minScrollInterval;
            dragScrolling = setInterval(this, "dragScroll", scrollInterval);
            this.dispatchEvent({type: "scroll", direction: "vertical", position: __vPosition});
        }
        else if (_ymouse > __height)
        {
            var _loc3 = __vPosition;
            this.setVPosition(__vPosition + 1);
            if (_loc3 != __vPosition)
            {
                this.selectRow(__rowCount - 1 - roundUp, false);
            } // end if
            _loc2 = Math.min(_ymouse - __height - 30, 0);
            scrollInterval = 0.593000 * _loc2 * _loc2 + 1 + minScrollInterval;
            dragScrolling = setInterval(this, "dragScroll", scrollInterval);
            this.dispatchEvent({type: "scroll", direction: "vertical", position: __vPosition});
        }
        else
        {
            dragScrolling = setInterval(this, "dragScroll", 15);
        } // end else if
        updateAfterEvent();
    } // End of the function
    function __onMouseUp(Void)
    {
        clearInterval(dragScrolling);
        delete this.dragScrolling;
        delete this.dragScrolling;
        delete this.isPressed;
        delete this.onMouseUp;
        if (!selectable)
        {
            return;
        } // end if
        if (changeFlag)
        {
            this.dispatchEvent({type: "change"});
        } // end if
        delete this.changeFlag;
    } // End of the function
    function moveSelBy(incr)
    {
        if (!selectable)
        {
            this.setVPosition(__vPosition + incr);
            return;
        } // end if
        var _loc3 = this.getSelectedIndex();
        if (_loc3 == undefined)
        {
            _loc3 = -1;
        } // end if
        var _loc2 = _loc3 + incr;
        _loc2 = Math.max(0, _loc2);
        _loc2 = Math.min(this.getLength() - 1, _loc2);
        if (_loc2 == _loc3)
        {
            return;
        } // end if
        if (_loc3 < __vPosition || _loc3 >= __vPosition + __rowCount)
        {
            this.setVPosition(_loc3);
        } // end if
        if (_loc2 >= __vPosition + __rowCount - roundUp || _loc2 < __vPosition)
        {
            this.setVPosition(__vPosition + incr);
        } // end if
        wasKeySelected = true;
        this.selectRow(_loc2 - __vPosition, false);
    } // End of the function
    function keyDown(e)
    {
        if (selectable)
        {
            if (this.findInputText())
            {
                return;
            } // end if
        } // end if
        if (e.code == 40)
        {
            this.moveSelBy(1);
        }
        else if (e.code == 38)
        {
            this.moveSelBy(-1);
        }
        else if (e.code == 34)
        {
            if (selectable)
            {
                var _loc3 = this.getSelectedIndex();
                if (_loc3 == undefined)
                {
                    _loc3 = 0;
                } // end if
                this.setVPosition(_loc3);
            } // end if
            this.moveSelBy(__rowCount - 1 - roundUp);
        }
        else if (e.code == 33)
        {
            if (selectable)
            {
                _loc3 = this.getSelectedIndex();
                if (_loc3 == undefined)
                {
                    _loc3 = 0;
                } // end if
                this.setVPosition(_loc3);
            } // end if
            this.moveSelBy(1 - __rowCount + roundUp);
        }
        else if (e.code == 36)
        {
            this.moveSelBy(-__dataProvider.length);
        }
        else if (e.code == 35)
        {
            this.moveSelBy(__dataProvider.length);
        } // end else if
    } // End of the function
    function findInputText(Void)
    {
        var _loc2 = Key.getAscii();
        if (_loc2 >= 33 && _loc2 <= 126)
        {
            this.findString(String.fromCharCode(_loc2));
            return (true);
        } // end if
    } // End of the function
    function findString(str)
    {
        if (__dataProvider.length == 0)
        {
            return;
        } // end if
        var _loc4 = this.getSelectedIndex();
        if (_loc4 == undefined)
        {
            _loc4 = 0;
        } // end if
        var _loc6 = 0;
        for (var _loc3 = _loc4 + 1; _loc3 != _loc4; ++_loc3)
        {
            var _loc2 = __dataProvider.getItemAt(_loc3);
            if (_loc2 instanceof XMLNode)
            {
                _loc2 = _loc2.attributes[__labelField];
            }
            else if (typeof(_loc2) != "string")
            {
                _loc2 = String(_loc2[__labelField]);
            } // end else if
            _loc2 = _loc2.substring(0, str.length);
            if (str == _loc2 || str.toUpperCase() == _loc2.toUpperCase())
            {
                _loc6 = _loc3 - _loc4;
                break;
            } // end if
            if (_loc3 >= this.getLength() - 1)
            {
                _loc3 = -1;
            } // end if
        } // end of for
        if (_loc6 != 0)
        {
            this.moveSelBy(_loc6);
        } // end if
    } // End of the function
    function onRowPress(rowIndex)
    {
        if (!enabled)
        {
            return;
        } // end if
        isPressed = true;
        dragScrolling = setInterval(this, "dragScroll", 15);
        onMouseUp = __onMouseUp;
        if (!selectable)
        {
            return;
        } // end if
        this.selectRow(rowIndex);
    } // End of the function
    function onRowRelease(rowIndex)
    {
    } // End of the function
    function onRowRollOver(rowIndex)
    {
        if (!enabled)
        {
            return;
        } // end if
        var _loc2 = rows[rowIndex].item;
        if (this.getStyle("useRollOver") && _loc2 != undefined)
        {
            rows[rowIndex].drawRow(_loc2, "highlighted", false);
        } // end if
        this.dispatchEvent({type: "itemRollOver", index: rowIndex + __vPosition});
    } // End of the function
    function onRowRollOut(rowIndex)
    {
        if (!enabled)
        {
            return;
        } // end if
        if (this.getStyle("useRollOver"))
        {
            rows[rowIndex].drawRow(rows[rowIndex].item, this.getStateAt(rowIndex + __vPosition), false);
        } // end if
        this.dispatchEvent({type: "itemRollOut", index: rowIndex + __vPosition});
    } // End of the function
    function onRowDragOver(rowIndex)
    {
        if (!enabled || isPressed != true || !selectable)
        {
            return;
        } // end if
        if (dropEnabled)
        {
        }
        else if (dragScrolling)
        {
            this.selectRow(rowIndex, false);
        }
        else
        {
            onMouseUp = __onMouseUp;
            this.onRowPress(rowIndex);
        } // end else if
    } // End of the function
    function onRowDragOut(rowIndex)
    {
        if (!enabled)
        {
            return;
        } // end if
        if (dragEnabled)
        {
        }
        else
        {
            this.onRowRollOut(rowIndex);
        } // end else if
    } // End of the function
    function init(Void)
    {
        super.init();
        tabEnabled = true;
        tabChildren = false;
        if (__dataProvider == undefined)
        {
            __dataProvider = new Array();
            __dataProvider.addEventListener("modelChanged", this);
        } // end if
        baseRowZ = topRowZ = 10;
    } // End of the function
    function createChildren(Void)
    {
        super.createChildren();
        listContent = this.createEmptyMovieClip("content_mc", CONTENTDEPTH);
        invLayoutContent = true;
        this.invalidate();
    } // End of the function
    function draw(Void)
    {
        if (invRowHeight)
        {
            delete this.invRowHeight;
            __rowCount = 0;
            listContent.removeMovieClip();
            listContent = this.createEmptyMovieClip("content_mc", CONTENTDEPTH);
        } // end if
        if (invUpdateControl)
        {
            this.updateControl();
        } // end if
        border_mc.draw();
    } // End of the function
    function invalidateStyle(propName)
    {
        if (isRowStyle[propName])
        {
            invUpdateControl = true;
            this.invalidate();
        }
        else
        {
            for (var _loc3 = 0; _loc3 < __rowCount; ++_loc3)
            {
                rows[_loc3].invalidateStyle(propName);
            } // end of for
        } // end else if
        super.invalidateStyle(propName);
    } // End of the function
    static var mixIt1 = mx.controls.listclasses.DataSelector.Initialize(mx.controls.listclasses.ScrollSelectList);
    static var mixIt2 = mx.controls.listclasses.DataProvider.Initialize(Array);
    var CONTENTDEPTH = 100;
    var __hPosition = 0;
    var __rowRenderer = "SelectableRow";
    var __rowHeight = 22;
    var __rowCount = 0;
    var __labelField = "label";
    var minScrollInterval = 30;
    var dropEnabled = false;
    var dragEnabled = false;
    var className = "ScrollSelectList";
    var isRowStyle = {styleName: true, backgroundColor: true, selectionColor: true, rollOverColor: true, selectionDisabledColor: true, backgroundDisabledColor: true, textColor: true, textSelectedColor: true, textRollOverColor: true, textDisabledColor: true, alternatingRowColors: true, defaultIcon: true};
    var roundUp = 0;
    var selectable = true;
    var multipleSelection = false;
} // End of Class
