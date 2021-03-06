namespace System
{
namespace Gui
{

class GUIEXT GroupVisual : public UIElement
{
public:

	CTOR GroupVisual();

	virtual void Render(ManagedRenderContext renderContext) override;
//	virtual UIElement* HitTest(LDraw::PointF point) override;

	virtual size_t GetChildrenCount() override;
	virtual Visual* GetChild(size_t index) override;
	virtual void AddChild(Visual* element) override;

	virtual geometry GetHitGeometry() override;

	void Add(Visual* element)
	{
		AddChild(element);
	}

	DEPENDENCY_CLASS(GroupVisual, UIElement)

	DEPENDENCY_PROPERTY(VisualCollection*, Children)
};

}	// Gui
}	// System
