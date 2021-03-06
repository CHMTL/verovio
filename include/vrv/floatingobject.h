/////////////////////////////////////////////////////////////////////////////
// Name:        floatingobject.h
// Author:      Laurent Pugin
// Created:     2015
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_FLOATING_OBJECT_H__
#define __VRV_FLOATING_OBJECT_H__

#include "devicecontextbase.h"
#include "object.h"

namespace vrv {

class Alignment;
class FloatingPositioner;
class StaffAlignment;

//----------------------------------------------------------------------------
// FloatingObject
//----------------------------------------------------------------------------

/**
 * This class represents elements appearing within a measure.
 * It is not an abstract class but should not be instanciated directly.
 */
class FloatingObject : public Object {
public:
    /**
     * @name Constructors, destructors, reset methods
     * Reset method resets all attribute classes
     */
    ///@{
    FloatingObject();
    FloatingObject(std::string classid);
    virtual ~FloatingObject();
    virtual void Reset();
    virtual ClassId GetClassId() const { return FLOATING_OBJECT; }
    ///@}

    virtual void UpdateContentBBoxX(int x1, int x2);
    virtual void UpdateContentBBoxY(int y1, int y2);
    virtual void UpdateSelfBBoxX(int x1, int x2);
    virtual void UpdateSelfBBoxY(int y1, int y2);

    /**
     * @name Get and set the X and Y drawing position
     */
    ///@{
    virtual int GetDrawingX() const;
    virtual int GetDrawingY() const;
    ///@}

    void SetCurrentFloatingPositioner(FloatingPositioner *boundingBox);
    FloatingPositioner *GetCurrentFloatingPositioner() const { return m_currentPositioner; }

    /**
     * @name Get and set the drawing group id for linking floating element horizontally
     */
    ///@{
    int GetDrawingGrpId() const { return m_drawingGrpId; }
    void SetDrawingGrpId(int drawingGrpId) { m_drawingGrpId = drawingGrpId; }
    ///@}

    //----------//
    // Functors //
    //----------//

    /**
     * See Object::ResetHorizontalAlignment
     */
    virtual int ResetHorizontalAlignment(FunctorParams *functorParams);

    /**
     * See Object::ResetVerticalAlignment
     */
    virtual int ResetVerticalAlignment(FunctorParams *functorParams);

    /**
     * See Object::FillStaffCurrentTimeSpanning
     */
    virtual int FillStaffCurrentTimeSpanning(FunctorParams *functorParams);

    /**
     * See Object::PrepareTimePointing
     */
    virtual int PrepareTimePointing(FunctorParams *functorParams);

    /**
     * See Object::PrepareTimeSpanning
     */
    virtual int PrepareTimeSpanning(FunctorParams *functorParams);

    /**
     * See Object::PrepareTimestamps
     */
    virtual int PrepareTimestamps(FunctorParams *functorParams);

    /**
     * See Object::ResetDrawing
     */
    virtual int ResetDrawing(FunctorParams *functorParams);

    /**
     * See Object::UnCastOff
     */
    virtual int UnCastOff(FunctorParams *functorParams);

private:
    //
public:
    //
private:
    FloatingPositioner *m_currentPositioner;

    /* Drawing Id to group floating elements horizontally */
    int m_drawingGrpId;
};

//----------------------------------------------------------------------------
// FloatingPositioner
//----------------------------------------------------------------------------

/**
 * This class represents a basic object in the layout domain
 */
class FloatingPositioner : public BoundingBox {
public:
    // constructors and destructors
    FloatingPositioner(FloatingObject *object);
    virtual ~FloatingPositioner(){};
    virtual ClassId GetClassId() const { return FLOATING_POSITIONER; }

    virtual void ResetPositioner();

    /**
     * @name Get the X and Y drawing position
     */
    ///@{
    virtual int GetDrawingX() const;
    virtual int GetDrawingY() const;
    ///@}

    virtual void ResetCachedDrawingX() const;
    virtual void ResetCachedDrawingY() const;

    void SetObjectXY(Object *objectX, Object *objectY);

    FloatingObject *GetObject() const { return m_object; }

    bool CalcDrawingYRel(Doc *doc, StaffAlignment *staffAlignment, BoundingBox *horizOverlapingBBox);

    data_STAFFREL_basic GetDrawingPlace() const { return m_place; }

    void UpdateCurvePosition(const Point points[4], float angle, int thickness, curvature_CURVEDIR curveDir);

    int CalcXMinMaxY(const Point points[4]);

    /**
     * @name Get and set the X and Y drawing relative position.
     * (X is currently used only for Arpeg)
     */
    ///@{
    int GetDrawingYRel() const { return m_drawingYRel; }
    virtual void SetDrawingYRel(int drawingYRel);
    int GetDrawingXRel() const { return m_drawingXRel; }
    virtual void SetDrawingXRel(int drawingXRel);
    ///@}

private:
    Object *m_objectX;
    Object *m_objectY;

protected:
    /**
     * The X drawing relative position of the object.
     * Arpeg are positionned according to the top note through the FloatingPositioner
     * (See View::DrawArpeg that sets the FloatingPositioner)
     */
    int m_drawingXRel;
    /**
     * The Y drawing relative position of the object.
     * It is re-computed everytime the object is drawn and it is not stored in the file.
     */
    int m_drawingYRel;

    FloatingObject *m_object;

    data_STAFFREL_basic m_place;

public:
    Point m_cuvrePoints[4];
    float m_cuvreAngle;
    int m_cuvreThickness;
    curvature_CURVEDIR m_cuvreDir;
    int m_cuvreXMinMaxY;
};

} // namespace vrv

#endif
