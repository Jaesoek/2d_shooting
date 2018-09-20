//fileName : BaseShader.fx

//전역변수 
float3 vLightDir;
texture diffuseTex;
sampler2D diffuseSampler = sampler_state
{
	Texture = diffuseTex;
};

texture normalTex;
sampler2D normalSampler = sampler_state
{
	Texture = normalTex;
};

struct VS_INPUT
{
	float4 position : POSITION;
	float2 texCoord0 : TEXCOORD0;
	float2 texCoord1 : TEXCOORD1;
};

struct VS_OUTPUT
{
	float4 position : POSITION;
	float2 texCoord0 : TEXCOORD0;
	float2 texCoord1 : TEXCOORD1;
};

VS_OUTPUT vs_main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = input.position;
	output.texCoord0 = input.texCoord0;
	output.texCoord1 = input.texCoord1;
	return output;
}
float4 ps_main(VS_OUTPUT input) : COLOR0
{
	float4 normal = tex2D(normalSampler,input.texCoord1);

	// normal  수직  0~ 1 -1 ~ 1
	float3 temp = (normal.xyz * 2.0f) -1;
	float3 toLight = normalize(vLightDir);

	float diffuse = dot(temp, toLight);
	//saturate(float) 0 ~ 1;
	diffuse = saturate(diffuse);
	float3 reflect = -toLight + 2.0f *diffuse * temp;

	reflect = normalize(reflect);

	float3 eyeDir = float3(0, 0, 1);

	float spec = saturate(dot(reflect, eyeDir));
	spec = pow(spec, 30.0f);

	float4 albedo = tex2D(diffuseSampler,input.texCoord0);
	float4 color = albedo * diffuse;

	//컬러 0~ 1
	return color + float4(1,1,1,1) * spec;
}

technique COLOR
{
	pass p0
	{
		VertexShader = compile vs_3_0 vs_main();
		PixelShader = compile ps_3_0 ps_main();
	}
}