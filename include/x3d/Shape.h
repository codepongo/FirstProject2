#ifndef x3d_Shape_h
#define x3d_Shape_h

namespace System
{
namespace x3d
{

class X3DEXT Shape : 
	public X3DShapeNode,
	public X3DBoundedObject,

//	public X3DNode,
	public X3DBoundedImplImpl,
	public RenderImplImpl
{
public:
	CTOR Shape();

	virtual void Draw(X3DDrawContext* pDC) override;
	virtual BoundingBox CalculateBoundingBox(gm::matrix4f& transform) override;

	virtual X3DGeometryNode* getGeometry() override;
	virtual void setGeometry(X3DGeometryNode* node) override;

	X3DAppearanceNode* getAppearance();
	virtual void setAppearance(X3DAppearanceNode* node) override;

//	virtual void addActors(NxScene* nxScene, D3DXMATRIX modelView) override;
	virtual void UpdatePos() override;

	virtual void AddShapeDesc(physx::PxRigidActor* actorDesc);

	static X3DFieldDefinition* get_appearanceFieldDef();
	static X3DFieldDefinition* get_geometryFieldDef();

	virtual void DrawOverlay(X3DDrawContext* pDC) override;

	X3DNODE(Shape, X3DShapeNode)

private:

	TypedSFNode<X3DAppearanceNode*>* m_appearance;
	TypedSFNode<X3DGeometryNode*>* m_geometry;
	/*
	SFNode  [in,out] appearance NULL     [X3DAppearanceNode]
	SFNode  [in,out] geometry   NULL     [X3DGeometryNode]
	SFVec3f []       bboxCenter 0 0 0    (-8,8)
	SFVec3f []       bboxSize   -1 -1 -1 (0,8) or -1 -1 -1
  */
};

}	// x3d
}

#endif // x3d_Shape_h
