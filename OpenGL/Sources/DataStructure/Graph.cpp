#include <DataStructure\Graph.hpp>
#include <iostream>

namespace DataStructure
{
	Graph::~Graph()
	{
		for (GameObject* obj : Objects)
		{
			if (obj->Collider)
				delete obj->Collider;
			delete obj;
		}
		Objects.clear();
	}

	void UpdateNode(SceneNode& curNode, LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights)
	{
		Physics::Transform& transform = curNode.Object->Transform;
		curNode.LocalTransform = Mat4::CreateTransformationMatrix(transform.Position, transform.Scale, transform.Rotation);
		curNode.WorldTransform = curNode.Parent->WorldTransform * curNode.LocalTransform;
		curNode.Object->Mesh.ModelMatrix = curNode.WorldTransform;
		curNode.Object->Mesh.MVPmat = cam.ViewProjectionMatrix * curNode.WorldTransform;
		curNode.Object->Mesh.Draw(cam, dirLights, pointLights, spotLights);
		if (curNode.Object->Collider)
			curNode.Object->Collider->Draw(curNode.Object->Mesh.MVPmat);
		for (SceneNode& node : curNode.Children)
			UpdateNode(node, cam, dirLights, pointLights, spotLights);
	}

	void Graph::Update(LowRenderer::Camera& cam, const std::vector<LowRenderer::DirectionalLight>& dirLights, const std::vector<LowRenderer::PointLight>& pointLights, const std::vector<LowRenderer::SpotLight>& spotLights)
	{
		for (SceneNode& node: RootChildren)
		{
			Physics::Transform& transform = node.Object->Transform;
			node.WorldTransform = Mat4::CreateTransformationMatrix(transform.Position, transform.Scale, transform.Rotation);
			node.Object->Mesh.ModelMatrix = node.WorldTransform;
			node.Object->Mesh.MVPmat = cam.ViewProjectionMatrix * node.WorldTransform;
			node.Object->Mesh.Draw(cam, dirLights, pointLights, spotLights);
			if(node.Object->Collider)
				node.Object->Collider->Draw(node.Object->Mesh.MVPmat);
			for (SceneNode& child : node.Children)
				UpdateNode(child, cam, dirLights, pointLights, spotLights);
		}

		for (GameObject* obj : Objects)
		{
			if (obj->Collider)
				obj->Collider->ComputeBoundaries(obj->Transform);
		}
	}
}
