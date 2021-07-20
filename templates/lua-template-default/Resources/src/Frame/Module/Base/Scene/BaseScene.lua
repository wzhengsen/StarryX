--[[
Copyright (c) 2021 wzhengsen.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
]]

local Sound = require("Audio.Sound");
---场景基类。
local BaseScene = class(cc.Scene);

BaseScene.static.const.PreloadRes = table.readonly({
    Sound = {},
    Animation = {},
    SpriteFrame = {},
    Texture = {}
});

function BaseScene:ctor()
    self.EnableEvents = true;
    self.EnableDelEvent = true;
end

function BaseScene:Run()
    if class.IsNull(D.RunningScene) then
        D:RunWithScene(self)
    else
        D:ReplaceScene(self)
    end
end

function BaseScene:dtor()
    for _,v in pairs(self.is().PreloadRes.Sound or {}) do
        Sound.Uncache(v)
    end
end

function BaseScene.handlers:AppEnterPortrait()
    local size = self.Size;
    self.Size = {
        height = size.width,
        width = size.height
    };
    self.Layout = true;
end

function BaseScene.handlers:AppEnterLandScape()
    local size = self.Size;
    self.Size = {
        height = size.width,
        width = size.height
    };
    self.Layout = true;
end
cc.BaseScene = BaseScene;
return BaseScene;