class mx.controls.CheckBox extends mx.controls.Button
{
    var _getTextFormat, labelPath, iconName, __get__toggle, __get__icon, __get__emphasized, __set__icon, __set__toggle;
    function CheckBox()
    {
        super();
    } // End of the function
    function onRelease()
    {
        super.onRelease();
    } // End of the function
    function init()
    {
        super.init();
    } // End of the function
    function size()
    {
        super.size();
    } // End of the function
    function get emphasized()
    {
        return;
    } // End of the function
    function calcPreferredHeight()
    {
        var _loc5 = this._getTextFormat();
        var _loc3 = _loc5.getTextExtent2(labelPath.text).height;
        var _loc4 = iconName._height;
        var _loc2 = 0;
        if (__labelPlacement == "left" || __labelPlacement == "right")
        {
            _loc2 = Math.max(_loc3, _loc4);
        }
        else
        {
            _loc2 = _loc3 + _loc4;
        } // end else if
        return (Math.max(14, _loc2));
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
    static var symbolName = "CheckBox";
    static var symbolOwner = mx.controls.CheckBox;
    static var version = "2.0.2.127";
    var className = "CheckBox";
    var ignoreClassStyleDeclaration = {Button: 1};
    var btnOffset = 0;
    var __toggle = true;
    var __selected = false;
    var __labelPlacement = "right";
    var __label = "CheckBox";
    var falseUpSkin = "";
    var falseDownSkin = "";
    var falseOverSkin = "";
    var falseDisabledSkin = "";
    var trueUpSkin = "";
    var trueDownSkin = "";
    var trueOverSkin = "";
    var trueDisabledSkin = "";
    var falseUpIcon = "CheckFalseUp";
    var falseDownIcon = "CheckFalseDown";
    var falseOverIcon = "CheckFalseOver";
    var falseDisabledIcon = "CheckFalseDisabled";
    var trueUpIcon = "CheckTrueUp";
    var trueDownIcon = "CheckTrueDown";
    var trueOverIcon = "CheckTrueOver";
    var trueDisabledIcon = "CheckTrueDisabled";
    var clipParameters = {label: 1, labelPlacement: 1, selected: 1};
    static var mergedClipParameters = mx.core.UIObject.mergeClipParameters(mx.controls.CheckBox.prototype.clipParameters, mx.controls.Button.prototype.clipParameters);
    var centerContent = false;
    var borderW = 0;
} // End of Class
