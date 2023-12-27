Texture2D tex_pos : register(t0);
Texture2D tex_color : register(t1);
SamplerState gSampler : register(s0);

struct PS_INPUT
{
    float4 Position : SV_POSITION;
    float2 TexCoord : TEXCOORD;
};

float4 PS(PS_INPUT pin) : SV_Target
{
    float4 position = tex_pos.Sample(gSampler, pin.TexCoord).xyzw;
    float4 color = tex_color.Sample(gSampler, pin.TexCoord).xyzw;

    return position * 0.5f + color * 0.5f;
}