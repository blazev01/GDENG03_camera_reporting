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

cbuffer constant : register(b0)
{
    row_major float4x4 world;
    row_major float4x4 view;
    row_major float4x4 proj;
    float time;
}

VS_OUTPUT vsmain(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;
    
    output.position = mul(input.position, world);
    output.position = mul(output.position, view);
    output.position = mul(output.position, proj);
    
    output.texcoord = input.texcoord;
    output.albedo = input.albedo;
    
    return output;
}