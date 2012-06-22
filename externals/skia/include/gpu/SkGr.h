
/*
 * Copyright 2010 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */



#ifndef SkGr_DEFINED
#define SkGr_DEFINED

#include <stddef.h>

// Gr headers
#include "GrTypes.h"
#include "GrContext.h"
#include "GrFontScaler.h"
#include "GrClipIterator.h"

// skia headers
#include "SkBitmap.h"
#include "SkPath.h"
#include "SkPoint.h"
#include "SkRegion.h"
#include "SkShader.h"
#include "SkClipStack.h"

#if (GR_DEBUG && defined(SK_RELEASE)) || (GR_RELEASE && defined(SK_DEBUG))
//    #error "inconsistent GR_DEBUG and SK_DEBUG"
#endif

////////////////////////////////////////////////////////////////////////////////
// Sk to Gr Type conversions

GR_STATIC_ASSERT((int)GrSamplerState::kClamp_WrapMode == (int)SkShader::kClamp_TileMode);
GR_STATIC_ASSERT((int)GrSamplerState::kRepeat_WrapMode ==(
                 int)SkShader::kRepeat_TileMode);
GR_STATIC_ASSERT((int)GrSamplerState::kMirror_WrapMode ==
                 (int)SkShader::kMirror_TileMode);

#define sk_tile_mode_to_grwrap(X) ((GrSamplerState::WrapMode)(X))

GR_STATIC_ASSERT((int)kZero_GrBlendCoeff == (int)SkXfermode::kZero_Coeff);
GR_STATIC_ASSERT((int)kOne_GrBlendCoeff  == (int)SkXfermode::kOne_Coeff);
GR_STATIC_ASSERT((int)kSC_GrBlendCoeff   == (int)SkXfermode::kSC_Coeff);
GR_STATIC_ASSERT((int)kISC_GrBlendCoeff  == (int)SkXfermode::kISC_Coeff);
GR_STATIC_ASSERT((int)kDC_GrBlendCoeff   == (int)SkXfermode::kDC_Coeff);
GR_STATIC_ASSERT((int)kIDC_GrBlendCoeff  == (int)SkXfermode::kIDC_Coeff);
GR_STATIC_ASSERT((int)kSA_GrBlendCoeff   == (int)SkXfermode::kSA_Coeff);
GR_STATIC_ASSERT((int)kISA_GrBlendCoeff  == (int)SkXfermode::kISA_Coeff);
GR_STATIC_ASSERT((int)kDA_GrBlendCoeff   == (int)SkXfermode::kDA_Coeff);
GR_STATIC_ASSERT((int)kIDA_GrBlendCoeff  == (int)SkXfermode::kIDA_Coeff);

#define sk_blend_to_grblend(X) ((GrBlendCoeff)(X))

GR_STATIC_ASSERT((int)SkPath::kMove_Verb  == (int)kMove_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kLine_Verb  == (int)kLine_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kQuad_Verb  == (int)kQuadratic_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kCubic_Verb == (int)kCubic_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kClose_Verb == (int)kClose_PathCmd);
GR_STATIC_ASSERT((int)SkPath::kDone_Verb  == (int)kEnd_PathCmd);

#define sk_path_verb_to_gr_path_command(X) ((GrPathCmd)(X))

///////////////////////////////////////////////////////////////////////////////

#include "SkColorPriv.h"

class SkGr {
public:
    /**
     *  Convert the SkBitmap::Config to the corresponding PixelConfig, or
     *  kUnknown_PixelConfig if the conversion cannot be done.
     */
    static GrPixelConfig BitmapConfig2PixelConfig(SkBitmap::Config);

    static GrColor SkColor2GrColor(SkColor c) {
        SkPMColor pm = SkPreMultiplyColor(c);
        unsigned r = SkGetPackedR32(pm);
        unsigned g = SkGetPackedG32(pm);
        unsigned b = SkGetPackedB32(pm);
        unsigned a = SkGetPackedA32(pm);
        return GrColorPackRGBA(r, g, b, a);
    }
};

////////////////////////////////////////////////////////////////////////////////
// Classes

class SkGrClipIterator : public GrClipIterator {
public:
    SkGrClipIterator() { fClipStack = NULL;  fCurr = NULL; }
    SkGrClipIterator(const SkClipStack& clipStack) { this->reset(clipStack); }

    void reset(const SkClipStack& clipStack);

    // overrides
    virtual bool isDone() const SK_OVERRIDE { return NULL == fCurr; }
    virtual void next() SK_OVERRIDE { fCurr = fIter.next(); }
    virtual void rewind() SK_OVERRIDE { this->reset(*fClipStack); }
    virtual GrClipType getType() const SK_OVERRIDE;

    virtual SkRegion::Op getOp() const SK_OVERRIDE;

    virtual bool getDoAA() const SK_OVERRIDE;

    virtual void getRect(GrRect* rect) const SK_OVERRIDE {
        if (!fCurr->fRect) {
            rect->setEmpty();
        } else {
            *rect = *fCurr->fRect;
        }
    }

    virtual const SkPath* getPath() SK_OVERRIDE {
        return fCurr->fPath;
    }

    virtual GrPathFill getPathFill() const SK_OVERRIDE;

private:
    const SkClipStack*                  fClipStack;
    SkClipStack::B2FIter                fIter;
    // SkClipStack's auto advances on each get
    // so we store the current pos here.
    const SkClipStack::B2FIter::Clip*   fCurr;
};

class SkGlyphCache;

class SkGrFontScaler : public GrFontScaler {
public:
    explicit SkGrFontScaler(SkGlyphCache* strike);
    virtual ~SkGrFontScaler();

    // overrides
    virtual const GrKey* getKey();
    virtual GrMaskFormat getMaskFormat();
    virtual bool getPackedGlyphBounds(GrGlyph::PackedID, GrIRect* bounds);
    virtual bool getPackedGlyphImage(GrGlyph::PackedID, int width, int height,
                                     int rowBytes, void* image);
    virtual bool getGlyphPath(uint16_t glyphID, SkPath*);

private:
    SkGlyphCache* fStrike;
    GrKey*  fKey;
//    DECLARE_INSTANCE_COUNTER(SkGrFontScaler);
};

////////////////////////////////////////////////////////////////////////////////
// Helper functions

GrContext::TextureCacheEntry sk_gr_create_bitmap_texture(GrContext* ctx,
                                                uint64_t key,
                                                const GrSamplerState* sampler,
                                                const SkBitmap& bitmap);


#endif
