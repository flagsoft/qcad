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

#ifndef RTEXTRENDERER_H
#define RTEXTRENDERER_H

#include "entity_global.h"

#include <QTextLayout>

#include "RDocument.h"
#include "REntityData.h"
#include "RPainterPath.h"
#include "RPainterPathSource.h"
#include "RTextData.h"
#include "RVector.h"

class QTextDocument;

/**
 * Renders formatted text into painter paths.
 *
 * \scriptable
 * \ingroup entity
 */
class QCADENTITY_EXPORT RTextRenderer {
public:
    enum Target {
        PainterPaths = 0x01,
        RichText = 0x02
    };

public:
    RTextRenderer(const RTextData& textData, bool draft, RTextRenderer::Target target, double fontHeightFactor = 1.0);

    void renderSimple();
    void render();

    QList<RPainterPath> getPainterPaths() const {
        return painterPaths;
    }

    RBox getBoundingBox() const {
        return boundingBox;
    }

    double getHeight() const {
        return height;
    }

    double getWidth() const {
        return width;
    }

    QString getRichText() const {
        return richText;
    }

private:
    QList<RPainterPath> getPainterPathsForBlock(
        const QString& blockText,
        const QList<QTextLayout::FormatRange>& formats,
        double& horizontalAdvance,
        double& horizontalAdvanceNoSpacing,
        double& ascent,
        double& descent);

    QList<RPainterPath> getPainterPathsForBlockTtf(
        const QString& blockText,
        const QList<QTextLayout::FormatRange>& formats,
        double& horizontalAdvance,
        double& horizontalAdvanceNoSpacing,
        double& ascent,
        double& descent);

    QList<RPainterPath> getPainterPathsForBlockCad(
        const QString& blockText,
        const QList<QTextLayout::FormatRange>& formats,
        double& horizontalAdvance,
        double& horizontalAdvanceNoSpacing,
        double& ascent,
        double& descent);

    QRectF getCharacterRect(const QString& fontName, const QChar& ch) const;
    QRectF getCharacterRect(const QFont& font, const QChar& ch) const;

    QString getRichTextForBlock(const QString& blockText,
                                const QList<QTextLayout::FormatRange>& formats);

public:
    static QString rxLineFeed;
    static QString rxParagraphFeed;
    static QString rxHeightChange;
    //static QString rxRelativeHeightChange;
    static QString rxStackedText;
    static QString rxColorChangeIndex;
    static QString rxColorChangeCustom;
    static QString rxNonBreakingSpace;
    static QString rxOverlineOn;
    static QString rxOverlineOff;
    static QString rxUnderlineOn;
    static QString rxUnderlineOff;
    static QString rxWidthChange;
    static QString rxObliqueAngleChange;
    static QString rxTrackChange;
    static QString rxAlignmentChange;
    static QString rxFontChangeCad;
    static QString rxFontChangeTtf;
    static QString rxBeginBlock;
    static QString rxEndBlock;
    static QString rxBackslash;
    static QString rxCurlyOpen;
    static QString rxCurlyClose;
    static QString rxDegree;
    static QString escDegree;
    static QString rxPlusMinus;
    static QString escPlusMinus;
    static QString rxDiameter;
    static QString escDiameter;
    static QString rxUnicode;

    static QString rxAll;

    static QChar chDegree;
    static QChar chPlusMinus;
    static QChar chDiameter;

private:
    RTextData textData;

    Target target;
    QList<RPainterPath> painterPaths;
    RBox boundingBox;
    double height;
    double width;
    bool draft;
    QString richText;
    double fontHeightFactor;

    QStack<bool> useCadFont;
    QStack<QTextCharFormat> currentFormat;
    QStack<double> blockHeight;
    QStack<QString> blockFont;
    QStack<bool> blockBold;
    QStack<bool> blockItalic;
    QStack<QStringList> openTags;
};

Q_DECLARE_METATYPE(RTextRenderer*)
Q_DECLARE_METATYPE(RTextRenderer::Target)
Q_DECLARE_METATYPE(RTextRenderer::Target*)

#endif
