#pragma once
#include "lua.hpp"
/*
    һЩ��OO_Lua��չ��Cocos2dx��lua������
*/
void LuaRegisterCocos2dx(lua_State* L) noexcept;
/*
	cc::network::Downloader����һ��lua�󶨣�cocosԭ���İ���lua�������չ���
	�������𲻿�Ԥ�ϵ��ڴ����
	�µ�lua����������˰󶨺�������������û�м̳�cc::Ref�������ֶ�����
*/
void LuaRegisterDownloader(lua_State* L) noexcept;