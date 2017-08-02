class mx.controls.RadioButton extends mx.controls.Button
{
    var setToggle, __value, selected, releaseFocus, phase, dispatchEvent, _parent, __data, __get__data, setState, __get__groupName, __state, getFocusManager, __get__toggle, __get__icon, __set__data, __get__emphasized, __set__groupName, __set__icon, __set__toggle;
    function RadioButton()
    {
        super();
    } // End of the function
    function init(Void)
    {
        this.setToggle(__toggle);
        __value = this;
        super.init();
    } // End of the function
    function size(Void)
    {
        super.size();
    } // End of the function
    function onRelease()
    {
        if (selected)
        {
            return;
        } // end if
        this.releaseFocus();
        phase = "up";
        this.setSelected(true);
        this.dispatchEvent({type: "click"});
        _parent[__groupName].dispatchEvent({type: "click"});
    } // End of the function
    function setData(val)
    {
        __data = val;
    } // End of the function
    function set data(val)
    {
        __data = val;
        //return (this.data());
        null;
    } // End of the function
    function getData(val)
    {
        return (__data);
    } // End of the function
    function get data()
    {
        return (__data);
    } // End of the function
    function onUnload()
    {
        if (_parent[__groupName].selectedRadio == this)
        {
            _parent[__groupName].selectedRadio = undefined;
        } // end if
        _parent[__groupName].radioList[indexNumber] = null;
        delete _parent[__groupName].radioList[indexNumber];
    } // End of the function
    function setSelected(val)
    {
        var _loc2 = _parent[__groupName];
        var _loc5 = _loc2.selectedRadio.__width;
        var _loc4 = _loc2.selectedRadio.__height;
        if (val)
        {
            _loc2.selectedRadio.setState(false);
            _loc2.selectedRadio = this;
        }
        else if (_loc2.selectedRadio == this)
        {
            _loc2.selectedRadio.setState(false);
            _loc2.selectedRadio = undefined;
        } // end else if
        this.setState(val);
    } // End of the function
    function deleteGroupObj(groupName)
    {
        delete _parent[groupName];
    } // End of the function
    function getGroupName()
    {
        return (__groupName);
    } // End of the function
    function get groupName()
    {
        return (__groupName);
    } // End of the function
    function setGroupName(groupName)
    {
        if (groupName == undefined || groupName == "")
        {
            return;
        } // end if
        delete _parent[__groupName].radioList[__data];
        this.addToGroup(groupName);
        __groupName = groupName;
    } // End of the function
    function set groupName(groupName)
    {
        this.setGroupName(groupName);
        //return (this.groupName());
        null;
    } // End of the function
    function addToGroup(groupName)
    {
        if (groupName == "" || groupName == undefined)
        {
            return;
        } // end if
        var _loc2 = _parent[groupName];
        if (_loc2 == undefined)
        {
            _loc2 = _parent[groupName] = new mx.controls.RadioButtonGroup();
            _loc2.__groupName = groupName;
        } // end if
        _loc2.addInstance(this);
        if (__state)
        {
            _loc2.selectedRadio.setState(false);
            _loc2.selectedRadio = this;
        } // end if
    } // End of the function
    function get emphasized()
    {
        return;
    } // End of the function
    function keyDown(e)
    {
        switch (e.code)
        {
            case 40:
            {
                this.setNext();
                break;
            } 
            case 38:
            {
                this.setPrev();
                break;
            } 
            case 37:
            {
                this.setPrev();
                break;
            } 
            case 39:
            {
                this.setNext();
                break;
            } 
        } // End of switch
    } // End of the function
    function setNext()
    {
        var _loc2 = _parent[this.__get__groupName()];
        if (_loc2.selectedRadio.indexNumber + 1 == _loc2.radioList.length)
        {
            return;
        } // end if
        var _loc4 = _loc2.selectedRadio ? (_loc2.selectedRadio.indexNumber) : (-1);
        for (var _loc3 = 1; _loc3 < _loc2.radioList.length; ++_loc3)
        {
            if (_loc2.radioList[_loc4 + _loc3] != undefined && _loc2.radioList[_loc4 + _loc3].enabled)
            {
                var _loc5 = this.getFocusManager();
                _loc2.radioList[_loc4 + _loc3].selected = true;
                _loc5.setFocus(_loc2.radioList[_loc2.selectedRadio.indexNumber]);
                _loc2.dispatchEvent({type: "click"});
                break;
            } // end if
        } // end of for
    } // End of the function
    function setPrev()
    {
        var _loc2 = _parent[this.__get__groupName()];
        if (_loc2.selectedRadio.indexNumber == 0)
        {
            return;
        } // end if
        var _loc4 = _loc2.selectedRadio ? (_loc2.selectedRadio.indexNumber) : (1);
        for (var _loc3 = 1; _loc3 < _loc2.radioList.length; ++_loc3)
        {
            if (_loc2.radioList[_loc4 - _loc3] != undefined && _loc2.radioList[_loc4 - _loc3].enabled)
            {
                var _loc5 = this.getFocusManager();
                _loc2.radioList[_loc4 - _loc3].selected = true;
                _loc5.setFocus(_loc2.radioList[_loc2.selectedRadio.indexNumber]);
                _loc2.dispatchEvent({type: "click"});
                break;
            } // end if
        } // end of for
    } // End of the function
    function set toggle(v)
    {
        //return (this.toggle());
        null;
    } // End of the function
    function get toggle()
    {
    } // End of the function
    function set icon(v)
    {
        //return (this.icon());
        null;
    } // End of the function
    function get icon()
    {
    } // End of the function
    static var symbolName = "RadioButton";
    static var symbolOwner = mx.controls.RadioButton;
    static var version = "2.0.2.127";
    var className = "RadioButton";
    var btnOffset = 0;
    var __toggle = true;
    var __label = "Radio Button";
    var __labelPlacement = "right";
    var ignoreClassStyleDeclaration = {Button: 1};
    var __groupName = "radioGroup";
    var indexNumber = 0;
    var offset = false;
    var falseUpSkin = "";
    var falseDownSkin = "";
    var falseOverSkin = "";
    var falseDisabledSkin = "";
    var trueUpSkin = "";
    var trueDownSkin = "";
    var trueOverSkin = "";
    var trueDisabledSkin = "";
    var falseUpIcon = "RadioFalseUp";
    var falseDownIcon = "RadioFalseDown";
    var falseOverIcon = "RadioFalseOver";
    var falseDisabledIcon = "RadioFalseDisabled";
    var trueUpIcon = "RadioTrueUp";
    var trueDownIcon = "";
    var trueOverIcon = "";
    var trueDisabledIcon = "RadioTrueDisabled";
    var centerContent = false;
    var borderW = 0;
    var clipParameters = {labelPlacement: 1, data: 1, label: 1, groupName: 1, selected: 1};
    static var mergedClipParameters = mx.core.UIObject.mergeClipParameters(mx.controls.RadioButton.prototype.clipParameters, mx.controls.Button.prototype.clipParameters);
} // End of Class
