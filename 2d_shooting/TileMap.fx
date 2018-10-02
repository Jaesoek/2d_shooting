//tileMap.fx

/*
	3D (16) 2D (9)     
	{1,0,0,0} -> x축 0축   {1,0,0} -> x축
	{0,1,0,0} -> y축       {0,1,0} -> y축 
	{0,0,1,0} -> z축       {0,0,1} -> 좌표 
	{0,0,0,1} -> 좌표 1좌표
*/
float4x4 matWorld;
float4x4 matView;
float4x4 matProjection;

texture pTex;
sampler2D Tex = sampler_state
{
	Texture = pTex;
};
float2 tiling;

float4 Color;

struct VS_INPUT
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD0;
};
struct PS_INPUT
{
	float4 position : POSITION;
	float2 texCoord : TEXCOORD0;
};
PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output;
	output.position = mul(input.position, matWorld);
	output.position = mul(output.position, matView);
	output.position = mul(output.position, matProjection);

	//0 ~ 1.0f; 10 
	//0~ 1 0 ~ 0 0~ 1
	output.texCoord = input.texCoord;

	return output;
}

float4 PS(PS_INPUT input) : COLOR
{
	float2 temp = input.texCoord;

	temp.x *= tiling.x;
	temp.y *= tiling.y;

	//셰이더에서는 실수끼리 나머지 연산이 된다. 
	temp.x = temp.x % 1.0f;
	temp.y = temp.y % 1.0f;

	float4 color = tex2D(Tex, temp);

	return Color;
}

technique TILING
{
	pass p0
	{
		VertexShader = compile vs_3_0 VS();
		PixelShader = compile ps_3_0 PS();
	}
}