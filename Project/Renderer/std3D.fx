struct VS_IN
{
	float3 vPos : POSITION;
	float4 vColor : COLOR;
	float2 UV : TEXCOORD;
};

struct VS_OUT
{
	float4 vPos : SV_Position;
	float4 vColor : COLOR;
	float2 UV : TEXCOORD;
};

VS_OUT VS_Main(VS_IN _inData)
{
	VS_OUT outData;
	outData.vPos = float4(_inData.vPos,1.0f);
	outData.vColor = _inData.vColor;
	return outData;
}
float4 PS_Main(VS_OUT _inData) : SV_Target
{
	return float4(1.0f,1.0f,0.0f,1.0f);//_inData.vColor;
}