/*
 * Software written by Jared Bruni https://github.com/lostjared
 
 This software is dedicated to all the people that experience mental illness.
 
 Website: http://lostsidedead.com
 YouTube: http://youtube.com/LostSideDead
 Instagram: http://instagram.com/lostsidedead
 Twitter: http://twitter.com/jaredbruni
 Facebook: http://facebook.com/LostSideDead0x
 
 You can use this program free of charge and redistrubute it online as long
 as you do not charge anything for this program. This program is meant to be
 100% free.
 
 BSD 2-Clause License
 
 Copyright (c) 2019, Jared Bruni
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 */

#include"ac.h"
#include<cctype>
#include<cstdlib>

namespace ac {
    
   	std::unordered_map<std::string, FilterItem> filter_menu_map;
    std::vector<std::string> svAll;
    std::vector<std::string> svAllSorted;
    std::vector<std::string> svUser;
    std::vector<std::string> solo_filter;
    std::vector<std::string> color_filter;

    void add_filter(std::vector<std::string> *menu_list, std::string menu_name) {
        filter_menu_map[menu_name].menu_name = menu_name;
        filter_menu_map[menu_name].menu_list = menu_list;
    }
    
    void init_filter_menu_map() {
        for(int i = 0; i < draw_max-5; ++i) {
            svAll.push_back(ac::draw_strings[i]);
            svAllSorted.push_back(ac::draw_strings[i]);
        }
        std::sort(svAllSorted.begin(), svAllSorted.end());
        add_filter(&svAll, "All Filters");
        add_filter(&svAllSorted, "All Filters Sorted");
        add_filter(&vzBlend, "Blend");
        add_filter(&svDistort, "Distort");
        add_filter(&svPattern, "Pattern");
        add_filter(&svGradient, "Gradient");
        add_filter(&svMirror, "Mirror");
        add_filter(&svStrobe, "Strobe");
        add_filter(&svBlur, "Blur");
        add_filter(&svImage, "Image");
        add_filter(&svSquare, "Square");
        add_filter(&svOther_Custom, "Other");
        add_filter(&vSub, "SubFilter");
        add_filter(&svCustom_Spec, "Special");
        add_filter(&svUser, "User");
        auto lwr = [](std::string &s) {
            for(unsigned int i = 0; i < s.size(); ++i) {
                s[i] = tolower(s[i]);
            }
        };
        for(unsigned int i = 0; i < svAll.size(); ++i) {
            std::string value = svAll[i];
            lwr(value);
            
            if(value.find("subfilter") == std::string::npos && value.find("image") == std::string::npos && value.find("fractal") == std::string::npos && value.find("random") == std::string::npos && value.find("1080") == std::string::npos && value.find("720") == std::string::npos && value.find("custom") == std::string::npos && value.find("plugin") == std::string::npos && value.find("shuffle") == std::string::npos && value.find("late") == std::string::npos && value.find("gradient") == std::string::npos && value.find("vertical") == std::string::npos && value.find("color") != std::string::npos)
                color_filter.push_back(svAll[i]);
            
            if(value.find("subfilter") == std::string::npos && value.find("image") == std::string::npos && value.find("random") == std::string::npos && value.find("fractal") == std::string::npos && value.find("feedback") == std::string::npos && value.find("1080p") == std::string::npos && value.find("720p") == std::string::npos && value.find("custom") == std::string::npos && value.find("plugin") == std::string::npos && value.find("1080") == std::string::npos && value.find("720") == std::string::npos) {
                solo_filter.push_back(svAll[i]);
            }
        }
    }
    
    const char *szCustom[] = {"Quality480", "Quality720", "Quality1080","Grayscale", "Negate","DarkNegate","DarkenFilter","FlipY_Axis", "FlipX_Axis", "FlipBoth", "Reverse","ReverseFrameBlend", "No Filter", "Blend with Source","BlendWithSource25", "BlendWithSource50", "BlendWithSource75", "BlendWithSource100","BlendWithImage","BlendWithImage25", "BlendWithImage50", "BlendWithImage75","AlphaBlendImageWithOrigSource", "BlendFor360","XorWithSource","AlphaBlendWithSource",  "GammaDarken5", "GammaDarken10","RestoreBlack","ReduceBy50","AlphaBlendWithSourceScale", "Plugin", "Custom",0};
    
    const char *szCustom_Spec[] = {"Quality480", "Quality720", "Quality1080","Grayscale", "Negate","DarkNegate", "DarkenFilter","FlipY_Axis", "FlipX_Axis", "FlipBoth","Reverse","ReverseFrameBlend", "No Filter", "Blend with Source","BlendWithSource25", "BlendWithSource50", "BlendWithSource75", "BlendWithSource100","BlendWithImage","BlendWithImage25", "BlendWithImage50", "BlendWithImage75","AlphaBlendImageWithOrigSource", "BlendFor360", "XorWithSource", "AlphaBlendWithSource", "GammaDarken5", "GammaDarken10","RestoreBlack","ReduceBy50","AlphaBlendWithSourceScale","Plugin",0};
    
    std::vector<std::string> svCustom_Spec {"Quality480", "Quality720", "Quality1080","Grayscale", "Negate","DarkNegate", "DarkenFilter","FlipY_Axis", "FlipX_Axis", "FlipBoth","Reverse","ReverseFrameBlend", "No Filter", "Blend with Source","BlendWithSource25", "BlendWithSource50", "BlendWithSource75", "BlendWithSource100", "BlendWithImage","BlendWithImage25", "BlendWithImage50", "BlendWithImage75","AlphaBlendImageWithOrigSource","BlendFor360", "XorWithSource", "AlphaBlendWithSource", "DarkNegate", "GammaDarken5", "GammaDarken10","RestoreBlack", "ReduceBy50", "AlphaBlendWithSourceScale"};
    
    std::vector<std::string> vzBlend { "Self AlphaBlend", "Self Scale", "Blend #3", "Negative Paradox",  "ThoughtMode", "RandTriBlend", "Filter3","Rainbow Blend","Rand Blend","Pixel Scale","Pulse", "Combine Pixels", "Blend_Angle", "XorMultiBlend", "UpDown","LeftRight", "BlendedScanLines","XorSine", "FrameBlend", "FrameBlendRGB", "PrevFrameBlend", "HorizontalBlend", "VerticalBlend", "OppositeBlend", "DiagonalLines", "HorizontalLines", "BlendSwitch", "IncreaseBlendHorizontal", "BlendIncrease", "ColorRange", "VectorIncrease", "BlendThree", "HorizontalStripes", "Dual_SelfAlphaRainbow", "Dual_SelfAlphaBlur", "SurroundPixelXor", "WeakBlend", "AverageVertical", "RandomAlphaBlend", "RandomTwoFilterAlphaBlend", "AlphaBlendPosition", "BlendRowAlpha", "BlendRow", "BlendRowByVar", "BlendRowByDirection", "BlendAlphaXor", "SelfXorScale", "SelfAlphaRGB", "XorSelfAlphaImage", "AlphaBlendRandom", "ChannelSortAlphaBlend", "RandomXor", "RandomXorFlash", "SoftXor", "SelfXorBlend", "SelfXorDoubleFlash", "SelfOrDoubleFlash", "BlendRowCurvedSqrt", "CycleShiftRandomAlphaBlend", "TanAlphaGrid", "BlendInAndOut", "BlendScaleInAndOut", "AcidGlitch", "LiquidFilter", "MatrixXorAnd", "XorAlpha", "SelfXorAverage", "RandomXorBlend", "RGBVerticalXor", "RGBVerticalXorScale", "RGBHorizontalXor", "RGBHorizontalXorScale", "FadeInAndOut", "InitBlend", "LagBlend", "SubFilter", "AddFilter", "AlphaBlendSubFilter", "SmoothSubFilterAlphaBlend", "IntertwineSubFilter", "RandBlend", "EveryOther", "EveryOtherSubFilter", "SmoothSubFilter", "EnergizeSubFilter", "SmoothSubFilter16", "EnergizeSubFilter16", "EnergizeSubFilter32", "SmoothSubFilter32", "HalfAddSubFilter", "HalfXorSubFilter", "StaticXorBlend", "XorScale", "ChannelMedianSubFilter", "Bitwise_XOR_Blend", "Bitwise_OR_Blend", "Bitwise_AND_Blend", "PixelReverseXor", "SilverBlend", "PixelXorBlend", "SelfAlphaScale", "SelfScaleAlpha", "RainbowXorBlend", "FadeBlend", "SelfAlphaScaleBlend", "FadeBars", "ShadeRGB", "InterRGB_SubFilter", "InterSmoothSubFilter", "InterRGB_Bars_XY", "InterRGB_Bars_X", "InterRGB_Bars_Y", "StoredFramesAlphaBlend_SubFilter", "BlendSubFilter", "BlendAlphaSubFilter", "ReverseFrameBlend", "ReverseFrameBlendSwitch", "Blend_AlphaSubFilter","RandomBlendFilter","DoubleRandomBlendFilter", "FlipBlendW", "FlipBlendH", "FlipBlendWH", "FlipBlendAll", "FrameMedianBlendSubFilter", "SelfScaleXorIncrease", "Blend_RedGreenBlue", "Blend_RedReenBlue_Dark", "DarkModBlend", "IncDifference", "IncDifferenceAlpha", "MirrorMedianBlend", "SubFilterMedianBlend", "DarkenBlend", "DarkCollectionSubFilter", "DarkSmooth_Filter", "DarkSelfAlpha", "FlipMedian", "FlipMedianSubFilter", "Bars", "BlendBurred", "BlendCombinedValues", "BlendCombinedValueSubFilter", "BlendSubFilterAlpha", "PurpleRain", "CopyXorAlpha", "AveragePixelsXor", "AveragePixelAlpha", "NegativeByRow", "AveragePixelCollection", "IncorrectLine", "XorShift", "RGBSep1x", "RandomIncrease", "BGRBlend", "RGBBlend", "IncreaseDecreaseGamma", "GammaIncDecIncrease", "SelfScaleSortBlend", "FlipAlphaBlend", "RandomFlipFilter", "FlipMatrixCollection", "SelfScaleByFrame", "SmoothCollectionAlphaBlend", "ShuffleAlphaWithRGB", "ShuffleAlphaMedianBlend", "AverageLinesBlend", "AverageVerticalLinesBlend", "PixelValuesPlusOne", "AverageHorizontalFilter", "AverageVerticalFilter", "SmoothRainbowMedian", "MatrixCollectionBlend", "MatrixCollectionXor", "MatrixCollectionXor32", "MatrixCollectionRandomColorMap", "MatrixCollectionDarkXor", "MatrixCollectionRGB", "SmoothMedianBlend", "ColorTransition", "ColorTransitionRandom", "CosSinMedianBlend", "CosSinMultiplyCollectionXor", "RandomSmoothAlphaMedian", "ColorExpand", "ColorXorScale", "MatrixCollectionXorBlendAlphaBlend", "Bitwise_XOR_BlendFrame", "SimpleMatrixBlend", "SurroundingPixels", "SurroundingPixelsAlpha", "MatrixCollectionSurroundingPixels", "ColorFlashIncrease", "ScaleFilter", "NegativeDarkenXor", "ChangeXorEachSecond", "MorphXor", "XorFrameShuffle", "ChannelSortMedianBlend", "SplitFrameBlend", "SplitFrameCollection", "SplitFrameMirror", "IncreaseRGB", "XorDifferenceFilter", "MatrixCollectionVariable", "SmoothFrame64", "SmoothFrame32", "MedianBlendIncreaseFilter", "MedianBlendNegate", "BlendWithOldFrame", "BlendWith16thFrame", "BlendTrailsFilter", "MatrixCollectionRandom", "MatrixCollectionRandomSmooth", "MatrixCollectionRandomDouble", "MatrixCollectionAddImage", "MedianBlendSquare", "SmoothIntertwineMedianBlend", "ShadowAlphaTrails16", "ShadowAlphaTrailsReset", "ShadowAlphaTrails", "FadeFromColorToColor", "BlendImageLayer", "AlphaBlendRandom_Filter","resizeImageAndFrameBlend", "ColorsFilter", "ColorFadeFilter", "ColorChannelMoveUpAndDown", "AlphaBlendFlippedFilter", "ColorVariableBlend", "ColorXorBlend", "ColorAddBlend", "SelfAlphaBlendMultiThread", "BytePixelSort", "BlendChannelXor","ColorShiftXor", "XorMultiply", "ColorShadowBlend", "ColorRGB_IncDec", "ColorCollection", "ColorCollectionRandom", "ColorCollectionStrobeShift", "ColorCollectionRandom_Filter", "ColorCollectionShift", "CollectionEnergy", "ColorCollectionInterlace", "ColorCollectionStrobeShake", "ColorCollectionSubtle","ColorCollection64", "ColorCollectionSubtleStrobe", "CollectionRandom","CollectionRandomSubFilter", "CollectionAlphaXor","ColorCollection64X", "ColorCollectionSwitch", "ColorCollectionRGB_Index", "ColorCollectionReverseStrobe", "ColorCollectionXorPixel", "ColorCollectionXorOffsetFlash", "ColorCollectionMatrixGhost", "ColorPositionAverageXor","ColorPositionXor", "ColorCollectionPixelXor", "ColorGhost", "ColorCollectionTwitchSubFilter", "Buzzed", "BuzzedDark", "AlphaBlendImageDownUp", "BlendWithImageAndSource", "PixelSourceFrameBlend256", "SplitMatrixCollection", "RectangleGlitch", "ColorCollectionMovementIndex", "Shake", "Disoriented", "ColorCollectionPositionStrobe", "ColorCollectionStrobeBlend", "AlphaBlendStoredFrames", "ShiftColorLeft", "CycleInAndOutRepeat", "ColorCollectionShuffle", "BlendImageXtoY", "BlendForwardAndBack16", "BlendForwardAndBack32", "BlendForwardAndBack64","BlendForwardAndBack8_RandomStrobe", "AlphaBlendWithThreeCollections", "AlphaBlendArrayRandom","AlphaBlendArrayTrailsFilters", "AlphaBlendMirrorChannelSort","ColorCollectionAlphaBlendArray", "ColorMatrixCollectionPixelation", "ColorChannelIteration"};
    
    std::vector<std::string> svDistort { "Tri","Distort","CDraw","Sort Fuzz","Fuzz","Boxes","Boxes Fade", "ShiftPixels", "ShiftPixelsDown","WhitePixel", "Block", "BlockXor","BlockStrobe", "BlockScale", "InvertedScanlines", "ColorMorphing", "NegativeStrobe", "ParticleRelease","ParticleBlend","ParticleFlash","ParticleAlpha","ParticleReleaseXor","ParticleReleaseXorVec", "All Red", "All Green", "All Blue", "LineRGB", "PixelRGB", "BoxedRGB", "KruegerSweater", "RGBStatic1", "RGBStatic2", "FrameBars", "Lines", "WhiteLines", "ThickWhiteLines", "UseLineObject","ParticleFast", "PictureBuzz", "ParticleSnow", "RandomPixels", "DarkRandomPixels", "PixelatedHorizontalLines", "PixelatedVerticalLines", "TwistedVision", "ParticleReleaseAlphaBlend", "ParticleReleaseWithImage", "PixelateNoResize12", "PixelateNoResize8", "PixelateNoResize32", "PixelateNoResize16", "PixelateNoResize24", "StretchAlphaBlend", "StretchAlphaBlendWidth", "StretchAlphaBlendHeight", "StretchAlphaBlendTwitch", "StretchAlphaBlednTwitchFast", "StretchRandomValues", "VideoStretchHorizontal", "VideoStretchVertical","AverageHorizontalDistortion", "PositionShift"};
    
    std::vector<std::string> svPattern { "Blend Fractal","Blend Fractal Mood","Diamond Pattern" };
    
    std::vector<std::string> svGradient { "RandomGradient", "CosSinMultiply","New Blend","Color Accumlate1", "Color Accumulate2", "Color Accumulate3", "Filter8", "Graident Rainbow","Gradient Rainbow Flash","Outward", "Outward Square","GradientLines","GradientSelf","GradientSelfVertical","GradientDown","GraidentHorizontal","GradientRGB","GradientStripes", "GradientReverse", "GradientReverseBox", "GradientReverseVertical", "GradientNewFilter", "AverageLines", "QuadCosSinMultiply", "GradientColors", "GradientColorsVertical", "GradientXorSelfScale", "GradientLeftRight", "GraidentUpDown", "GradientLeftRightInOut", "GradientUpDownInOut", "GradientSubFilterXor","GradientXorPixels", "DivideAndIncH", "DivideAndIncW", "GradientAlphaXorHorizontal", "GradientAlphaXorVertical", "Filter8_Blend"};
    
    std::vector<std::string> svMirror { "ImageXorMirrorFilter", "NewOne", "MirrorBlend", "Sideways Mirror","Mirror No Blend","Mirror Average", "Mirror Average Mix","Reverse","Double Vision","RGB Shift","RGB Sep","Side2Side","Top2Bottom", "Soft_Mirror", "KanapaTrip", "InterReverse", "InterMirror", "InterFullMirror", "MirrorRGB", "LineByLineReverse", "CycleShiftRGB", "CycleShiftRandomRGB", "CycleShiftRandomRGB_XorBlend", "RGBMirror", "MirrorStrobe", "RandomMirror", "RandomMirrorBlend", "RandomMirrorAlphaBlend", "MirrorXor", "MirrorXorAll", "MirrorXorScale", "EnergyMirror", "MirrorXorAlpha", "MirrorEnergizeSubFilter", "IntertwinedMirror", "BlurredMirror", "DoubleRandomMirror", "FlipMirror", "FlipMirrorAverage","FlipMirrorSubFilter", "RGBMirror1", "RGBMirror1Median", "FlashMirror", "ReverseMirrorX", "MirrorXorAll_Reverse", "MirrorRGBReverse", "MirrorRGBReverseBlend", "MirrorBitwiseXor", "EnergyMirrorDark", "AlphaBlendMirror", "TwistedMirror", "MirrorMatrixCollection", "MirrorMatrixSource", "SmoothMirrorBlurFlip", "MirrorOrder", "BlurMirrorOrder", "AveragePixelMirror", "SoftFeedbackMirror", "MirrorAlphaBlend","RandomMirrorBitwiseXor", "MirrorBlendFrame", "MirrorBlendVertical", "MirrorVerticalAndHorizontal", "MirrorSidesMedian", "MirrorEachSecond", "Mirror_Xor_Combined", "MirrorFrameShuffle", "MirrorShuffleSmooth", "Mirror_Xor_Smooth", "XorMirrorBlendFrame", "MatrixCollectionMirrorDirection", "MirrorIntertwine", "ReverseOnOff", "MirrorLeft", "MirrorRight","MirrorBackAndForth", "FlipMirrorAlphaBlend", "StretchVerticalMirror", "MirrorTopToBottom", "MirrorBottomToTop", "MirrorSwitch", "MirrorSwitchFlip", "MirrorLeftMirrorRightBlend", "MirrorTopMirrorBottomBlend", "MirrorAll", "MirrorDoubleVision", "Mirror_Rainbow_Blur", "MirrorMedianBlur", "MirrorLeftBottomToTop", "MirrorRightTopToBottom"};
    
    std::vector<std::string> svStrobe{  "StrobeEffect", "Blank", "Type","Random Flash","Strobe Red Then Green Then Blue","Flash Black","FlashWhite","StrobeScan", "RGBFlash", "ReinterpretDouble", "DiamondStrobe", "BitwiseXorStrobe","FlashBlackAndWhite", "StrobeBlend", "FibFlash", "ScaleFlash", "FadeStrobe", "AndStrobe", "AndStrobeScale", "AndPixelStrobe", "AndOrXorStrobe", "AndOrXorStrobeScale", "BrightStrobe", "DarkStrobe", "RandomXorOpposite", "StrobeTransform", "RandomStrobe", "OrStrobe", "DifferenceStrobe", "BlackAndWhiteDifferenceStrobe", "DifferenceXor", "DifferenceRand", "HalfNegateStrobe", "RandomStrobeFlash", "GaussianStrobe", "StrobeSort", "GlitchSortStrobe", "StrobeXor", "AlphaMorph", "StrobeXorAndOr", "FlashMedianBlend", "RainbowGlichStrobe", "NegateSwitchStrobe", "StrobeAlphaShuffle","MirrorOrderAlpha", "StrobeNegatePixel", "StrobeNegateInOut", "AlphaStrobeBlend", "StrobeRandomChannel", "MaxRGB", "IncreaseQuick", "StrobeRandomFilter", "MedianStrobe", "MildStrobe", "CannyStrobe", "LaplacianStrobe", "LaplacianStrobeOnOff", "GrayStrobe", "ColorStrobeXor"};
    
    
    std::vector<std::string> svBlur { "GaussianBlur", "Median Blur", "Blur Distortion", "ColorTrails","TrailsFilter", "TrailsFilterIntense", "TrailsFilterSelfAlpha", "TrailsFilterXor","BlurSim", "TrailsInter", "TrailsBlend", "TrailsNegate", "AcidTrails", "HorizontalTrailsInter" ,"Trails", "BlendTrails", "SmoothTrails", "SmoothTrailsSelfAlphaBlend", "SmoothTrailsRainbowBlend", "MedianBlend", "XorTrails", "RainbowTrails", "NegativeTrails", "IntenseTrails", "GaussianBlend", "RandomAmountMedianBlur", "MedianBlendAnimation", "AlphaAcidTrails", "RandomBlur", "RGBTrails", "RGBTrailsDark", "RGBTrailsAlpha", "RGBTrailsNegativeAlpha", "MovementRGBTrails", "RGBTrailsXor", "DifferenceBrightStrobe", "PsycheTrails", "DarkTrails", "MedianBlurXor", "NegateTrails", "FrameBlurSubFilter", "Headrush", "MedianBlurSubFilter", "RGBColorTrails", "PixelByPixelXor", "RGBMedianBlend", "MedianBlend16", "BlurSmooth", "BlurSmoothMedian", "BlurFlip", "BlurMirrorGamma", "MedianBlendDark", "MedianBlendSubFilterEx", "SmoothTrailsBlend", "MatrixCollectionRGBXor", "LinesMedianBlend", "MedianBlendSoft", "MatrixCollectionBlurAlpha", "MedianTrails", "ColorTransitionMedian", "ColorTransitionRandomMedian", "RandomTrails", "TrailsRGB", "MatrixTrailsXorRandom", "MedianBlendSelfBlend", "RandomAmountOfMedianBlur", "GaussianBlendEx", "BlurSmoothSubFilterAlphaBlend", "BlurSmoothMatrix", "MedianBlurInc", "GaussianBlurInc", "BlurSmoothMedianInc", "BlurSmoothGaussianInc", "BlurMatrixCollectionXor", "BlurSmoothRevFilter",  "SmoothMedian64", "DarkTrailsEffect", "MedianBlend64", "SmoothRandomChannels", "SaturateBlend", "ColorTrailsFilter", "DarkNegateRainbowMedian", "PixelateBlurFilter","MatrixCollectionMedianBlendFilter", "MatrixCollectionTrails", "SmoothBlendMedian", "AlphaBlendTrails", "StrobeTrailsFilter", "AlphaBlendTrailsReverse", "ShadowAlphaTrails64", "BlurHighToLow", "RandomXorMultiThreadTest", "MedianBlendMultiThread", "FuzzyFilter","FlashMatrixTrails","GhostTrails", "MedianBlend_Random_Filter", "GhostTwitch", "GhostTwitchTrails", "Dyskinesia", "ErodeFilter", "DilateFilter", "BilateralFilter", "BilateralFilterFade", "BilateralBlend", "BilateralBlendFade", "BilateralFilterScale","ColorCollectionGhostTrails", "ColorCollectionScale", "ColorPositionXorMedianBlend", "BlurredOutXor", "DizzyFilter"};
    
    std::vector<std::string> svImage{"Blend with Image", "Blend with Image #2", "Blend with Image #3", "Blend with Image #4", "ImageFile", "ImageXor", "ImageAlphaBlend", "ImageInter", "ImageX", "SmoothRandomImageBlend", "SmoothImageAlphaBlend", "BlendImageOnOff", "ImageShiftUpLeft", "AlphaBlendImageXor", "ExactImage", "BlendImageXor", "BlendImageAround_Median", "ImageBlendTransform", "ImageXorAlpha", "ImageAverageXor", "DarkImageMedianBlend", "ImageBlendSubFilter", "ImageBlendXorSubFilter", "ImageCollectionSubFilter", "MirrorAlphaBlendedImage", "AlphaBlendXorImage", "ImageXorFrame", "ImageXorFunction", "ImageXorAlphaBlend", "ImageSubtractMedianBlend", "ImageDarkBlend", "ImageAverageDark", "ImageRemainderPixel", "ImageEnergy", "ImageDistortion", "SmoothExactImageXorAlpha", "SmoothImageAlphaBlendMedian", "ImageDarkenSmoothMedian", "XorReverseImageSmooth", "ImageSmoothMedianBlend", "ImageAlphaXorMedianBlend", "ColorTransitionImageSubFilter", "RotateImage", "RotateBlendImage", "RotateAlphaBlendImage", "ImageXorScale", "MatrixCollectionBlurImageXorAlpha", "MatrixCollectionSurroundingPixelsImage", "ImageTransparent", "ImageAlphaCollectionSmoothBlend", "ImageRandomColormap", "ImageRandomColormapAlphaBlend", "ImageRandomColormapAlphaScale", "ImageRandomColormapSubFilter", "ImageShuffle","ImageFadeInOut", "ImageFadeBlackInOut", "ImageFadeFrameInOut", "ImageFadeDouble", "ImageXor_SubFilter", "ImageStrobeOnOff", "FrameImageFadeInOut", "FrameImageFadeInOutDouble", "ShuffleImage", "ChangeImageEachSecond", "ChangeImageFilterOnOff", "ImageXorSmooth", "ImageNegate", "ImageNegateAlphaBlend", "FrameNegateAlphaBlendImage", "ImageChannelSubFilter", "ImageChannelRandom", "MirrorXorImage", "PixelImageTex", "MirrorIntertwineImage", "MatrixCollectionVariableImage", "ImageIntertwine32", "ImageIntertwine16", "ImageIntertwine8", "IntertwineRowsImageAlphaBlend", "IntertwineRowsImage","IntertwineFrameWithImage", "IntertwineImageFlip", "IntertwineImageOnOff", "ImageFlipFilter", "ImageRandomValues", "ImageLoFi", "ImageLofiAlphaBlend", "ImageAlphaBlendScale", "ImageHighToLowAlpha", "ImageDiff","FillPixelsImage", "resizeImageWidth", "resizseImageHeight", "resizeImageWidthAndHeight", "resizeImageFrameWidth", "resizeImageFrameHeight", "resizeImageFrameWidthAndHeight", "resizeImageRandom", "resizeFrameImageFlash", "IntertwineFrameImage1080X", "SortedColorVariable", "SmoothColorVariableImageBlend", "RandomImageSquares", "CollectionImage", "SplitMatrixSortChannelImage", "BlendByColsImage", "AlphaBlendArrayExpand", "ColorImageMatrixFade", "ColorImageMatrixFadeFast", "ColorImageMatrixFadeDirection", "ColorImageMatrixFadeDirectionBlend", "ColorMatrixColllectionImagePixelation", "ColorImageMatrixMedianBlend", "ColorImageBlendPixelMedian", "ColorImageBlendOrigMedian", "ColorImageBlendSource", "ColorImageMatrixFadeOnAndOff", "ColorImageMatrixRect", "ColorImageBackAndForth", "ColorImageFadeReallyFast", "ColorImageAllXor", "ColorImageMatrixFadeVariable", "ColorXorImageFade"};
    
    std::vector<std::string> svOther { "Mean", "Laplacian", "Bitwise_XOR", "Bitwise_AND", "Bitwise_OR", "Channel Sort", "Reverse_XOR", "Bitwise_Rotate", "Bitwise_Rotate Diff","Equalize","PixelSort", "GlitchSort", "HPPD", "FuzzyLines","Random Filter", "Alpha Flame Filters","Scanlines", "TV Static","FlipTrip", "Canny", "Inter","Circular","MoveRed","MoveRGB","MoveRedGreenBlue", "Wave","HighWave","VerticalSort","VerticalChannelSort","ScanSwitch","ScanAlphaSwitch", "XorAddMul","RandomIntertwine","RandomFour","RandomTwo","Darken", "AverageRandom","RandomCollectionAverage","RandomCollectionAverageMax","BitwiseXorScale","XorChannelSort","Bitwise_XOR_Average","Sort_Vertical_Horizontal","Sort_Vertical_Horizontal_Bitwise_XOR","Scalar_Average_Multiply","Scalar_Average","Total_Average","VerticalColorBars","inOrder","inOrderBySecond","DarkenFilter","RandomFilterBySecond","ThreeRandom",  "Blend with Source", "Plugin", "Custom", "inOrderAlpha", "XorBackwards", "MoveUpLeft", "Stuck", "StuckStrobe", "SoftFeedback", "SoftFeedbackFrames", "ResizeSoftFeedback","SoftFeedback8","SoftFeedbackFrames8","ResizeSoftFeedback8", "ResizeSoftFeedbackSubFilter", "SoftFeedbackRandFilter","SoftFeedback32","SoftFeedbackFrames32","ResizeSoftFeedback32", "SoftFeedbackRandFilter32", "SoftFeedbackSubFilter","SoftFeedbackResizeSubFilter", "SoftFeedbackResizeSubFilter64", "SoftFeedbackReszieSubFilter64_Negate", "SoftFeedbackReszieSubFilter64_Mirror", "RandomOther", "RandomXorFilter", "Bitwise_XOR_AlphaSubFilter", "XorBlend_SubFilter", "RandomFilterRandomTimes", "RandomSubFilterRandomTimes", "PsycheSort", "Bitwise_XOR_Sort", "BitwiseColorMatrix", "PixelatedSubFilterSort", "RandomPixelOrderSort", "FrameDifference", "SmallDiffference","FilteredDifferenceSubFilter", "GammaDarken5", "GammaDarken10","ChannelSort_NoBlend_Descending", "ChannelSort_NoBlend_Ascending", "ShuffleRGB", "ShuffleAlpha", "ShuffleSelf", "StrobeShuffle", "RainbowGlitch", "ShuffleColorMap", "RandomColorMap", "RandomOrder", "RandomAlphaBlend", "FlipShuffle", "FlipRandom", "CannyRandomPixels", "ChangeEachSecond", "SplitFramesSort", "SplitFrameFilter", "RandomChannels", "AlphaBlendChannelSort", "IncreaseRandomIndex", "PixelRowMedianBlend", "IntertwineRows32", "IntertwineRows16", "IntertwineRows8", "IntertwineAlpha", "IntertwineSubFilter", "IntertwineRows4", "Intertwine64x4", "Intertwine64X", "Intertwine64XPixel","IntertwinePixels", "IntertwineColsX", "IntertwineCols16", "IntertwineCols8","IntertwineCols32", "IntertwineRowsReverse32", "IntertwineRowsReverse16", "IntertwineRowsReverse8", "IntertwineRowsReverse64X", "IntertwineRowsSwitch32", "IntertwineRowsSwitch16", "IntertwineRowsSwitch8", "IntertwineRows64", "IntertwineRows64", "IntertwineRowsReverse64", "IntertwineRowsSwitch64", "IntertwineShuffle", "IntertwineRowsAndCols", "IntertwineColsX2", "IntertwineGhost", "IntertwineGhost32", "LineMoveInOut", "TwitchinGlitchin", "IntertwineRow2", "IntertwineRow720p", "IntertwineRow1080p", "IntertwineRow720pX2", "IntertwineRow1080pX2", "IntertwineCols1280", "IntertwineRowCols1280x720", "InterlaceVerticalFilter", "InterlaceHorizontalFilter", "IntertwineVideoShuffle", "FlipFrameFilter", "SetColormap", "FadeFromColorToColorImage", "Random_Filter", "Random_FilterX2", "Random_FilterSubFilter", "IntertwineRow480pX2", "LowFi", "HighToLow", "LowToHigh", "MoveHighAndLow", "FrameStretchAlphaBlend", "OrigAndCurrentRandomX2","resizeFrameWidth","resizeFrameHeight", "resizeFrameWidthAndHeight", "resizeFrameRandom", "RandomFlip", "IntertwineRowsShadow720p", "IntertwineRowsAlpha720p", "IntertwineByFrameDown", "IntertwineByFrameUp",  "IntertwineFrameFast", "IntertwineFrame360", "IntertwineFrame360X", "IntertwineFrameTwitch", "IntertwineFrame360_Reverse", "IntertwineFrameBlend", "IntertwineXorCollection", "IntertwineFrame720X", "IntertwineFrame1080X", "IntertwineFrameDark", "Random_FilterX2_SubFilter", "IntertwineMirrorEnergy", "IntertwineMultipleRows", "VideoTwitch", "RandomAlphaBlend", "SplitMatrixSortChannel", "SplitMatrixSortChannelArrayPosition", "IntertwineX", "IntertwineY", "IntertwineSubFilterX", "IntertwineSubFilterY", "IntertwineImageX", "IntertwineImageY","InertwineImageSubFilter"};
    
    std::vector<std::string> svOther_Custom { "Mean", "Laplacian", "Bitwise_XOR", "Bitwise_AND", "Bitwise_OR", "Channel Sort", "Reverse_XOR","Bitwise_Rotate","Bitwise_Rotate Diff", "Equalize","PixelSort", "GlitchSort","HPPD","FuzzyLines","Random Filter", "Alpha Flame Filters","Scanlines", "TV Static","FlipTrip", "Canny","Inter","Circular","MoveRed","MoveRGB", "MoveRedGreenBlue", "Wave","HighWave","VerticalSort","VerticalChannelSort","ScanSwitch", "ScanAlphaSwitch","XorAddMul", "RandomIntertwine","RandomFour","RandomTwo","Darken", "Blend with Source","AverageRandom","RandomCollectionAverage","RandomCollectionAverageMax","BitwiseXorScale","XorChannelSort","Bitwise_XOR_Average","Sort_Vertical_Horizontal","Sort_Vertical_Horizontal_Bitwise_XOR", "Scalar_Average_Multiply","Scalar_Average","Total_Average","VerticalColorBars","inOrder","inOrderBySecond","DarkenFilter","RandomFilterBySecond","ThreeRandom","inOrderAlpha","XorBackwards", "Plugin", "MoveUpLeft", "Stuck", "StuckStrobe", "SoftFeedback", "SoftFeedbackFrames", "ResizeSoftFeedback", "SoftFeedback8","SoftFeedbackFrames8","ResizeSoftFeedback8", "ResizeSoftFeedbackSubFilter", "SoftFeedbackRandFilter", "SoftFeedback32","SoftFeedbackFrames32","ResizeSoftFeedback32", "SoftFeedbackRandFilter32", "SoftFeedbackSubFilter","SoftFeedbackResizeSubFilter", "SoftFeedbackResizeSubFilter64", "SoftFeedbackReszieSubFilter64_Negate", "SoftFeedbackReszieSubFilter64_Mirror", "RandomOther", "RandomXorFilter", "Bitwise_XOR_AlphaSubFilter", "XorBlend_SubFilter", "RandomFilterRandomTimes", "RandomSubFilterRandomTimes", "PsycheSort", "Bitwise_XOR_Sort", "BitwiseColorMatrix", "PixelatedSubFilterSort", "RandomPixelOrderSort", "FrameDifference", "SmallDiffference", "FilteredDifferenceSubFilter", "GammaDarken5", "GammaDarken10", "ChannelSort_NoBlend_Descending", "ChannelSort_NoBlend_Ascending", "ShuffleRGB", "ShuffleAlpha", "ShuffleSelf", "StrobeShuffle", "RainbowGlitch", "ShuffleColorMap", "RandomColorMap", "RandomOrder", "FeedbackColormap", "RandomAlphaBlend", "FlipShuffle", "FlipRandom", "SplitFramesSort", "SplitFrameFilter", "RandomChannels", "IncreaseRandomIndex", "AlphaBlendChannelSort", "IncreaseRandomIndex", "PixelRowMedianBlend", "IntertwineRows32", "IntertwineRows16", "IntertwineRows8", "IntertwineAlpha", "IntertwineSubFilter", "IntertwineRows4", "Intertwine64x4", "Intertwine64X", "Intertwine64XPixel", "IntertwinePixels", "IntertwineColsX", "IntertwineCols16", "IntertwineCols8","IntertwineCols32", "IntertwineRowsReverse32", "IntertwineRowsReverse16", "IntertwineRowsReverse8","IntertwineRowsReverse64X", "IntertwineRowsSwitch32", "IntertwineRowsSwitch16", "IntertwineRowsSwitch8","IntertwineRows64", "IntertwineRowsReverse64", "IntertwineRowsSwitch64", "IntertwineShuffle", "IntertwineRowsAndCols", "IntertwineColsX2", "IntertwineGhost", "IntertwineGhost32", "LineMoveInOut", "TwitchinGlitchin", "IntertwineRow2", "IntertwineRow720p", "IntertwineRow1080p", "IntertwineRow720pX2", "IntertwineRow1080pX2", "IntertwineCols1280","IntertwineRowCols1280x720", "InterlaceVerticalFilter", "InterlaceHorizontalFilter", "IntertwineVideoShuffle", "FlipFrameFilter", "setColormap","FadeFromColorToColorImage", "Random_Filter", "Random_FilterX2", "Random_FilterSubFilter", "IntertwineRow480pX2", "LowFi", "HighToLow", "LowToHigh", "MoveHighAndLow", "FrameStretchAlphaBlend", "OrigAndCurrentRandomX2", "resizeFrameWidth", "resizeFrameHeight", "resizeFrameWidthAndHeight", "resizeFrameRandom", "RandomFlip","IntertwineRowsShadow720p", "IntertwineRowsAlpha720p", "IntertwineByFrameDown", "IntertwineByFrameUp", "IntertwineFrameFast", "IntertwineFrame360", "IntertwineFrame360X", "IntertwineFrameTwitch", "IntertwineFrame360_Reverse", "IntertwineFrameBlend", "IntertwineXorCollection", "IntertwineFrame720X", "IntertwineFrame1080X", "IntertwineFrameDark", "Random_FilterX2_SubFilter", "IntertwineMirrorEnergy", "IntertwineMultipleRows", "VideoTwitch", "RandomALphaBlend", "SplitMatrixSortChannel", "SplitMatrixSortChannelArrayPosition","IntertwineX", "IntertwineY", "IntertwineSubFilterX", "IntertwineSubFilterY", "IntertwineImageX", "IntertwineImageY"};
    
    std::vector<std::string> svSquare {"SquareSwap","SquareSwap4x2","SquareSwap8x4", "SquareSwap16x8","SquareSwap64x32", "SquareBars","SquareBars8","SquareSwapRand16x8","SquareVertical8","SquareVertical16","SquareVertical_Roll","SquareSwapSort_Roll","SquareVertical_RollReverse","SquareSwapSort_RollReverse", "RandomFilteredSquare","RandomQuads","QuadRandomFilter", "RollRandom", "GridFilter8x", "GridFilter16x", "GridFilter8xBlend", "GridRandom", "GridRandomPixel", "PixelatedSquare", "SmoothSourcePixel", "ColorLines", "Curtain", "RandomCurtain", "RandomCurtainVertical", "CurtainVertical", "SlideFilter","SlideFilterXor", "RandomSlideFilter", "SlideUpDown", "SlideUpDownXor", "SlideUpDownRandom", "SlideSubFilter", "SlideSubUpDownFilter", "FourSquare", "EightSquare", "DiagonalSquare", "DiagonalSquareRandom", "SquareStretchDown", "SquareStretchRight", "SquareStretchUp", "SquareStretchLeft", "ExpandSquareBlendSubFilter", "ExpandSquareSubFilter", "ExpandSquareVerticalSubFilter", "SquareDivideSubFilter", "SquareSubFilter", "SquareSubFilter8", "SquareRandomFilter", "SquareFill", "RandomSquares"};
    
    
    std::vector<std::string> vSub { "SlideSubFilter", "SubFilter", "ResizeSoftFeedbackSubFilter", "SoftFeedbackSubFilter", "SoftFeedbackResizeSubFilter", "SoftFeedbackResizeSubFilter64", "SoftFeedbackReszieSubFilter64_Negate", "SoftFeedbackReszieSubFilter64_Mirror", "Bitwise_XOR_AlphaSubFilter", "AlphaBlendSubFilter", "GradientSubFilterXor", "XorBlend_SubFilter", "SmoothSubFilterAlphaBlend", "SmoothSubFilterXorBlend", "IntertwineSubFilter", "EveryOtherSubFilter", "RandomSubFilterRandomTimes", "AddToFrameSubFilter", "SmoothSubFilter", "EnergizeSubFilter", "SmoothSubFilter16", "EnergizeSubFilter16", "EnergizeSubFilter32", "SmoothSubFilter32", "HalfAddSubFilter", "HalfXorSubFilter", "ChannelMedianSubFilter", "PixelatedSubFilterSort", "FilteredDifferenceSubFilter", "ExpandSquareSubFilter", "ExpandSquareBlendSubFilter", "ExpandSquareVerticalSubFilter", "MirrorEnergizeSubFilter", "InterRGB_SubFilter", "InterSmoothSubFilter", "StoredFramesAlphaBlend_SubFilter", "BlendSubFilter", "BlendAlphaSubFilter", "Blend_AlphaSubFilter", "FrameMedianBlendSubFilter", "FrameBlurSubFilter", "ImageBlendSubFilter", "ImageBlendXorSubFilter", "ImageCollectionSubFilter", "SubFilterMedianBlend", "DarkCollectionSubFilter", "FlipMedianSubFilter", "FlipMirrorSubFilter", "BlendCombinedValueSubFilter", "BlendSubFilterAlpha", "CollectionXorSourceSubFilter", "BlendReverseSubFilter", "SmoothBlendReverseSubFilter", "MedianBlendBufferSubFilter", "RGBBlendSubFilter", "XorOppositeSubFilter", "BlendSmoothSubFilter", "BlurSmoothSubFilter", "BlurFlipSubFilter", "MedianBlendSubFilterEx", "ShiftFrameSmoothSubFilter", "ShiftFrameStaticXorSubFilter", "RandomSubFilter", "BlendWithFrameSubFilter", "AlphaBlendWithFrameSubFilter", "AlphaXorBlendWithFrameSubFilter", "XorBlendSubFilter", "SmoothMedianRotateSubFilter", "XorSubFilter", "XorAlphaSubFilter", "BlurXorAlphaSubFilter", "ImageAlphaXorMedianSubFilter", "ImageSmoothAlphaXorSubFilter", "ImageXorSubFilter", "ImageAlphaXorSubFilter", "BlendWithRainbowSubFilter","BlendWithJetSubFilter", "ColormapBlendSubFilter", "RandomColorMapAlphaBlendSubFilter", "RandomOrderMedianBlendSubFilter", "MirrorOrderSubFilter","FilterStrobeSubFilter", "BlendImageWithSubFilter", "BlendImageWithSubFilterAlpha", "AndImageSubFilterXor", "AlphaBlendImageSubFilterXor", "AlphaBlendImageSubFilterXorRev", "ParticleReleaseSubFilter", "ParticleReleaseImageSubFilter", "ImageEnergySubFilter", "ImageDistortionSubFilter", "ReverseSubFilterBlend", "ReverseSubFilterXor", "ImageReverseSubFilter", "ImageSmoothMedianSubFilter", "MatrixCollectionSubFilter", "MatrixCollectionImageSubFilter", "TrailsSubFilter", "TrailsSubFilter32", "CompareWithSubFilter", "ColorTransitionSubFilter", "CurtainSubFilter", "RandomTrailsSubFilter", "Filter8_SubFilter", "SquareRandomSubFilter", "ColorExpandSubFilter", "RotateImageSubFilter", "FlipStrobeSubFilter", "MirrorSidesSubFilter", "MedianFrameAlphaBlendSubFilter", "MedianSubFilter", "ColorXorScaleSubFilter", "MatrixCollectionShiftSubFilter", "MatrixCollectionImageShiftSubFilter", "MatrixCollectionBlurImageSubFilter", "MatrixCollectionBlurImageSubFilter16", "ImageAlphaBlendSubFilter", "MultipleMatrixCollectionSubFilter", "BlurAlphaSubFilter", "BlurImageSubFilter", "MedianBlendSubFilter", "MedianBlendImageSubFilter", "BlendHalfSubFilter", "BlurImageAlphaBlendSubFilter", "BlurImageAlphaBlendScaleSubFilter", "AlphaBlendWithSubFilter", "AlphaBlendScaleWithSubFilter", "MatrixBlendSubFilter", "SmoothMatrixBlendSubFilter", "BlurSmoothAlphaXorBlendSubFilter", "BlurTwiceSubFilter", "BlurFrameBlendSubFilter", "BlurFrameSubFilter", "MatrixCollection8XorSubFilter", "MatrixCollectionSurroundingPixelsSubFilter", "MatrixCollectionSurroundingPixelsImageSubFilter","MatrixImageAlphaBlendSubFilter","ImageAlphaBlendWithFrameSubFilter","ImageFadeBlackInOutSubFilter","ImageFadeFrameInOutSubFilter","FadeSubFilter","FadeSubFilterRev","ImageBlendSubFilterMedianBlend","FadeSubFilterXor","BlurXorSubFilter", "NegateBlendSubFilter", "MorphXorWithSubFilter", "MirrorReverseSubFilterAlphaBlend", "SmoothSubFilter64", "SmoothMedian32_SubFilter", "SmoothAlphaMedian_SubFilter", "SmoothImage_SubFilter", "SmoothImageMedian_SubFilter", "SmoothImageAndSubFilter", "SmoothSubFilter90", "SmoothMedianImageSubFilter16", "ImageNegateAlphaBlendSubFilter", "SplitFrameSortSubFilter", "SplitFrameBlendSubFilter", "SmoothChannelSubFilter", "SaturateBlendSubFilter", "ColorTrailsSubFilter", "ImageChannelChangeSubFilter", "ImageChannelRandomSubFilter", "PixelateBlurSubFilter", "MirrorXorSubFilter", "PixelXorImageSubFilter", "PixelAlphaImageSubFilter", "PixelScaleImageSubFilter", "PixelImageSubFilter", "IntertwineSubFilter", "Intertwine64XSubFilter", "MirrorIntertwineImageSubFilter", "IntertwineImageSubFilter", "InterwtineAlphaSubFilter", "IntertwineImageAndSubFilter", "IntertwineRowsAndColsSubFilter", "MatrixCollectionVariableSubFilter", "MatrixCollectionVariableImageSubFilter", "SmoothImageAverageSubFilter", "CallSubFilterBlend50", "CallSubFilterBlend25", "CallSubFilterBlend75", "BlendWithFrameAndImageSubFilter", "IntertwineDoubleSubFilter", "IntertwineDoubleImageSubFilter", "IntertwineEachRowXSubFilter", "IntertwineGhostSubFilter", "MatrixCollectionAlphaBlendSubFilter", "MatrixCollectionImageBlendSubFilter", "ChannelSortSubFilter", "SmoothDoubleSubFilter", "AlphaBlendMedianSubFilter", "SmoothReverseSubFilter", "IntertwineWithSubFilter", "IntertwineWithImageAndSubFilter", "IntertwineImageFlipSubFilter", "IntertwineFlipImageAndSubFilter", "AlphaBlendImageAndSubFilter","StretchSubFilter", "FlashRGB_SubFilter","MirrorSwitchSubFilter","DoubleRandomAlphaImageSubFilter","ImageDiffSubFilter","OrigBlendSubFilter","resizeImageWidthAndHeightSubFilter","DifferenceSubFilter","ColorCollectionSubFilter","ColorCollectionShiftSubFilter","ColorCollectionRGBStrobeSubFilter","CollectionAlphaBlend_SubFilter","ColorCollectionTwitchSubFilter","BlendColorImageStrobeSubFilter","BlendByColsSubFilter","IntertwineImageSubFilter","IntertwineHorizontalImageSubFilter", "InterwtineHorizontalImageSubFilterByIndex","IntertwineHorizontalImageSubFilterMatrixCollection", "ColorMatrixCollectionImagePixelationSubFilter", "ColorImageSubFilterXor"};
    
    
    void SortFilters() {
        std::sort(vzBlend.begin(), vzBlend.end());
        std::sort(svDistort.begin(), svDistort.end());
        std::sort(svPattern.begin(), svPattern.end());
        std::sort(svGradient.begin(), svGradient.end());
        std::sort(svMirror.begin(), svMirror.end());
        std::sort(svStrobe.begin(), svStrobe.end());
        std::sort(svBlur.begin(), svBlur.end());
        std::sort(svImage.begin(), svImage.end());
        std::sort(svOther.begin(), svOther.end());
        std::sort(svOther_Custom.begin(), svOther_Custom.end());
        std::sort(svSquare.begin(), svSquare.end());
        std::sort(vSub.begin(), vSub.end());
    }
}
