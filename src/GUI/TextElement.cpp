#include "stdafx.h"
#include "GUI2.h"

#if 0

namespace System
{
namespace Gui
{

DependencyClass* TextElement::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_FontSizeProperty(),
		get_FontFamilyProperty(),
		get_FontWeightProperty(),
		get_FontStyleProperty(),
		get_TextSourceProperty(),
		get_TextProperty(),
		get_BrushProperty(),
//		get_CursorPositionProperty(),
//		get_CursorLineProperty(),
//		get_CursorColumnProperty(),
	};

	return &depclass;
}

DependencyClass* TextElement::pClass(get_Class());

IMP_DEPENDENCY_PROPERTY(float, TextElement, FontSize, 17.0f)
IMP_DEPENDENCY_PROPERTY(String, TextElement, FontFamily, new FontFamily(L"Courier New"))
IMP_DEPENDENCY_PROPERTY(int, TextElement, FontWeight, 400)
IMP_DEPENDENCY_PROPERTY(FontStyle, TextElement, FontStyle, FontStyle_Normal)

IMP_DEPENDENCY_PROPERTY(ITextSource*, TextElement, TextSource, nullptr)
IMP_DEPENDENCY_PROPERTY(String, TextElement, Text, nullptr)
//IMP_DEPENDENCY_PROPERTY(Geometry*, TextElement, LayoutRect, NULL)
IMP_DEPENDENCY_PROPERTY(Brush*, TextElement, Brush, new SolidColorBrush(0,0,0))

/*
//IMP_DEPENDENCY_PROPERTY(float, TextVisual, Width, _this().getWidth())
IMP_DEPENDENCY_PROPERTY(float, TextVisual, WidthIncludingTrailingWhitespace, _this().getWidthIncludingTrailingWhitespace())
IMP_DEPENDENCY_PROPERTY(float, TextVisual, MinWidth, _this().DetermineMinWidth())

IMP_DEPENDENCY_PROPERTY(int, TextVisual, CursorPosition, 0)
IMP_DEPENDENCY_PROPERTY(int, TextVisual, CursorLine, 0)
IMP_DEPENDENCY_PROPERTY(int, TextVisual, CursorColumn, 0)
*/

Dictionary* dict;

TextElement::TextElement() : UIElement(get_Class())
{
	dict = new Dictionary;
//	Expressive::Parser::FromFile2("D:\\Templates.gui", dict);

}

/*
void TextElement::Render(ManagedRetainedRenderContext renderContext)
{
	renderContext.OutputText(
		GetProperty(&TextProperty),
		GetProperty(&TextSourceProperty),
		GetProperty(&BrushProperty),
		GetProperty(&FontFamilyProperty),
		GetProperty(&FontSizeProperty),
		GetProperty(&FontStyleProperty),
		GetProperty(&FontWeightProperty));

	//	get_Text(), get_Brush(), get_FontFamily(), get_FontSize(), get_FontWeight());
}
*/

}	// Gui
}	// System

#endif