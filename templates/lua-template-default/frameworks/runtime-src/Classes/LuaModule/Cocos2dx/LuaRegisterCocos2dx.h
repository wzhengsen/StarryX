#pragma once
#include "lua.hpp"
/*
	cc::network::Downloader����һ��lua�󶨣�cocosԭ���İ���lua�������չ���
	�������𲻿�Ԥ�ϵ��ڴ����
	�µ�lua����������˰󶨺�������������û�м̳�cc::Ref�������ֶ�����
*/
void LuaRegisterDownloader(lua_State* L) noexcept;