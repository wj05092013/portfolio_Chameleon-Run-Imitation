#include "stdafx.h"

namespace ba
{
	//
	// ModelData class
	//

	ModelData::ModelData() :
		diffuse_map(nullptr)
	{
	}

	bool ModelData::Init(ID3D11Device* device, const GeometryGenerator::Geometry& geo, const XMMATRIX& local_transform, const light::Material& material)
	{
		UINT vtx_count = geo.vertices.size();

		std::vector<inputvertex::PosNormalTexTangent::Vertex> vertices(vtx_count);
		for (UINT i = 0; i < vtx_count; ++i)
		{
			vertices[i].pos = geo.vertices[i].pos;
			vertices[i].normal = geo.vertices[i].normal;
			vertices[i].uv = geo.vertices[i].uv;
			vertices[i].tangent = geo.vertices[i].tangent;
		}

		std::vector<UINT> indices;
		indices.insert(indices.begin(), geo.indices.begin(), geo.indices.end());

		if (!mesh.BuildVertexBuffer(device, vertices))
			return false;
		if (!mesh.BuildIndexBuffer(device, indices))
			return false;
		mesh.set_local_transform(local_transform);
		mesh.set_material(material);

		return true;
	}

	//
	// Model class
	//

	Model::Model(ModelData* model_data) :
		model_data_(model_data),
		scale_(XMVectorZero()),
		rotation_(XMVectorZero()),
		translation_(XMVectorZero()),
		local_world_(XMMatrixIdentity()),
		model_type_(kStatic)
	{
	}

	Model::Model(ModelData* model_data, EModelType type) :
		model_data_(model_data),
		scale_(XMVectorZero()),
		rotation_(XMVectorZero()),
		translation_(XMVectorZero()),
		local_world_(XMMatrixIdentity()),
		model_type_(type)
	{
	}

	Model::~Model()
	{
	}

	void Model::OnCollision(const collision::CollisionInfo& info)
	{
		// Do nothing.
	}

	void Model::UpdateWorldTransform()
	{
		local_world_ = model_data_->mesh.local_transform()
			* XMMatrixScalingFromVector(scale_)
			* XMMatrixRotationQuaternion(rotation_)
			* XMMatrixTranslationFromVector(translation_);
	}

	void Model::set_model_data(ModelData* model_data)
	{
		model_data_ = model_data;
	}

	void Model::set_scale(const XMVECTOR& scale)
	{
		scale_ = scale;
	}

	void Model::set_rotation(const XMVECTOR& rotation)
	{
		rotation_ = rotation;
	}

	void Model::set_translation(const XMVECTOR& translation)
	{
		translation_ = translation;
	}

	const ModelData* Model::model_data() const
	{
		return model_data_;
	}

	const XMVECTOR& Model::scale() const
	{
		return scale_;
	}

	const XMVECTOR& Model::rotation() const
	{
		return rotation_;
	}

	const XMVECTOR& Model::translation() const
	{
		return translation_;
	}

	const XMMATRIX& Model::local_world() const
	{
		return local_world_;
	}

	Model::EModelType Model::model_type() const
	{
		return model_type_;
	}
}
