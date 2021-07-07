/*
* Copyright (c) 2021 @aismann; Peter Eismann, Germany; dreifrankensoft
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __PHYSICSNODES_DEBUGNODE_BOX2D_H__
#define __PHYSICSNODES_DEBUGNODE_BOX2D_H__

#include "box2d/box2d.h"
#include "cocos2d.h"

struct b2AABB;

extern cocos2d::DrawNode* drawBox2D;

// This class implements debug drawing callbacks that are invoked
// inside b2World::Step.
class GLESDebugDraw : public b2Draw
{
    float mRatio;
 //   cocos2d::g* mShaderProgram;
    GLint        mColorLocation;

    cocos2d::DrawNode* drawBP = NULL;

    void initShader( void );
public:
    GLESDebugDraw();

    GLESDebugDraw(float ratio );

    virtual void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);

    virtual void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);

    virtual void DrawCircle(const b2Vec2& center, float radius, const b2Color& color);

    virtual void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color);

    virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

    virtual void DrawTransform(const b2Transform& xf);

    virtual void DrawPoint(const b2Vec2& p, float size, const b2Color& color);

    virtual void DrawString(int x, int y, const char* string, ...); 

    virtual void DrawAABB(b2AABB* aabb, const b2Color& color);
};


#endif
