#pragma once

#include "Mesh.h"

class CubeMap : public Mesh
{
public:
	void InitialiseCubeMap();

	virtual void RenderMesh() override;

};

