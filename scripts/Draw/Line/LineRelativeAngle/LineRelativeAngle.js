/**
 * Copyright (c) 2011-2013 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("../Line.js");

/**
 * \class LineRelativeAngle
 * \brief Line with relative angle to existing line, position and length.
 * \ingroup ecma_draw_line
 */
function LineRelativeAngle(guiAction) {
    Line.call(this, guiAction);

    this.entity = undefined;
    this.shape = undefined;
    this.pos = undefined;
    this.angle = Math.PI/2.0;
    this.length = 100.0;

    if (!isNull(guiAction)) {
        this.setUiOptions("LineRelativeAngle.ui");
    }
}

LineRelativeAngle.prototype = new Line();

LineRelativeAngle.State = {
    ChoosingEntity : 0,
    SettingPos : 1
};

LineRelativeAngle.prototype.beginEvent = function() {
    Line.prototype.beginEvent.call(this);

    this.setState(LineRelativeAngle.State.ChoosingEntity);
};

LineRelativeAngle.prototype.setState = function(state) {
    Line.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case LineRelativeAngle.State.ChoosingEntity:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.setLeftMouseTip(qsTr("Choose base entity"));
        this.setRightMouseTip(EAction.trCancel);
        this.entity = undefined;
        this.shape = undefined;
        this.pos = undefined;
        EAction.showLineTools();
        break;
    case LineRelativeAngle.State.SettingPos:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        this.setLeftMouseTip(qsTr("Set position"));
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;
    }

};

LineRelativeAngle.prototype.escapeEvent = function() {
    switch (this.state) {
    case LineRelativeAngle.State.ChoosingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;
    case LineRelativeAngle.State.SettingPos:
        this.setState(LineRelativeAngle.State.ChoosingEntity);
        break;
    }
};

LineRelativeAngle.prototype.pickEntity = function(event, preview) {
    var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = event.getEntityId();
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    var shape = entity.getClosestShape(pos);

    //if (preview) {
    //    di.highlightEntity(entityId);
    //}

    switch (this.state) {
    case LineRelativeAngle.State.ChoosingEntity:
        if (isArcShape(shape) ||
            isCircleShape(shape) ||
            isLineShape(shape)) {

            this.entity = entity;
            this.shape = shape;
            if (preview) {
                this.updatePreview();
            }
            else {
                this.setState(LineRelativeAngle.State.SettingPos);
            }
        }
        else {
            if (!preview) {
                EAction.warnNotLineArcCircle();
            }
            this.entity = undefined;
            this.shape = undefined;
        }

        break;
    }
};

LineRelativeAngle.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case LineRelativeAngle.State.SettingPos:
        this.pos = event.getModelPosition();

        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
            }
        }
        break;
    }
};

LineRelativeAngle.prototype.getHighlightedEntities = function() {
    var ret = new Array();
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

LineRelativeAngle.prototype.getOperation = function(preview) {
    if (isNull(this.pos) || isNull(this.entity)) {
        return undefined;
    }

    var doc = this.getDocument();

    var line = this.getLine();

    if (isNull(line)) {
        return undefined;
    }

    var op = new RAddObjectsOperation();
    op.addObject(new RLineEntity(doc, new RLineData(line)));
    return op;
};

LineRelativeAngle.prototype.getLine = function() {
    var doc = this.getDocument();

    // check given entity / coord:
    if (isNull(this.shape) || isNull(this.pos)) {
        return undefined;
    }

    var v1 = RVector.createPolar(this.length/2.0, this.getAbsoluteAngle());

    return new RLine(this.pos.operator_subtract(v1), this.pos.operator_add(v1));
};

LineRelativeAngle.prototype.getAbsoluteAngle = function() {
    var ret;

    if (isLineShape(this.shape)) {
        ret = this.shape.getAngle();
    }
    else if (isArcShape(this.shape) || isCircleShape(this.shape)) {
        ret = this.shape.getCenter().getAngleTo(this.pos) + Math.PI/2.0;
    }

    ret += this.angle;

    return ret;
};

LineRelativeAngle.prototype.slotAngleChanged = function(value) {
    this.angle = value;
    this.updatePreview(true);
};

LineRelativeAngle.prototype.slotLengthChanged  = function(value) {
    this.length = value;
    this.updatePreview(true);
};

