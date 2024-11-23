struct VS_INPUT
{
    float4 position : POSITION;
    float2 texcoord : TEXCOORD0;
    float4 albedo : ALBEDO;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD0;
    float4 albedo : ALBEDO;
};

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    return output;
}