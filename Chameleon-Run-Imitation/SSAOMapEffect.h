#pragma once

/*
PCH: Yes
*/

namespace ba
{
	class SSAOMapEffect final : public EffectWrapper
	{
	public:
		enum ETechType
		{
			kSSAOMap =0,
			kMax
		};

	public:
		SSAOMapEffect();
		~SSAOMapEffect() override;

		bool Init(ID3D11Device* device, const std::wstring& file_name) override;
		void Destroy() override;

		ID3DX11EffectTechnique* tech(ETechType type);


		//
		// Set Effect Variables
		//

		// Per frame.
		void SetFarPlaneCorners(const XMFLOAT4 vec[4]);
		void SetOffsetVectors(const XMFLOAT4 vec[14]);

		// Per resize.
		void SetProj(const XMMATRIX& matrix);

		// Change rarely.
		void SetToTex(const XMMATRIX& matrix);
		void SetNormalDepthMap(ID3D11ShaderResourceView* srv);
		void SetRandomVectorMap(ID3D11ShaderResourceView* srv);

	private:
		ID3DX11EffectTechnique** techs_;

		ID3DX11EffectVectorVariable* far_plane_corners_;
		ID3DX11EffectVectorVariable* offset_vectors_;

		ID3DX11EffectMatrixVariable* proj_;

		ID3DX11EffectMatrixVariable* to_tex_;
		ID3DX11EffectShaderResourceVariable* normal_depth_map_;
		ID3DX11EffectShaderResourceVariable* random_vector_map_;
	};
}