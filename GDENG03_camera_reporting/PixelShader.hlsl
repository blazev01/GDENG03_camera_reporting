struct PS_INPUT
{
    float4 position : POSITION;
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

Texture2D Texture : register(t0);
sampler TexSampler : register(s0);

float4 psmain(PS_INPUT input) : SV_TARGET
{
    return input.albedo;
}