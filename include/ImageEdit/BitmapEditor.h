namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT BitmapEditor : public Gui::UIElement, public Gui::IRootVisual
{
public:

	CTOR BitmapEditor();

	void OnTimer(double);

	virtual void InvalidateRender() override;
	virtual Gui::OleContainer* GetOleContainer() override
	{
		return NULL;
	}
	virtual Graphics::GraphicsI* GetGI() override
	{
		return GetRoot()->GetGI();
	}

	bool ElementCaptureMouse(Gui::UIElement* element) override
	{
		return false;
	}
	bool ElementReleaseMouseCapture(Gui::UIElement* element) override
	{
		return false;
	}

	virtual void RenderRetained(Gui::ManagedRetainedRenderContext pGraphics) override;
//	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize);

	virtual void OnLeftMouseButtonDown(Gui::MouseButtonEventArgs* args) override;
	virtual void OnLeftMouseButtonUp(Gui::MouseButtonEventArgs* args) override;

//	virtual void OnMouseDown(Gui::MouseButtonEventArgs* args);
//	virtual void OnMouseUp(Gui::MouseButtonEventArgs* args);
	virtual void OnMouseMove(Gui::MouseEventArgs* args) override;

	/*
	void OnLayerAddLayer(Object* sender, Gui::ExecutedRoutedEventArgs* args);
	void OnCanLayerAddLayer(Object* sender, Gui::CanExecuteRoutedEventArgs* args);

	void OnLayerAddLayerMask(Object* sender, Gio::ExecutedRoutedEventArgs* args);
	void OnCanLayerAddLayerMask(Object* sender, Gui::CanExecuteRoutedEventArgs* args);

	*/

	//void OnFramePropertyChanged(Object* sender, StringW* propertyName);

	void Add(Gui::Visual* visual);

	virtual void OnSetRoot(Gui::IRootVisual* root) override;

	void set_Mask(Mask* mask);
	void UpdateBitmap();

	virtual void Invalidate(gm::RectI* rect);

	void set_Bitmap(Graphics::Bitmap* bitmap);

	Graphics::Bitmap* GetCompositeBitmap();

	unsigned int get_CanvasWidth()
	{
		return (unsigned int)GetCompositeBitmap()->get_Width();
	}

	unsigned int get_CanvasHeight()
	{
		return (unsigned int)GetCompositeBitmap()->get_Height();
	}

	DEPENDENCY_CLASS(BitmapEditor, Gui::UIElement)

	DEPENDENCY_PROPERTY(bool, ViewSelectionOutline)
//	DEPENDENCY_PROPERTY(bool, ShowRulers)
	DEPENDENCY_PROPERTY(float, ZoomFactor)
	DEPENDENCY_PROPERTY(ImageTool*, Tool)

	class DrawBitmap : public Gui::UIElement
	{
	public:

		CTOR DrawBitmap() : Gui::UIElement(get_Class())
		{
		}

		virtual void Render(Gui::ManagedRenderContext renderContext) override
		{
			Graphics::Bitmap* bitmap = m_ed->GetCompositeBitmap();

			if (!m_ed->m_bitmapUpdated)
			{
				m_ed->m_bitmapUpdated = true;
				m_ed->UpdateBitmap();
			}

			renderContext.DrawBitmap(bitmap, GetRect(), 1.0f);
		}

		gm::RectF GetRect()
		{
			Graphics::Bitmap* bitmap = m_ed->GetCompositeBitmap();
			return gm::RectF(0, 0, bitmap->GetWidth(), bitmap->GetHeight());
		}

		virtual Gui::UIElement* HitTest(gm::PointF point) override
		{
			if (GetRect().Contains(point))
			{
				return this;
			}

			return nullptr;
		}

		static Gui::DependencyClass* get_Class();

		BitmapEditor* m_ed;
	};

	Gui::Visuals* m_elements;
	Graphics::Bitmap* m_compositeBitmap;
	Graphics::Bitmap* m_compositeBitmaps[2];
	//Graphics::RenderTarget* m_compositeRTs[2];
	Graphics::RenderTarget* m_compositeRT;
	Mask* m_currentMask;
	MaskOutlineVisual* m_maskrender;

	Gui::Visual* m_topelement;

	DrawBitmap* m_drawBitmap;

public:

	SelectedItems* m_selected;

//	BrowserFrame* m_frame;

	ImageDocument* m_document;
	Layer* m_activeLayer;

	Graphics::Bitmap* m_checkboardBitmap;

	RenderTo m_renderTo;

	int m_dragging;
	int m_marchingOffset;
	bool m_showLayerEdges;
	bool m_bitmapUpdated;

//	bool dragging;
	Gui::Visual* m_hitVisual;
	Gui::Point m_startpt;
	Gui::Point m_oldpt;

};

}	// ImageEdit
}	// System
