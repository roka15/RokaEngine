cbuffer cb_GLOBAL : register(b0)
{
	float2 g_Resolution;
	float2 globalPadding;
}
cbuffer cb_TRANSFORM : register(b1)
{
	row_major matrix g_matWorld;
	row_major matrix g_matWorldInv;

	row_major matrix g_matView;
	row_major matrix g_matViewInv;

	row_major matrix g_matProjec;
	row_major matrix g_matProjecInv;

	row_major matrix g_matWV;
	row_major matrix g_matWVP;
}